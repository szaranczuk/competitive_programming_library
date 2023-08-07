template<typename T>
struct DsuEntry
{
	int p;
	int rank;
	T val;
};

template<typename T>
struct set_to_first
{
	void operator()(const T& a, const T& b, T& out) {out = a;}
};

template<typename T, typename MergeFunc = set_to_first<T>>
struct Dsu
{
	vector<DsuEntry<T>> entries;
	int find_parent(int v)
	{
		if (this->entries[v].p == -1) return v;
		else return entries[v].p = this->find_parent(entries[v].p);
	}
	void makeset(int v, T val)
	{
		this->entries[v].p = -1;
		this->entries[v].rank = 0;
		this->entries[v].val = val;
	}
    Dsu(){}
	Dsu(int _size)
	{
		this->entries.resize(_size);
		for (int i = 0; i < _size; i++) this->makeset(i, (T) 0);
	}
	Dsu(const vector<T>& arr)
	{
		int _size = arr.size();
		for (int i = 0; i < _size; i++) this->makeset(i, arr[i]);
	}
	void unify(int a, int b)
	{
		int a_parent = this->find_parent(a);
		int b_parent = this->find_parent(b);
		if (this->entries[a_parent].rank > this->entries[b_parent].rank)
		{
			this->entries[b_parent].p = a_parent;
			MergeFunc(this->entries[a_parent].val, this->entries[b_parent].val, this->entries[a_parent].val);
		}
		else if (this->entries[a_parent].rank < this->entries[b_parent].rank)
		{
			entries[a_parent].p = b_parent;
			MergeFunc(this->entries[b_parent].val, this->entries[a_parent].val, this->entries[b_parent].val);
		}
		else if (a_parent != b_parent)
		{
			this->entries[b_parent].p = a_parent;
			this->entries[a_parent].rank++;
			MergeFunc(this->entries[a_parent].val, this->entries[b_parent].val, this->entries[a_parent].val);
		}
	}
    bool are_together(int a, int b) {return this->find_parent(a) == this->find_parent(b);}
};
