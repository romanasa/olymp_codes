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

const ll p = 3;
const ll MM2 = 1e9 + 11;
const int MAXN = 2e5 + 7;

ll a[MAXN], h[MAXN], hr[MAXN], P[MAXN];
ll h2[MAXN], hr2[MAXN], P2[MAXN];

ll get(int l, int r) {
	if (!l)
		return h[r];

	return (h[r] + MM - (h[l - 1] * P[r - l + 1]) % MM) % MM;
}

ll get2(int l, int r) {
	if (!l)
		return h2[r];
	return (h2[r] + MM2 - (h2[l - 1] * P2[r - l + 1]) % MM2) % MM2;
}

ll getr(int l, int r) {
	if (!l)
		return hr[r];

	return (hr[r] + MM - (hr[l - 1] * P[r - l + 1]) % MM) % MM;
}

ll getr2(int l, int r) {
	if (!l)
		return hr2[r];

	return (hr2[r] + MM2 - (hr2[l - 1] * P2[r - l + 1]) % MM2) % MM2;
}

int solve() {
	forn(i, MAXN)
		P[i] = (i > 0 ? (P[i - 1] * p) % MM : 1);
	
	forn(i, MAXN)
		P2[i] = (i > 0 ? (P2[i - 1] * p) % MM2 : 1);

	int t;
	cin >> t;
	while (t--) {
		int n;
		cin >> n;
		memset(a, 0, sizeof(ll) * 2 * n);
		memset(h, 0, sizeof(ll) * 2 * n);
		memset(hr, 0, sizeof(ll) * 2 * n);

		forn(i, n)
			cin >> a[i];

		fornn(i, n, 2 * n)
			a[i] = a[i - n];

		ll hh = 0;
		forn(i, 2 * n)
			h[i] = hh = ((hh * p) % MM + a[i] + 1) % MM;
		
		ll hh2 = 0;
		forn(i, 2 * n)
			h2[i] = hh2 = ((hh2 * p) % MM2 + a[i] + 1) % MM2;

		reverse(a, a + 2 * n);

		hh = 0;
		forn(i, 2 * n)
			hr[i] = hh = ((hh * p) % MM + a[i] + 1) % MM;

		hh2 = 0;
		forn(i, 2 * n)
			hr2[i] = hh2 = ((hh2 * p) % MM2 + a[i] + 1) % MM2;

		bool ok = false;
		for (int i = 0; i < n; i++) {
			int l = i, r = i + n - 1;
			if (get(l, r) == getr(2 * n - r - 1, 2 * n - l - 1) && 
				get2(l, r) == getr2(2 * n - r - 1, 2 * n - l - 1))
				ok = true;
		}

		if (n % 2 == 0) {
			for (int i = 0; i < n - 1; i++) {
				int l = i, r = i + n;
				if (get(l, r) == getr(2 * n - r - 1, 2 * n - l - 1) &&
					get2(l, r) == getr2(2 * n - r - 1, 2 * n - l - 1))
					ok = true;
			}
		}

		cout << (ok ? "Yes\n" : "No\n");
	}
	return 0;
}