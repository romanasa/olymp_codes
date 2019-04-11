#include <cstdio>
#include <cstdlib>
#include <vector>
#include <set>
#include <map>
#include <algorithm>

#include "grader.h"

using namespace std;

typedef long long ll;

vector<set<int> > E;
const int dd = 1e5 + 7;

int col[dd], cnt[dd];
ll S[dd], SS, G[dd];
ll ans;

void dfs(int v, int pr) {
	S[v] = cnt[v];
	G[v] = 0;
	for (int to : E[v]) {
		if (to != pr) {
			dfs(to, v);
			S[v] += S[to];
			G[v] += S[to] + G[to];
		}
	}
	SS += cnt[v];
}

void calc(int v, int pr, ll cur) {
	ans += 1ll * cur * cnt[v];
	for (int to : E[v]) {
		if (to != pr) {
			ll t = cur - S[to] + (SS - S[to]);
			calc(to, v, t);
		}
	}
}


ll get(vector<pair<int, int> > A) {
	int n = (int)A.size();

	fill(G, G + n, 0);
	fill(S, S + n, 0);
	fill(cnt, cnt + n, 0);
	fill(col, col + n, 0);
	SS = 0;

	sort(A.begin(), A.end());

	int c = 0;

	for (int i = 0; i < n; i++) {
		if (i > 0 && (A[i].first != A[i - 1].first || A[i].second != A[i - 1].second + 1))
			c++;
		col[i] = c;
		cnt[c]++;
	}

	c++;

	E.resize(0);
	E.resize(c);

	vector<int> P(n);
	for (int i = 0; i < n; i++)
		P[i] = i;

	sort(P.begin(), P.end(), [&A](int a, int b) { return (A[a].second == A[b].second ? A[a].first < A[b].first : A[a].second < A[b].second);});

	for (int j = 1; j < n; j++) {
		int a = P[j], b = P[j - 1];
		if (A[a].second == A[b].second && A[a].first == A[b].first + 1)
			E[col[a]].insert(col[b]), E[col[b]].insert(col[a]);
	}
	dfs(0, -1);
	calc(0, -1, G[0]);
	return 0;
}

int DistanceSum(int N, int *X, int *Y) {
	vector<pair<int, int> > A(N);
	for (int i = 0; i < N; i++)
		A[i] = { X[i], Y[i] };

	get(A);

	for (int i = 0; i < N; i++)
		swap(A[i].first, A[i].second);

	get(A);
	int mod = (int)1e9;
	return (ans / 2) % mod;

}
