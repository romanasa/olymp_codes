#include <bits/stdc++.h>
#define ll long long
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

const int dd = (int)1e5 + 7;
int a[dd];
int l[dd], r[dd], P[dd];

const int mod = (int)1e9 + 7;
const int LOG = 30;

void add(int &a, int b) {
	a += b;
	if (a >= mod) a -= mod;
}

const int maxS = (int)1e5 * 30 * 2 + 7;

int go[maxS][2];
int sum[maxS];

int nv = 0;

struct Trie {
	int root;
	
	Trie() { root = nv++; }
	
	void upd(int x, int val) {
		//err("add (%d, %d)\n", x, val);
		int cur = root;
		add(sum[root], val);
		for (int i = 0; i < LOG; i++) {
			int t = (x >> (LOG - i - 1)) & 1;
			if (go[cur][t] == -1) go[cur][t] = nv++;
			cur = go[cur][t];
			add(sum[cur], val);
		}
	}
	
	int countL(int q, int L) {
		//err("countL %d, %d, ", q, L);
		int cur = root;
		int res = 0;
		for (int i = 0; i < LOG; i++) {
			int t = (q >> (LOG - i - 1)) & 1;
			int l = (L >> (LOG - i - 1)) & 1;
			if (l == 1 && go[cur][t] != -1) add(res, sum[go[cur][t]]);
			if (go[cur][l ^ t] == -1) break;
			cur = go[cur][l ^ t];
		}
		//err("res = %d\n", res);
		return res;
	}
	
	int countR(int q, int R) {
		//err("countR %d, %d, ", q, R);
		int cur = root;
		int res = 0;
		for (int i = 0; i < LOG; i++) {
			int t = (q >> (LOG - i - 1)) & 1;
			int r = (R >> (LOG - i - 1)) & 1;
			if (r == 0 && go[cur][t ^ 1] != -1) add(res, sum[go[cur][t ^ 1]]);
			if (go[cur][r ^ t] == -1) break;
			cur = go[cur][r ^ t];
		}
		//err("res = %d\n", res);
		return res;
	}
};

#define TASK "xor"

int main() {
	for (int i = 0; i < maxS; i++) go[i][0] = go[i][1] = -1;
	
#ifndef HOME
	freopen(TASK".in", "r", stdin), freopen(TASK".out", "w", stdout);
#endif
	int n, k;
	scanf("%d %d", &n, &k);
	for (int i = 0; i < n; i++) {
		scanf("%d", &a[i]);
		P[i + 1] = P[i] ^ a[i];
	}	
	
	for (int i = 0; i < k; i++) {
		scanf("%d %d", &l[i], &r[i]);
	}
	
	vector<vector<int> > dp(k + 1, vector<int>(n + 1, 0));
	
	dp[0][0] = 1;
	
	for (int t = 1; t <= k; t++) {
		Trie J;
		for (int i = 0; i < n; i++) {
			//err("t = %d, i = %d, ", t, i);
			J.upd(P[i], dp[t - 1][i]);
			//err("ok1");
			dp[t][i + 1] = sum[J.root];
			
			dp[t][i + 1] -= J.countL(P[i + 1], l[t - 1]); if (dp[t][i + 1] < 0) dp[t][i + 1] += mod;
			dp[t][i + 1] -= J.countR(P[i + 1], r[t - 1]); if (dp[t][i + 1] < 0) dp[t][i + 1] += mod;
			
			//err("ok2\n");
		}
		
		/*for (int i = 0; i <= n; i++) {
			err("dp[%d][%d] = %d\n", t, i, dp[t][i]);
		}*/
		
	}
	printf("%d\n", dp[k][n]);
	return 0;
}