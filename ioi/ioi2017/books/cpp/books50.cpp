#include "books.h"
#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

const int dd = (int)1e6 + 1;

int l, r;
int used[dd];

void dfs(int v, vector<int> &p) {
	used[v] = 1;
	l = min(l, v);
	r = max(r, v);
	if (!used[p[v]]) dfs(p[v], p);
}

ll minimum_walk(vector<int> p, int s) {
	int n = (int)p.size();
	
	ll ans = 0;
	int maxL = -1;
	for (int i = 0; i < n; i++) ans += abs(p[i] - i);
	
	vector<int> B(n);
	for (int i = 0; i < n; i++) {
		if (!used[i]) {
			l = n, r = -1;
			
			dfs(i, p);
			if (l == r) continue;
			
			maxL = max(maxL, l);
			B[l]++, B[r]--;
		}
	}
	
	int bal = 0;
	for (int i = 0; i < n; i++) {
		bal += B[i];
		if (bal == 0 && i < maxL) ans += 2;	
	}
	return ans;
}
