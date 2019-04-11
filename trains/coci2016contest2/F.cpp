#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

const int dd = 401;

bitset<(1 << 22) + 1> dp[401];

vector<vector<int> > E, T;

int in[dd], out[dd];
int h[dd];
int cur;
int n, k;

void dfs(int v, int pr = -1) {
	int ok = 1;
	in[v] = cur;
	h[v] = (pr == -1 ? 0 : h[pr] + 1);
	
	if (h[v] < k) for (int to : E[v]) if (to != pr) {
		ok = 0;
		dfs(to, v);
	}
	
	if (h[v] == k) cur++;
	out[v] = cur;
}

int main() {
	cin >> n >> k;
	
	
	if (k * k >= n) {
		return 0 * puts("DA");
	}
	
	E.resize(n);
	T.resize(n);
	
	for (int i = 0; i + 1 < n; i++) {
		int a, b;
		cin >> a >> b;
		E[a - 1].push_back(b - 1);
		E[b - 1].push_back(a - 1);
	}
	
	for (int i = 0; i < n; i++) in[i] = -1;
	dfs(0);

	for (int i = 1; i < n; i++) if (in[i] != -1) {
		T[in[i]].push_back(i);		
	}
	
	dp[0][0] = 1;
	
	for (int i = 0; i < cur; i++) {
		for (int msk = 0; msk < (1 << k); msk++) if (dp[i][msk]) {
		
			//err("i = %d, msk = %d\n", i, msk);
    		for (int p : T[i]) {
    			//err("p = %d\n", p);
    			if (((msk >> (h[p] - 1)) & 1) == 0) {
  					dp[out[p]][msk | (1 << (h[p] - 1))] = 1;
      			}
    		}
		}
	}

	if (dp[cur].count()) puts("DA");
	else puts("NE");
	
	return 0;
}