#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <set>
#include <map>
#include <bitset>
#include <string>
#include <fstream>
#include <vector>
#include <cstring>
#include <cassert>

using namespace std;

typedef long long ll;
typedef double ld;

int solve();

#define TASK "fuel"
#define err(...) //fprintf(stdout, __VA_ARGS__), fflush(stdout)

int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin), freopen("output.txt", "w", stdout);
#else
    //freopen(TASK".in", "r", stdin), freopen(TASK".out", "w", stdout);
#endif
    solve();
}

const int dd = (int)707;

char s[dd], t[dd], ans[dd];
short dp[2][dd][dd];
bitset<dd> p[dd][dd], g[dd][dd];

inline int get(char c) {
	return c == '(' ? 1 : -1;
}

int solve() {
	scanf("%s", s);
	int n = strlen(s);
	scanf("%s", t);
	int m = strlen(t);

	int mbal = min(m, n);

	for (int i = 0; i < 2; i++)
		for (int j = 0; j <= m; j++)
			for (int bal = 0; bal <= mbal; bal++)
				dp[i][j][bal] = -1000;

	dp[0][0][0] = 0;

	for (int i = 0; i <= n; i++) {

		int cur = i & 1;
		int nxt = cur ^ 1;

		for (int j = 0; j <= m; j++)
			for (int bal = 0; bal <= mbal; bal++)
				dp[nxt][j][bal] = -1000;

		for (int j = 0; j <= m; j++) {
			for (int bal = 0; bal < mbal; bal++) {

				if (dp[cur][j][bal] == -1000) continue;

				if (i < n && j < m && s[i] == t[j] && bal + get(s[i]) >= 0) {
					if (dp[nxt][j + 1][bal + get(s[i])] < dp[cur][j][bal] + 1) {
						dp[nxt][j + 1][bal + get(s[i])] = dp[cur][j][bal] + 1;
						g[i + 1][j + 1][bal + get(s[i])] = 1;
					}
				}

				if (i < n) {
					if (dp[nxt][j][bal] < dp[cur][j][bal]) {
						dp[nxt][j][bal] = dp[cur][j][bal];
						p[i + 1][j][bal] = 0;
					}
				}
				if (j < m) {
					if (dp[cur][j + 1][bal] < dp[cur][j][bal]) {
						dp[cur][j + 1][bal] = dp[cur][j][bal];
						p[i][j + 1][bal] = 1;
					}
				}

			}
		}
	}

	int pos = dp[n & 1][m][0];
	int i = n, j = m, bal = 0;
	while (i > 0 && j > 0) {

		err("%d %d %d\n", i, j, bal);
		err("dp = %d\n", dp[i][j][bal]);


		if (g[i][j][bal]) {

			err("1\n");

			ans[--pos] = s[i - 1];
			bal -= get(s[i - 1]);
			i--, j--;
		} else {
			if (p[i][j][bal] == 0) {
				i--;
				err("2\n");
			} else {
				j--;
				err("3\n");
			}
		}
	}
	printf("%s", ans);
    return 0;
}