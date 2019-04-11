#include <bits/stdc++.h>
#define err(...) //fprintf(stderr, __VA_ARGS__), fflush(stderr)
#include "wiring.h"

using namespace std;

typedef long long ll;

const int dd = (int)1e5 + 1;
unordered_map<int, ll> dp[dd];

void upd(ll &a, ll b) { if (a > b) a = b; }

ll min_total_length(vector<int> r, vector<int> b) {
	int n = (int)r.size(), m = (int)b.size();

	vector<pair<int, int>> A;
	for (int i = 0; i < n; i++) A.push_back({ r[i], 0 });
	for (int i = 0; i < m; i++) A.push_back({ b[i], 1 });
	
	sort(A.begin(), A.end());
	
	vector<ll> P(n + m + 1);
	for (int i = 0; i < n + m; i++) P[i + 1] = P[i] + A[i].first;
	
	vector<int> sz(1);
	for (int i = 0; i < n + m; i++) {
		if (i == 0 || A[i].second != A[i - 1].second) sz.push_back(1);
		else sz.back()++;
	}
	
	int len = (int)sz.size() - 1; 
	
	vector<int> ind(len + 1);
	for (int i = 0; i <= len; i++) ind[i] = (i ? ind[i - 1] : 0) + sz[i];
	
	for (int t = 1; t <= len; t++) {
		for (int q = 0; q <= sz[t]; q++) {
			dp[t][q] = (ll)1e18;
		}
	}
	
	dp[1][sz[1]] = 0;
	
	auto get = [&P](int l, int r) {
		return P[r + 1] - P[l];
	};
	
	for (int t = 1; t <= len; t++) {
		if (t == len) continue;
		for (int q = sz[t] - 1; q >= 0; q--) upd(dp[t][q], dp[t][q + 1] + A[ind[t]].first - A[ind[t] - q - 1].first);
		for (int q = 0; q <= min(sz[t], sz[t + 1]); q++) 
			upd(dp[t + 1][sz[t + 1] - q], dp[t][q] + (q ? get(ind[t], ind[t] + q - 1) - get(ind[t] - q, ind[t] - 1) : 0));
		for (int q = sz[t + 1] - 1; q >= 0; q--) 
			upd(dp[t + 1][q], dp[t + 1][q + 1] + A[ind[t] + sz[t + 1] - q - 1].first - A[ind[t] - 1].first);
	}
	
	return dp[len][0];
}
