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
#include <sstream>
#include <numeric>
#include <unordered_set>

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

#define TASK "king"

const double eps = 1e-7;
const double pi = acos(-1.0);

const ll INF = (ll)2e9 + 1;
const ll LINF = (ll)8e18;
const ll inf = (ll)2e9 + 1;
const ll linf = (ll)2e18;
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

const int dd = 1e3 + 7;

ll e[dd], c[dd], p[dd];
ll dp[dd][dd];

int solve() {
	int n;
	cin >> n;

	forn(i, n)
		cin >> e[i];
	forn(i, n)
		cin >> c[i];
	forn(i, n)
		cin >> p[i];


	ll cure = 0, curp = 0;
	forn(i, n) {
		cure += e[i];
		curp += p[i];
		forn(j, i + 1) {
			dp[i + 1][j] = max(dp[i + 1][j], dp[i][j]);
			
			ll cnt = 0;
			if (cure > curp + j + 1)
				cnt = c[i];

			dp[i + 1][j + 1] = max(dp[i + 1][j + 1], dp[i][j] + cnt);
		}
	}

	cout << *max_element(dp[n], dp[n] + n + 1);
	return 0;
}