#include <cstdio>
#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

const int dd = (int)1e5 + 7;
int dp[dd], nxt[dd];
int p[dd];
pair<int, int> A[dd];
vector<int> E[dd];

int solve(int n, int m, int c, const int* a, const int* b, int* answer) {
	
	for (int i = 0; i < m; i++) A[i] = { min(a[i], b[i]), max(a[i], b[i]) };	
	for (int i = 0; i < m; i++) E[A[i].first].push_back(i);
	
	fill(p, p + n + 2, -1);
	dp[0] = 1;
	
	multiset<int> S1, S2;
	set<int> zero;
	
	for (int i = 1; i <= n + 1; i++) zero.insert(i);
	
	for (int i = 0; i < m; i++) S2.insert(A[i].second);
	
	for (int i = 0; i <= n; i++) {
		
		for (int j : E[i]) {
			S2.erase(S2.find(A[j].second));
			S1.insert(A[j].second + 1);
		}
		if (!dp[i]) continue;
	
		int l = i + 1;
		if (S1.size()) l = max(l, *S1.rbegin());
		//for (int j = 0; j < m; j++) if (A[j].first <= i) l = max(l, A[j].second + 1);
		
		int r = n + 1;
		if (S2.size()) r = min(r, *S2.begin());
		//for (int j = 0; j < m; j++) if (A[j].first > i) r = min(r, A[j].second);
		
		vector<int> del;
		for (auto it = zero.lower_bound(l); it != zero.end() && *it <= r; ++it) {
			dp[*it] = 1, p[*it] = i;
			del.push_back(*it);
		}
		for (int x : del) zero.erase(x);
	}
	
	if (!dp[n + 1]) return 0;
	int pos = p[n + 1];
	while (pos > 0) {
		answer[pos] = c;
		pos = p[pos];
	}
	return 1;
}
