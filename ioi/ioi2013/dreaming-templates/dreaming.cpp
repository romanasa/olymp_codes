#include "grader.h"

#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int dd = (int)1e5 + 7;
const int inf = (int)1e9 + 1;

vector<vector<pair<int, int> > > E;

int used[dd];
int R[dd], G[dd];
int ans;

int calc(int v, int pr = -1) {
	G[v] = 0;
	for (auto c : E[v]) {
		if (pr != c.first)
			G[v] = max(G[v], c.second + calc(c.first, v));
	}
	return G[v];
}

void upd(pair<int, int> &a, int c) {
	if (c > a.first) {
		a.second = a.first;
		a.first = c;
	} else if (c > a.second) {
		a.second = c;
	}
}

void dfs(int v, int col, int dist = 0) {
	used[v] = true;
	
	int cur = dist;
	pair<int, int> mx(0, 0);

	for (auto c : E[v]) {
		if (used[c.first]) continue;
		cur = max(cur, G[c.first] + c.second);
		upd(mx, G[c.first] + c.second);
	}

	for (auto c : E[v]) {
		if (used[c.first]) continue;

		int t = max(dist, (mx.first == G[c.first] + c.second ? mx.second : mx.first)) + c.second;

		dfs(c.first, col, t);
	}

	R[col] = min(R[col], cur);
}

int s, maxd;

void dfs1(int v, int d, int pr) {
	if (d > maxd) {
		maxd = d;
		s = v;
	}
	
	for (auto c : E[v]) {
		if (c.first != pr)
			dfs1(c.first, d + c.second, v);
	}
}

void upd(int i) {
	s = 0, maxd = -1;
	dfs1(i, 0, -1);
	int t = s;
	
	s = 0, maxd = -1;
	dfs1(t, 0, -1);
	ans = max(ans, maxd);
}

int travelTime(int N, int M, int L, int A[], int B[], int T[]) {
	E.resize(N);

	for (int i = 0; i < M; i++) {
		E[A[i]].push_back({ B[i], T[i] });
		E[B[i]].push_back({ A[i], T[i] });
	}

	fill(R, R + N, inf);

	int c = 0;
	for (int i = 0; i < N; i++) {
		if (!used[i]) {
			upd(i);
			calc(i);
			dfs(i, c);
			c++;
		}
	}
	sort(R, R + c);
	reverse(R, R + c);

	if (c > 1)
		ans = max(ans, R[0] + R[1] + L);
	if (c > 2)
		ans = max(ans, R[1] + R[2] + L + L);

	return ans;
}