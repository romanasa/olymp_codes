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
#include <unordered_set>

using namespace std;

typedef unsigned long long ull;
typedef long long ll;
typedef long double ld;

#define forn(i, n) for (ll i = 0; i < (ll)n; i++)
#define fornn(i, q, n) for (ll i = q; i < (ll)n; i++)
#define mp make_pair
#define pk push_back
#define all(v) v.begin(), v.end()
#define times clock() * 1.0 / CLOCKS_PER_SEC

#define TASK "makeintihappy"

const double eps = 1e-7;
const double pi = acos(-1.0);

const int inf = (int)2e9 + 1;
const ll linf = (ll)9e18 + 7;
const ll MM = (ll)1e9 + 7;

int solve();
void gen();

int main() {
#ifdef _DEBUG
	freopen("input.txt", "r", stdin), freopen("output.txt", "w", stdout);
#else
	freopen(TASK".in", "r", stdin), freopen(TASK".out", "w", stdout);
	//freopen("input.txt", "r", stdin), freopen("output.txt", "w", stdout), freopen("test.txt", "w", stderr);
#endif
	solve();
	return 0;
}

ll dp[1007][1007], a[1007][1007];
int ans[1007][1007];
int h, w;

void go(int v, ll msk, ll k) {
	if (v == w) {
		return;
	}
	forn(i, 1 << h) {
		if (a[msk][i]) {
			int ind = w - v;
			if (k > 0 && dp[ind][i] >= k) {
				forn(j, h)
					ans[h - j - 1][v] = ((i & (1 << j)) > 0);
				go(v + 1, i, k);
			}
			k -= dp[ind][i];
		}
	}
}

int solve() {
	ll k;
	cin >> h >> w >> k;
	if (h > w)
		swap(w, h);

	forn(i, (1 << h) + 2) {
		if (i < (1 << h))
			forn(j, (1 << h) + 2) {

			if (j < (1 << h)) {
				bool ok = true;
				forn(k, h - 1) {
					if ((i & (1 << k)) && (j & (1 << k)) &&
						(i & (1 << (k + 1))) && (j & (1 << (k + 1))))
						ok = false;
					if ((i & (1 << k)) == 0 && (j & (1 << k)) == 0 &&
						(i & (1 << (k + 1))) == 0 && (j & (1 << (k + 1))) == 0)
						ok = false;
				}
				a[i][j] = ok;
			}
			else
				a[i][j] = (j != (1 << h));
		}
		else {
			forn(j, (1 << h))
				a[i][j] = (i == (1 << h));
		}
	}

	dp[0][1 << h] = 1;

	fornn(i, 1, w + 2) 
		forn(j, (1 << h) + 2)
			forn(k, (1 << h) + 2) {
				dp[i][k] += dp[i - 1][j] * a[j][k];
				if (dp[i][k] > 1e18)
					dp[i][k] = 1e18 + 1;
			}

	go(0, (1 << h), k);

	forn(i, h) {
		forn(j, w)
			cout << (ans[i][j] ? 'b' : 'w');
		cout << "\n";
	}
	return 0;
}