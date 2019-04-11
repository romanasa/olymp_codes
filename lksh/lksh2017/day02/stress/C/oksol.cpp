#include <iostream>
#include <vector>
#include <cstdio>
#include <set>
#include <cassert>
#include <map>
#include <algorithm>

using namespace std;

const int MAXN = 3e5 + 10;

struct Treap {
	int x, y;
	int sz, prior;
	Treap *left, *right, *parent;
	Treap (int x = -1, int y = -1):
		x(x), y(y), sz(1), prior(rand()), left(NULL), right(NULL), parent(NULL) {}
};

set <int> gr[MAXN];

map <pair <int, int>, Treap *> get_node;

int get_sz_left(Treap *x) {
	if (x == NULL)
		return 0;
	int res = ((x->left != NULL) ? x->left->sz : 0) + 1;
	while (x->parent != NULL) {
		if (x->parent->left != x)
			res += ((x->parent->left != NULL) ? x->parent->left->sz : 0) + 1;
		x = x->parent;
	}
	return res - 1;
}

void print_tree(Treap *root) {
	if (root == NULL)
		return;
	if (root->left != NULL)
		assert(root->left->parent == root);
	if (root->right != NULL)
		assert(root->right->parent == root);
	print_tree(root->left);
	cout << "(" << root->x + 1 << "->" << root->y + 1 << ") ";
	print_tree(root->right);
}

Treap *make_node(int x, int y) {
	Treap *cur = new Treap(x, y);
	get_node[make_pair(x, y)] = cur;
	return cur;
}

void update(Treap *a) {
	if (a == NULL)
		return;
	a->sz = 1;
	if (a->left != NULL)
		a->sz += a->left->sz;
	if (a->right != NULL)
		a->sz += a->right->sz;
}

void set_edge(Treap *p, Treap *x, bool isright) {
	if (isright) {
		if (p != NULL)
			p->right = x;
		if (x != NULL)
			x->parent = p;
	} else {
		if (p != NULL)
			p->left = x;
		if (x != NULL)
			x->parent = p;
	}
}

Treap *merge(Treap *l, Treap *r) {
	if (l == NULL)
		return r;
	if (r == NULL)
		return l;
	if (l->prior > r->prior) {
		set_edge(l, merge(l->right, r), 1);
		update(l);
		return l;
	} else {
		set_edge(r, merge(l, r->left), 0);
		update(r);
		return r;
	}
}

void split(Treap *root, Treap *&l, Treap *&r, int sz_left) {
	if (sz_left == 0) {
		l = NULL, r = root;
		return;
	}
	if (root->sz <= sz_left) {
		l = root, r = NULL;
		return;
	}
	int lsz = (root->left != NULL) ? root->left->sz : 0;
	if (lsz >= sz_left) {
		Treap *tmp_l = NULL, *tmp_r = NULL;
		split(root->left, tmp_l, tmp_r, sz_left);
		set_edge(root, tmp_r, 0);
		update(root);
		l = tmp_l, r = root;
	} else {
		Treap *tmp_l = NULL, *tmp_r = NULL;
		split(root->right, tmp_l, tmp_r, sz_left - lsz - 1);
		set_edge(root, tmp_l, 1);
		update(root);
		l = root, r = tmp_r;
	}
	l->parent = r->parent = NULL;
}

Treap *get_root(Treap *x) {
	while (x != NULL && x->parent != NULL)
		x = x->parent;
	return x;
}

Treap *get_some_node(int v) {
	if (gr[v].empty())
		return NULL;
	int u = (*gr[v].begin());
	return get_node[{v, u}];
}

Treap *make_root(int v) {
	Treap *a = get_some_node(v);
	if (a == NULL)
		return NULL;
	Treap *root = get_root(a);
	Treap *l, *r;
	split(get_root(a), l, r, get_sz_left(a));
	root = merge(r, l);
	return root;
}

void link(int x, int y) {
	make_root(x);
	Treap *p = get_root(get_some_node(x));
	
	make_root(y);
	Treap *q = get_root(get_some_node(y));
	
	Treap *z1 = make_node(x, y);
	Treap *z2 = make_node(y, x);
	
	merge(merge(p, z1), merge(q, z2));
	gr[x].insert(y);
	gr[y].insert(x);
}

void cut(int x, int y) {
	make_root(x);
	
	Treap *a = get_node[{x, y}];
	Treap *b = get_node[{y, x}];
	
	Treap *l, *m, *r;
	int pos1 = get_sz_left(a), pos2 = get_sz_left(b);
	split(get_root(a), l, m, pos1);
	split(m, m, r, pos2 - pos1 + 1);
	
	Treap *trash;
	split(m, trash, m, 1);
	
	get_node[{trash->x, trash->y}] = NULL;
	
	split(m, m, trash, m->sz - 1);
	
	get_node[{trash->x, trash->y}] = NULL;
	
	gr[x].erase(y);
	gr[y].erase(x);
}

bool is_connected(int u, int v) {
	if (u == v)
		return true;
	if (get_some_node(u) == NULL)
		return false;
	if (get_some_node(v) == NULL)
		return false;
	return get_root(get_some_node(u)) == get_root(get_some_node(v));
}

int n;

void print() {
	int maxsz = -1, pi = -1, pj = -1;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			if (get_node[{i, j}] != NULL && maxsz < get_node[{i, j}]->sz) {
				maxsz = get_node[{i, j}]->sz;
				pi = i, pj = j;
			}
	print_tree(get_node[{pi, pj}]);
}

int main() {
	//freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);
	
	int m; cin >> n >> m;
	for (int kek = 0; kek < m; kek++) {
		string s; cin >> s;
		if (s == "make_root") {
			int v; cin >> v; v--;
			make_root(v);
		} else if (s == "cut") {
			int u, v; cin >> u >> v; u--, v--;
			cut(u, v);
		} else if (s == "link") {
			int u, v; cin >> u >> v; u--, v--;
			link(u, v);
		} else if (s == "get") {
			int u, v; cin >> u >> v; u--, v--;
			cout << is_connected(u, v);
		}
		
		
		/*print();
		cout << endl;*/
	}
	
	cout << endl;
	
	return 0;
}
