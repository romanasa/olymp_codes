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

typedef long long ll;

#define TASK "o"
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stdout);
#define all(v) v.begin(), v.end()

int solve();

int main() {
#ifdef HOME
	//freopen("input.txt", "r", stdin), freopen("output.txt", "w", stdout);
#else
	//if (TASK != "")
	//freopen(TASK".in", "r", stdin), freopen(TASK".out", "w", stdout);
#endif
	solve();
	return 0;
}

const int dd = 2007;

vector<pair<int, int> > E[dd];

const int maxC = 50 * 100;

int dp[57][57][5007];
int p[57][57][5007];
int T[5007][5007], S[57][57];

int n, c;

void rec(int x, int y) {
	for (int i = 1; i <= c; i++) {
		vector<int> ans;
		int a = x, b = y;
		int k = (int)E[i].size();

		while (k) {
			if (p[i][k][a] == 1) {
				a -= E[i][k - 1].first;
				ans.push_back(E[i][k - 1].second);
			} else {
				b -= E[i][k - 1].first;
			}

			k--;
		}

		for (int x : ans)
			printf("%d ", x);
	}
}

int solve() {
	scanf("%d %d", &n, &c);

	for (int i = 0; i < n; i++) {
		int a, b;
		scanf("%d %d", &a, &b);
		E[b].push_back({ a, i + 1 });
	}


	for (int i = 1; i <= c; i++) {
		dp[i][0][0] = 1;
		
		int s = 0;
		for (int k = 0; k < (int)E[i].size(); k++) {
			
			if (k)
				s += E[i][k - 1].first;
			if (k)
				S[i][k - 1] = s;
			
			for (int a = 0; a <= maxC; a++) {
				int b = s - a;
				
				if (a + E[i][k].first <= maxC && !dp[i][k + 1][a + E[i][k].first]) {
					dp[i][k + 1][a + E[i][k].first] = 1;
					p[i][k + 1][a + E[i][k].first] = 1;
				}
				
				if (b + E[i][k].first <= maxC && !dp[i][k + 1][a]) {
					dp[i][k + 1][a] = 1;
					p[i][k + 1][a] = 2;
				}
			}
		}
		s += E[i].back().first;
		S[i][(int)E[i].size()] = s;

		for (int a = 0; a <= s; a++) {
			int b = s - a;
			if (dp[i][(int)E[i].size()][a])
				T[a][b]++;
		}
	}

	for (int a = 1; a <= maxC; a++) {
		for (int b = 1; b <= maxC; b++) {
			if (T[a][b] == c) {
				puts("YES");
				rec(a, b);
				return 0;
			}
		}
	}
	puts("NO");
	return 0;
}