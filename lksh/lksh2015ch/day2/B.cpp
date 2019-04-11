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
typedef double ld;

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

struct pt{
	ld x, y;
};


ld dist(pt a, pt b) {
	return sqrt((b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y));
}

const int MAXN = 1e5 + 7;
int is[MAXN];

int solve() {
	int n, k;
	ld l;
	cin >> n >> l >> k;
	vector<int> broke(k);
	vector<pt> p(n);

	forn(i, k) {
		cin >> broke[i];
		broke[i]--;
		is[broke[i]] = true;
	}

	forn(i, n) {
		cin >> p[i].x >> p[i].y;
	}

	int j = 0;
	ld len = 0, per = 0, curl = 0, ans = 0, res = 0;

	forn(i, k) {
		len += dist(p[broke[i]], p[(broke[i] + 1) % n]);
	}
	forn(i, n) {
		per += dist(p[i], p[(i + 1) % n]);
	}
	if (l >= per) {
		cout << 0;
		exit(0);
	}

	forn(i, n) {
		if (!curl)
			j = i;

		while (curl + dist(p[j], p[(j + 1) % n]) <= l) {
			curl += dist(p[j], p[(j + 1) % n]);
			if (is[j])
				ans += dist(p[j], p[(j + 1) % n]);
			j = (j + 1) % n;
		}

		if (is[j])
			ans += (l - curl);
		res = max(ans, res);
		if (is[j])
			ans -= (l - curl);

		if (is[i])
			ans -= dist(p[i], p[(i + 1) % n]);
		curl -= dist(p[i], p[(i + 1) % n]);
	}

	printf("%.10f", len - res);
	return 0;
}