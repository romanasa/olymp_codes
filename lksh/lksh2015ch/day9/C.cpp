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

int A[2007][2007];
ll dp[17][2007];

int solve() {
	int n, m;
	cin >> n >> m;
	if (n > m)
		swap(n, m);

	forn(i, 1 << n)
		forn(j, 1 << n) {
			if (i & j) continue;
			int msk = i | j, cur = 0, ok = 1;

			forn(k, n) 
				if (msk & (1 << k)) {
					if (cur % 2)
						ok = false;
					cur = 0;
				}
				else 
					cur++;
			
			if (cur % 2 == 0 && ok)
				A[i][j] = 1;
		}

	dp[0][0] = 1;
	fornn(i, 1, m + 1)
		forn(j, 1 << n)
			forn(k, 1 << n)
				dp[i][k] += dp[i - 1][j] * A[j][k];
	cout << dp[m][0];
	return 0;
}