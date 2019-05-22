#include <bits/stdc++.h>
#define ll long long
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

#define TASK "fastfood"

const int dd = 1500 + 7;
int A[dd][dd];
int dp[dd][dd], dpR[dd][dd];
int ans[2 * dd];

void upd(int &a, int b) {
	if (a < b)
		a = b;
}

struct FenTree {
	int T[dd], P[dd];
	int tmm = 1;
	
	inline void clear() { tmm++; }
	
	inline void upd(int v, int val) {
		for (int i = v + 1; i < dd; i += (i&-i)) {
			if (P[i] != tmm)
				T[i] = 0, P[i] = tmm;
				
			if (T[i] < val)
				T[i] = val;
		}
	}
	
	inline int get(int v) {
		int res = 0;
		for (int i = v + 1; i; i -= (i&-i)) {
			if (P[i] != tmm)
				T[i] = 0, P[i] = tmm;
				
			if (res < T[i])
				res = T[i];
		}
		return res;
	}
} F;

vector<pair<int, int> > E[dd * dd];

void calc(int color) {
	F.clear();
	sort(E[color].begin(), E[color].end());
	for (pair<int, int> c : E[color]) {
		int x = c.first, y = c.second;	
		dp[x][y] = F.get(y) + 1;
		F.upd(y, dp[x][y]);
	}
}

int n;

void calcR(int color) {
	F.clear();
	sort(E[color].begin(), E[color].end());
	for (pair<int, int> : E[color]) {
		int x = c.first, y = c.second;	
		dpR[n + 1 - x][n + 1 - y] = F.get(y) + 1;
		F.upd(y, dpR[n + 1 - x][n + 1 - y]);
	}
}


int main() {
#ifndef HOME
	freopen(TASK".in", "r", stdin), freopen(TASK".out", "w", stdout);
#endif
	scanf("%d", &n);
	
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++) {
			scanf("%d", &A[i][j]);
			E[A[i][j]].push_back({ i, j });
		}

	for (int i = 1; i <= n * n; i++) {
		calc(i);
		for (auto &c : E[i])
			c.first = n + 1 - c.first, c.second = n + 1 - c.second;
		calcR(i);
	}
		
	for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            ans[dp[i][j] + dpR[i][j] - 1]++;
		
	for (int i = 1; i < 2 * n; i++)
		printf("%d ", ans[i]);
	return 0;
}