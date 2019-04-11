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

#define TASK "olympiad"

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

short dp[1007][1007];

string s;

string rec(int l, int r) {
	if (l > r)
		return "";
	
	string cur;

	
	if (l == r)
		cur.push_back(s[l]);
	else if (s[l] == s[r]) {
		cur.push_back(s[l]);

		string ans = rec(l + 1, r - 1);

		for (auto c : ans)
			cur.push_back(c);

		cur.push_back(s[r]);
	}
	else if (dp[l][r] == dp[l][r -  1] + 1) {
		cur.push_back(s[r]);


		string ans = rec(l, r - 1);

		for (auto c : ans)
			cur.push_back(c);

		cur.push_back(s[r]);
	}
	else {
		cur.push_back(s[l]);

		string ans = rec(l + 1, r);

		for (auto c : ans)
			cur.push_back(c);

		cur.push_back(s[l]);
	}

	return cur;
}

int solve() {
	cin >> s;

	int n = s.size();

	forn(i, n)
		forn(j, n)
			dp[i][j] = n + 7;

	for (int j = 0; j < n; j++) {
		for (int i = 0; i + j < n; i++) {
			int l = i, r = i + j;

			if (l == r) {
				dp[l][r] = 0;
				continue;
			}

			if (s[l] == s[r]) {
				if (l < r - 1)
					dp[l][r] = min(dp[l][r], dp[l + 1][r - 1]);
				else
					dp[l][r] = 0;
			}

			dp[l][r] = min(dp[l][r], (short)(dp[l][r - 1] + 1));
			dp[l][r] = min(dp[l][r], (short)(dp[l + 1][r] + 1));
		}
	}

	cout << dp[0][n - 1] << "\n";

	cout << rec(0, n - 1);
	return 0;
}
