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

const int MAXN = 5e4 + 7;

vector<vector<int> > e;

int n, K;
ll dp[47][MAXN], cost[47][MAXN], t[MAXN], sum[MAXN], cnt[MAXN];

void dfs(int v) {
	for (int i = 0; i < e[v].size(); i++) {
		int to = e[v][i];
		dfs(to);
	}

	forn(i, 47)
		forn(j, e[v].size() + 2)
			cost[i][j] = inf;

	cost[0][0] = 0;

	for (int i = 0; i < e[v].size(); i++) {
		int to = e[v][i];
		for (int k = 0; k <= K; k++) {
			if (dp[k][to] == inf)
				break;
			for (int l = 0; k + l <= K; l++) {
				if (cost[l][i] == inf)
					break;
    				cost[k + l][i + 1] = min(cost[k + l][i + 1], cost[l][i] + dp[k][to]);
			}
		}
	}

	
	ll cur = 0, curcost = 0;
	for (int i = 0; i < e[v].size(); i++) {
		int to = e[v][i];
		cur += cnt[to];
		curcost += sum[to];
	}
	cur++;
	curcost += t[v];

	sum[v] = curcost;
	cnt[v] = cur;
    
	for (int i = 0; i <= K; i++)
		dp[i][v] = cost[i][e[v].size()];

	dp[0][v] = 0;

	if (cnt[v] <= K)
		dp[cnt[v]][v] = sum[v];
}

int solve() {
	cin >> n >> K;
	e.resize(n);
	forn(i, n)
		cin >> t[i];
	fornn(i, 1, n) {
		int v;
		cin >> v;
		e[v - 1].pk(i);
	}
	dfs(0);
	cout << dp[K][0];
	return 0;
}