#define _CRT_SECURE_NO_DEPRECATE
//#pragma comment (linker, "/STACK:30000000")

//#define debug

#include <string>
#include <vector>
//#include <cmath>
//#include <queue>
//#include <set>
//#include <map>
#include <algorithm>
//#include <iostream>
#include <cstdio>
//#include <sstream>
#include <cassert>
//#include <utility>

using namespace std;

#define EPS 1E-8
const int INF = (int)1E+9;

#define C_IN_FILE "kthmax.in"
#define C_OUT_FILE "kthmax.out"

#define forn(i, n) for (int i = 0; i < (int)(n); ++i)
#define forv(i, v) for (int i = 0; i < (int)(v.size()); ++i)
#define fors(i, s) for (int i = 0; i < (int)(s.length()); ++i)
#define all(a) a.begin(), a.end()
#define pb push_back
#define PII pair<int, int>
#define mp make_pair
#define VI vector<int>
#define VS vector<string>

int n, m, ans;

int Random()
{
	return ((((unsigned int)rand()) << 15) + ((unsigned int)rand()));
}

struct tree {
	int x, y;
	int l, r;
	int k;
	tree() {x = l = r = k = 0; y = Random();};
	tree(int key) {x = key; y = Random(); k = 1; l = r = 0;};
};

int root;
vector<tree> t;

#ifdef debug
VI a;
#endif

void outdata() {
}

inline void norm(int v) {
	t[v].k = t[t[v].l].k + t[t[v].r].k + (int)(v > 0);
}

int merge(int &l, int &r) {
	if (l == 0 || r == 0) return l + r;
	if (t[l].y < t[r].y) {
		t[r].l = merge(l, t[r].l);
		norm(r);
		return r;
	} else {
		t[l].r = merge(t[l].r, r);
		norm(l);
		return l;
	}
}

void split(int v, int key, int &l, int &r) {
	if (v == 0) {
		l = r = 0;
		return ;
	}
	if (t[v].x < key) {
		split(t[v].r, key, t[v].r, r);
		l = v;
	} else {
		split(t[v].l, key, l, t[v].l);
		r = v;
	}
	norm(l); norm(r);
}

void insert(int key) {
	int l, r, m;
	split(root, key, l, r);
	t.pb(tree(key));
	m = (int)t.size() - 1;
	root = merge(l, m);
	root = merge(root, r);
}

void del(int &v, int key) {
#ifdef debug
	assert(v > 0);
#endif
	if (t[v].x == key) {
		v = merge(t[v].l, t[v].r);
	} else {
		if (t[v].x > key) del(t[v].l, key); else del(t[v].r, key);
	}
	norm(v);
}

void del(int key) {
	del(root, key);
}

int find(int &v, int key) {
#ifdef debug
	assert(v > 0);
#endif
	if (t[v].x == key) return v;
	if (t[v].x > key) return find(t[v].l, key); 
		else return find(t[v].r, key);
}

int find(int key) {
	return find(root, key);
}

int findKth(int &v, int k) {
#ifdef debug
	assert(v > 0);
	assert(k <= t[v].k);
#endif
	if (t[t[v].l].k >= k) return findKth(t[v].l, k); else k -= t[t[v].l].k;
	if (k == 1) return v; else --k;
	return findKth(t[v].r, k);
}

int findKth(int k) {
	return findKth(root, k);
}

void init() {
	t.pb(tree());
}

void solve() {
}

void readdata() {
	init();
	scanf("%d", &n);
#ifdef debug
	assert(1 <= n && n <= 100000);
#endif
	forn(i, n) {
		int type, r;
		scanf("%d%d", &type, &r);
		if (type == 0) {
			r = t[root].k - r + 1;
			int ans = t[findKth(r)].x;
#ifdef debug
			assert(t[root].k == (int)a.size());
			assert(1 <= r && r <= (int)t[root].k);
			assert(1 <= r && r <= (int)a.size());
			int ans2 = a[r - 1];
			assert(ans == ans2);
#endif
			printf("%d\n", ans);
			continue;
		}
		if (type == 1) {
#ifdef debug
			assert(!binary_search(all(a), r));
			assert(abs(r) <= 1000000000);
			a.pb(r);
			for(int i = (int)a.size() - 1; i > 0; --i) {
				if (a[i] < a[i - 1]) swap(a[i], a[i - 1]);
			}
#endif
			insert(r);
			continue;
		}
		if (type == -1) {
#ifdef debug
			assert(abs(r) <= 1000000000);
			assert(binary_search(all(a), r));
			a.erase(lower_bound(all(a), r));
#endif
			del(r);
			continue;
		}
#ifdef debug
		assert(false);
#endif
	}
}

int main() {
    freopen(C_IN_FILE, "rt", stdin);
    freopen(C_OUT_FILE, "wt", stdout);
	readdata();
	solve();
	outdata();
	return 0;
}

