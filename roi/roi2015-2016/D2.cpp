#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <vector>
#include <set>
#include <map>
#include <bitset>
#include <unordered_map>

using namespace std;

int solve();

#define TASK "typing"

typedef long long ll;

#define forn(i, n) for (int i = 0; i < n; i++)
#define fornn(i, q, n) for (int i = q; i < n; i++)
#define all(v) v.begin(), v.end()
#define mp make_pair

int main() {
#ifdef KAZAN
	freopen("input.txt", "r", stdin), freopen("output.txt", "w", stdout);
#else
	freopen(TASK".in", "r", stdin), freopen(TASK".out", "w", stdout);
#endif
	solve();
	return 0;
}

const int dd = 3e5 + 7;

ll dp[dd];

map<pair<int, int>, int> M[dd];
ll P[dd], P2[dd];

const ll mod = 1e9 + 3;
const ll mod2 = 1e9 + 11;
const ll p = 3;

int solve() {
	P[0] = 1;
	P2[0] = 1;

	forn(i, dd - 1)
		P[i + 1] = P[i] * p % mod;

	forn(i, dd - 1)
		P2[i + 1] = P2[i] * p % mod2;

	dp[0] = 0;

	int m, n, L;
	cin >> m >> n >> L;
	string t;
	cin >> t;

	forn(i, n) {
		int c;
		cin >> c;

		string s;
		cin >> s;

		ll hh = 0;
		ll hh2 = 0;
		forn(i, s.size()) {
			hh = (hh * p + s[i] - '0' + 1) % mod;
			hh2 = (hh2 * p + s[i] - '0' + 1) % mod2;

			if (M[i + 1].count(mp(hh, hh2))) {
				M[i + 1][mp(hh, hh2)] = min(M[i + 1][mp(hh, hh2)], c);
			}
			else {
				M[i + 1][mp(hh, hh2)] = c;
			}
		}


		hh = 0;
		hh2 = 0;
		for (int i = s.size() - 1; i >= 0; i--) {
			hh = (hh + P[s.size() - 1 - i] * (s[i] - '0' + 1)) % mod;
			hh2 = (hh2 + P2[s.size() - 1 - i] * (s[i] - '0' + 1)) % mod2;

			if (M[s.size() - i].count(mp(hh, hh2))) {
				M[s.size() - i][mp(hh, hh2)] = min(M[s.size() - i][mp(hh, hh2)], c);
			}
			else {
				M[s.size() - i][mp(hh, hh2)] = c;
			}
		}
	}


	fornn(i, 1, m + 1) {
		dp[i] = (ll)(1e18 + 7);
		string cur;
		ll hh = 0;
		ll hh2 = 0;

		for (int j = i; j > 0; j--) {
			hh = (hh + P[i - j] * (t[j - 1] - '0' + 1)) % mod;
			hh2 = (hh2 + P2[i - j] * (t[j - 1] - '0' + 1)) % mod2;


			if (M[i - j + 1].count(mp(hh, hh2))) {
				dp[i] = min(dp[i], dp[j - 1] + M[i - j + 1][mp(hh, hh2)]);
			}
		}
	}
	cout << (dp[m] == (ll)(1e18 + 7) ? -1 : dp[m]);
	return 0;
}