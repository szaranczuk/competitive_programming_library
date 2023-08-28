template<typename T>
struct DsuEntry
{
	int p;
	int tree_rank;
	T val;
};
 
template<typename T>
struct set_to_first
{
	void operator()(const T& a, const T& b, T& out) {out = a;}
};
 
template<typename T>
struct RollbackEntry
{
	int idx;
	DsuEntry<T> state;
	bool even_ranks;
};
 
template<typename T, typename MergeFuncStruct = set_to_first<T>>
struct Dsu
{
	MergeFuncStruct MergeFunc;
	vector<DsuEntry<T>> entries;
	vector<RollbackEntry<T>> rollback_stack;
	int comps = 0;
	void rollback()
	{
		if (this->rollback_stack.empty()) return;
		RollbackEntry<T> v = this->rollback_stack.back();
		this->rollback_stack.pop_back();
		if (v.even_ranks)
		{
			this->entries[entries[v.idx].p].tree_rank--;
		}
		this->entries[v.idx] = v.state;
		this->comps++;
	}
	int get_comps() {return comps;}
	int find_parent(int v)
	{
		if (this->entries[v].p == -1) return v;
		else return this->find_parent(entries[v].p);
	}
	void makeset(int v, T val)
	{
		this->entries[v].p = -1;
		this->entries[v].tree_rank = 0;
		this->entries[v].val = val;
		this->comps++;
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
		this->entries.resize(_size);
		for (int i = 0; i < _size; i++) this->makeset(i, arr[i]);
	}
	bool unify(int a, int b)
	{
		int a_parent = this->find_parent(a);
		int b_parent = this->find_parent(b);
		if (this->entries[a_parent].tree_rank > this->entries[b_parent].tree_rank)
		{
			rollback_stack.push_back({b_parent, entries[b_parent], false});
			this->entries[b_parent].p = a_parent;
			MergeFunc(this->entries[a_parent].val, this->entries[b_parent].val, this->entries[a_parent].val);
			this->comps--;
			return true;
		}
		else if (this->entries[a_parent].tree_rank < this->entries[b_parent].tree_rank)
		{
			rollback_stack.push_back({a_parent, entries[a_parent], false});
			entries[a_parent].p = b_parent;
			MergeFunc(this->entries[b_parent].val, this->entries[a_parent].val, this->entries[b_parent].val);
			this->comps--;
			return true;
		}
		else if (a_parent != b_parent)
		{
			rollback_stack.push_back({b_parent, entries[b_parent], true});
			this->entries[b_parent].p = a_parent;
			this->entries[a_parent].tree_rank++;
			MergeFunc(this->entries[a_parent].val, this->entries[b_parent].val, this->entries[a_parent].val);
			this->comps--;
			return true;
		}
		else
		{
			return false;
		}
	}
	bool are_together(int a, int b) {return this->find_parent(a) == this->find_parent(b);}
};
