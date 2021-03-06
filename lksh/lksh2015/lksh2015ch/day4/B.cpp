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
    
double d[57], p[27], ans[57];
int w[27];

int solve() {
	int n, m, s;
	cin >> n >> m >> s;

	forn(i, m)
		cin >> p[i] >> w[i];

	for (int gg = 0; gg < 20000; gg++) {
		for (int j = 0; j < m; j++)
			for (int i = 1; i <= n; i++) {

				if (i + w[j] > n)
					d[i] = (p[j] / s);
				else
					d[i] = (p[j] / s) * ans[i + w[j]];

				if (i > 0)
					d[i] += (1.0 - p[j] * 1.0 / s) * ans[i - 1];
    
				ans[i] = max(ans[i], d[i]);
			}
	}
	printf("%.10f", ans[n]);
	return 0;
}