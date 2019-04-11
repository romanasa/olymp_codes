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

#define TASK "elections"

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
	freopen(TASK".in", "r", stdin), freopen(TASK".out", "w", stdout);
	//freopen("input.txt", "r", stdin), freopen("output.txt", "w", stdout), freopen("test.txt", "w", stderr);
#endif
	solve();
	return 0;
}

const int MAXN = 1e5 + 7;
const int MAXC = 5e7;

int a[MAXN];
map<int, int> cnt;

int solve() {
	int n;
	scanf("%d", &n);
	forn(i, n) {
		scanf("%d", a + i);
		cnt[a[i]]++;
	}
	vector<pair<int, int> > b;
	for (map<int, int>::iterator it = cnt.begin(); it != cnt.end(); it++) {
		b.pk(mp(it->second, it->first));
	}
	sort(all(b));
	reverse(all(b));

	int c = min(MAXC / n, (int)cnt.size());
	vector<vector<int> > f(c, vector<int>(n, 0));

	for (int k = 0; ;k++) {
		if (k >= c)
			break;
		forn(i, n) {
			f[k][i] = (i > 0 ? f[k][i - 1] : 0) + (b[k].second == a[i]);
		}
	}

	int m;
	scanf("%d", &m);
	forn(i, m) {
		int l, r, k = 0, ans = 0;
		scanf("%d%d", &l, &r);
		l--, r--;
		if (r - l <= 2 * c) {
			map<int, int> g;
			for (int j = l; j <= r; j++)
				g[a[j]]++, ans = max(ans, g[a[j]]);
		}
		else 
			forn(k, c)
				ans = max(ans, f[k][r] - (l > 0 ? f[k][l - 1] : 0));

		printf("%d\n", ans);
	}
	return 0;
}