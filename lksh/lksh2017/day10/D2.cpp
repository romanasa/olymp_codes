#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

const int dd = (int)2e5 + 1;

const int MAXMEM = (int)2e8;
char MEM[MAXMEM];
int mpos;

inline void* operator new (size_t n) {
	char *res = MEM + mpos;
	mpos += n;
	return (void*)res;
}

inline void operator delete(void*) {}

struct Tree {
	
    vector<vector<int> > E;
	vector<int> tin, tout;
	int tmm;
	
	void read(int n) {
		E.resize(n), tin.resize(n), tout.resize(n);
		for (int i = 1; i < n; i++) {
    		int p;
    		scanf("%d", &p);
    		E[p - 1].push_back(i);
    	}
	}

    void dfs(int v) {
    	tin[v] = tmm++;
    	for (int to : E[v]) {
    		dfs(to);
    	}
    	tout[v] = tmm++;
	}
} A, B;

vector<int> T[8 * dd];
int Q[2 * dd];

void build(int v, int tl, int tr) {
	T[v].resize(tr - tl + 1);
	if (tl == tr) {
		T[v][0] = Q[tl];
	} else {
		int tm = (tl + tr) / 2;
		build(v * 2, tl, tm);
		build(v * 2 + 1, tm + 1, tr);
		merge(T[v * 2].begin(), T[v * 2].end(), T[v * 2 + 1].begin(), T[v * 2 + 1].end(), T[v].begin());
	}
}

int get(int v, int tl, int tr, int l, int r, int x, int y) {
	if (tl == l && tr == r) {
		return upper_bound(T[v].begin(), T[v].end(), y) - lower_bound(T[v].begin(), T[v].end(), x);
	}
	int tm = (tl + tr) / 2;
	if (r <= tm) return get(v * 2, tl, tm, l, r, x, y);
	if (l > tm) return get(v * 2 + 1, tm + 1, tr, l, r, x, y);
	return get(v * 2, tl, tm, l, tm, x, y) + get(v * 2 + 1, tm + 1, tr, tm + 1, r, x, y);
}

int main() {
	int n;
	scanf("%d", &n);

	A.read(n);
	B.read(n);

	A.dfs(0);
	B.dfs(0);

	fill(Q, Q + 2 * n, -1);
	
	for (int i = 0; i < n; i++) Q[A.tin[i]] = B.tin[i];
	
	build(1, 0, 2 * n);
	
	for (int i = 0; i < n; i++) {
		int cur = get(1, 0, 2 * n, A.tin[i], A.tout[i], B.tin[i], B.tout[i]);
		printf("%d ", cur - 1);
	}
	
	return 0;
}