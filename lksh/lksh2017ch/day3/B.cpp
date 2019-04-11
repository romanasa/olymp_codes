#include <bits/stdc++.h>
#define err(...) //fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

const int maxK = 107;
const int maxN = (int)2e5 + 1;

ll dp[maxK][maxN];
ll ans = 0;

int A[maxN], K, n;

inline void upd(ll &a, ll b) { if (a < b) a = b; }

void make(int l, int m, int r) {
    for (int x = 0; x <= K; x++) fill(dp[x] + l, dp[x] + r, -(ll)1e18);
    
    dp[1][m - 1] = 0;
    dp[0][m - 1] = A[m - 1];
	for (int x = 0; x <= K; x++) {
		for (int j = m - 1; j >= l; j--) {
			if (j + 1 < m) upd(dp[x][j], dp[x][j + 1] + A[j]);
			if (x > 0) upd(dp[x][j], dp[x - 1][j]);
			if (j + 1 < m && x > 0) upd(dp[x][j], dp[x - 1][j + 1]);
		}
	}
	
	for (int x = 0; x <= K; x++) {
		for (int j = m - 1; j > l; j--) {
			upd(dp[x][j - 1], dp[x][j]);
		}
	}
	
	dp[1][m] = 0;
    dp[0][m] = A[m];
    
    for (int x = 0; x <= K; x++) {
  		for (int j = m; j < r; j++) {
  			if (j > m) upd(dp[x][j], dp[x][j - 1] + A[j]);
  			if (x > 0) upd(dp[x][j], dp[x - 1][j]);
  			if (x > 0 && j > m) upd(dp[x][j], dp[x - 1][j - 1]);
  		}
    }
    
    err("l = %d, m = %d, r = %d\n", l, m, r);
    for (int x = 0; x <= K; x++) for (int j = l; j < r; j++) err("dp[%d][%d] = %I64d\n", x, j, dp[x][j]);
    
    for (int x2 = 0; x2 <= K; x2++) {
    	for (int j = m; j < r; j++) {
    		int x1 = K - x2;
    		int len1 = n - (j - m + 1);
    		if (len1 == 0) continue;
    		if (j - m + 1 <= x2) continue;	
    		int pos = max(m - len1, l);
    		err("len1 = %d, ", len1);
    		err("x2 = %d, j = %d, x1 = %d, pos = %d, val = %I64d\n", x2, j, x1, pos, dp[x2][j] + dp[x1][pos]);
    		
    		upd(ans, dp[x2][j] + dp[x1][pos]);
    	}
    }
    
}

void dfs(int l, int r) {
    if (l + 1 >= r) return;
    int m = (l + r) / 2;
    dfs(l, m);
    dfs(m, r);
	make(l, m, r);
}

int main() {
#ifdef WIN
    freopen("01.in", "r", stdin);
    //freopen("01.out", "w", stdout);
#endif // WIN
    int test;
    scanf("%d", &test);
    while (test--) {
        scanf("%d %d", &n, &K);
        
        for (int i = 0; i < n; i++) scanf("%d", &A[i]);
        for (int i = 0; i < n; i++) A[i + n] = A[i];
        
        ans = -(ll)1e18;
        dfs(0, n);
        make(0, n, 2 * n);
        
        printf("%I64d\n", ans);
    }
}

