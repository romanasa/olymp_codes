#include <cstdio>
#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

vector<vector<pair<int, int> > > E;

struct triple { 
	int a, b, c; 
	bool operator < (triple m) const {
		if (c != m.c) return c < m.c;
		if (a != m.a) return a < m.a;
		return b < m.b;
	}
};
vector<triple> cur;

bool dfs(int v, int t, int pr) {

	if (v == t) return true;
	
	for (auto c : E[v]) if (c.first != pr) {
		cur.push_back({ min(v, c.first), max(v, c.first), c.second });
		if (dfs(c.first, t, v)) return true;
		cur.pop_back();
	}
	return false;
}

const int mod = (int)1e9 + 9;

int calculate(int n, int m, int *a, int *b, int *c) {

	E.resize(n);

	for (int i = 0; i < n - 1; i++) {
		E[a[i] - 1].push_back({ b[i] - 1, c[i] });
		E[b[i] - 1].push_back({ a[i] - 1, c[i] });
	}	
	
	ll ans = 1;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < i; j++) {
			cur.clear();
			
			dfs(i, j, -1);
			
			if (cur.size() == 1) continue;
			
			auto c = *max_element(cur.begin(), cur.end());
			
			int cur = m - c.c;
			if (make_pair(j, i) > make_pair(c.a, c.b)) cur++; 
			
			ans *= cur;
			ans %= mod;
		}
	}
    return (int)ans;
}
