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

using namespace std;

int solve();

#define TASK "video"

typedef long long ll;

#define forn(i, n) for (int i = 0; i < n; i++)
#define fornn(i, q, n) for (int i = q; i < n; i++)
#define all(v) v.begin(), v.end()

int main() {
#ifdef KAZAN
	freopen("input.txt", "r", stdin), freopen("output.txt", "w", stdout);
#else
	freopen(TASK".in", "r", stdin), freopen(TASK".out", "w", stdout);
#endif
	solve();
	return 0;
}

const int dd = 2e3 + 7;

string A[dd];
int P[dd][dd];
int T[dd][dd];

bool check(int i, int j) {
	if (i == 0 || j == 0)
		return false;
	return A[i][j] == A[i - 1][j] && A[i][j] == A[i][j - 1] && A[i][j] == A[i - 1][j - 1];
}

inline int get(int i1, int j1, int i2, int j2) {
	return P[i2][j2] - P[i1 - 1][j2] - P[i2][j1 - 1] + P[i1 - 1][j1 - 1];
}

int solve() {
	int n, m;
	scanf("%d %d", &n, &m);

	forn(i, n) {
		cin >> A[i];
		
		A[i] += A[i];
		A[i + n] = A[i];
	}

	fornn(i, 1, n + n + 1) {
		fornn(j, 1, m + m + 1) {
			P[i][j] = P[i - 1][j] + P[i][j - 1] - P[i - 1][j - 1] + check(i - 1, j - 1);
			T[i][j] = check(i - 1, j - 1);
		}
	}

	int ans = 0;

	fornn(i, 1, n + 1) {
		fornn(j, 1, m + 1) {
			int t = get(i + 1, j + 1, i + n - 1, j + m - 1);
			if (t > ans)
				ans = t;
		}
	}
	cout << ans;
	return 0;
}