#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

mt19937 gen;

void randinit()
{
	srand(time(NULL));
	gen.seed(rand());
}

ll getrand(ll lo, ll hi)
{
	uniform_int_distribution<ll> dist(lo, hi);
	return dist(gen);
}

struct node
{
	int key, prior;
	int l, r;
	node() {}
	node(int key) : key(key), prior(getrand(1, 1e9)), l(0), r(0) {}
	node(int key, int prior) : key(key), prior(prior), l(0), r(0) {}
};

int node_count = 1;
int root = 0;
vector<node> nodes(1);

int newNode()
{
	nodes.emplace_back();
	return node_count++;
}

int newNode(int key)
{
	nodes.emplace_back(key);
	return node_count++;
}

int newNode(int key, int prior)
{
	nodes.emplace_back(key, prior);
	return node_count++;
}

void merge(int t, int l, int r)
{
	if (l == 0 || r == 0)
	{
		nodes[t] = l ? nodes[l] : nodes[r];
	}
	if (nodes[l].prior > nodes[r].prior)
	{
		merge(nodes[l].r, nodes[l].r, r);
		nodes[t] = nodes[l];
	}
	else
	{
		merge(nodes[r].l, l, nodes[r].l);
		nodes[t] = nodes[r];
	}
}

void split(int t, int key, int& l, int& r)
{
	if (nodes[t].key <= key)
	{
		l = t;
		split(nodes[t].r, key, nodes[l].r, r);
	}
	else
	{
		r = t;
		split(nodes[t].l, key, l, nodes[r].l);
	}
}

void insert(int& t, int k)
{
	if (t == 0)
	{
		t = k;
	}
	else if (nodes[t].prior < nodes[k].prior)
	{
		split(t, nodes[k].key, nodes[k].l, nodes[k].r);
		t = k;
	}
	else if (nodes[t].key > nodes[k].key)
	{
		insert(nodes[t].r, k);
	}
	else
	{
		insert(nodes[t].l, k);
	}
}

void insert(int x)
{
	int k = newNode(x);
	insert(root, k);
}

void erase(int& t, int key)
{
	if (t == 0) return;
	else if (nodes[t].key > key)
	{
		erase(nodes[t].r, key);
	}
	else if (nodes[t].key < key)
	{
		erase(nodes[t].l, key);
	}
	else
	{
		merge(t, nodes[t].l, nodes[t].r);
	}
}

void erase(int key)
{
	erase(root, key);
}

