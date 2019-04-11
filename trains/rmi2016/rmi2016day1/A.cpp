#include <bits/stdc++.h>
#define ll long long
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

const int mod = (int)1e9 + 7;

const int dd = (int)1e8 + 1;
int dp[dd];

void add(int &a, int b) {
	a += b;
	if (a >= mod) a -= mod;
}
	
int m, n, k, f;

struct matr {
	int **T;
	matr() { 
		T = new int*[k]; 
		for (int i = 0; i < k; i++) {
			T[i] = new int[k];
		}
		for (int i = 0; i < k; i++) for (int j = 0; j < k; j++) T[i][j] = 0;
	}
};

matr mul(matr &a, matr &b) {
	matr c;
	for (int i = 0; i < k; i++) {
		for (int j = 0; j < k; j++) {
			for (int t = 0; t < k; t++) {
				add(c.T[i][j], 1ll * a.T[i][t] * b.T[t][j] % mod);
			}
		}
	}
	return c;
}

matr bp(matr a, int n) {
	matr Q = a;
	matr res;
	for (int i = 0; i < k; i++) res.T[i][i] = 1;
	for (; n; n >>= 1) {
		if (n & 1) res = mul(res, Q);
		Q = mul(Q, Q);
	}
	return res;
}

int main() {
	scanf("%d %d %d %d", &m, &n, &k, &f);
	n++;
	
	int cnt1 = 0, cnt0 = 0;
	for (int i = 0; i < (1 << m); i++) {
		if (__builtin_popcount(i) >= f) cnt1++;
		else cnt0++;
	}	
	
	if (k <= 100) {
		n--;
		
		matr A;
		A.T[0][0] = 1;
		
		matr G;
		for (int i = 0; i < k; i++) G.T[i][0] = cnt1;
		for (int i = 1; i < k; i++) G.T[i - 1][i] = cnt0;
		
		G = bp(G, n);
		A = mul(A, G);
			
		int ans = 0;
		for (int i = 0; i < k; i++) {
			//err("T[0][%d] = %d\n", i, A.T[0][i]);
			add(ans, A.T[0][i]);
		}
		
		printf("%d\n", ans);
		return 0;
	}
	
	int p = 1;
	for (int i = 0; i < k; i++) p = 1ll * p * cnt0 % mod;
	
	dp[0] = 1;
	
	int cur = dp[0];
	
	for (int i = 1; i <= n; i++) {
		dp[i] = cur;
		if (i < n) dp[i] = 1ll * dp[i] * cnt1 % mod;
		cur = (1ll * cur * cnt0 + dp[i]) % mod;
		if (i >= k) {
			cur -= 1ll * dp[i - k] * p % mod;
			if (cur < 0) cur += mod;
		}
		//err("dp[%d] = %d\n", i, dp[i]);
	}
	printf("%d\n", dp[n]);
	return 0;
}