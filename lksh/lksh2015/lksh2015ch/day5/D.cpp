#define _CRT_SECURE_NO_WARNINGS
#pragma comment(linker, "/STACK:66777216")
#include <iostream>
#include <cstdio>
#include <cmath>
#include <vector>
#include <ctime>
#include <map>
#include <set>
#include <string>
#include <queue>
#include <deque>
#include <cassert>
#include <cstdlib>
#include <bitset>
#include <algorithm>
#include <string>
#include <list>
#include <fstream>
#include <cstring>

using namespace std;

typedef unsigned long long ull;
typedef long long ll;
typedef long double ld;

#define forn(i, n) for (int i = 0; i < (int)n; i++)
#define fornn(i, q, n) for (int i = q; i < (ll)n; i++)
#define mp make_pair
#define pk push_back
#define all(v) v.begin(), v.end()
#define times clock() * 1.0 / CLOCKS_PER_SEC
#define prev pprev

#define TASK "sum2"

const double eps = 1e-7;
const double pi = acos(-1.0);

const ll INF = (ll)2e9 + 1;
const ll LINF = (ll)8e18;
const ll inf = (ll)2e9 + 1;
const ll linf = (ll)8e18;
const ll MM = (ll)1e9 + 7;

int solve();
void gen();

int main()
{
#ifdef _DEBUG
	freopen("input.txt", "r", stdin), freopen("output.txt", "w", stdout);
#else
	//freopen(TASK".in", "r", stdin), freopen(TASK".out", "w", stdout);
	//freopen("input.txt", "r", stdin), freopen("output.txt", "w", stdout), freopen("test.txt", "w", stderr);
#endif
	solve();
	return 0;
}

const int MAXN = 1e5 + 7;

int dp[17][MAXN], tin[MAXN], tout[MAXN], beg[MAXN], ans[MAXN], cl[MAXN], cb[MAXN];

int tmm = 1, n, res = 0;

vector<vector<int> > e;

void dfs(int v, int pr = -1) {
	tin[v] = tmm++;
	if (!v) {
		forn(i, 17)
			dp[i][v] = 0;
	}
	else {
		dp[0][v] = pr;
		for (int i = 1; i < 17; i++) {
			dp[i][v] = dp[i - 1][dp[i - 1][v]];
		}
	}

	for (int i = 0; i < e[v].size(); i++) {
		int to = e[v][i];
		if (to != pr)
			dfs(to, v);
	}
	tout[v] = tmm++;
}

bool is(int a, int b) {
	return tin[a] <= tin[b] && tout[b] <= tout[a];
}

int countl(int v, int pr = -1) {
	for (int i = 0; i < e[v].size(); i++) {
		int to = e[v][i];
		if (to != pr)
			cl[v] += countl(to, v);
	}
	cl[v] += ans[v];
	return cl[v];
}

int countb(int v, int pr = -1) {
	for (int i = 0; i < e[v].size(); i++) {
		int to = e[v][i];
		if (to != pr)
			cb[v] += countb(to, v);
	}
	cb[v] += beg[v];
	return cb[v];
}

void check(int v, int pr = -1) {
	for (int i = 0; i < e[v].size(); i++) {
		int to = e[v][i];
		if (pr != to) {
			check(to, v);
			if (cl[to] * 2 == cb[to])
				res++;
		}
	}
}

int solve() {
	scanf("%d", &n);

	e.resize(n);

	forn(i, n - 1) {
		int a, b;
		scanf("%d%d", &a, &b);
		e[a - 1].pk(b - 1);
		e[b - 1].pk(a - 1);
	}
	dfs(0);

	int m;
	scanf("%d", &m);
	forn(i, m) {
		int a, b;
		scanf("%d%d", &a, &b);
		a--, b--;

		beg[a]++, beg[b]++;

		int lca = a;

		if (is(a, b)) {
			lca = a;
		}
		else if (is(b, a)) {
			lca = b;
		}
		else {
			for (int k = 16; k >= 0; k--) {
				if (!is(dp[k][lca], b))
					lca = dp[k][lca];
			}

			lca = dp[0][lca];
		}

		ans[lca]++;

	}
	countb(0);
	countl(0);
	check(0);

	printf("%d", res);
	return 0;
}