#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

vector<vector<int> > E, H, R;

const int dd = (int)2e5 + 7;
const int sz = 500;
const int maxR = 25000 + 1;

int h[dd];
int tin[dd], tout[dd], tmm;

void dfs(int v) {
	tin[v] = tmm++;
	for (int to : E[v])
		dfs(to);
	tout[v] = tmm++;
}

int cnt[maxR];
int cnt2[maxR];

vector<int> Q[dd], G[dd];
int lt[dd], rt[dd];

int calc(int v, int col, int was) {
	if (h[v] != col) cnt2[h[v]] += was;
	
	int t = (h[v] == col);
	for (int to : E[v]) 
		t += calc(to, col, was + (h[v] == col));
		
	if (h[v] != col) cnt[h[v]] += t;
	return t;
} 

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int n, r, q;
	cin >> n >> r >> q;
	
	E.resize(n);
	H.resize(r);
	R.resize(r);
		
	for (int i = 0; i < n; i++) {
		if (i) {
			int p;
			cin >> p;
			E[p - 1].push_back(i);
		}
		cin >> h[i];
		h[i]--;
		H[h[i]].push_back(i);
		R[h[i]].push_back(i);
	}
	
	dfs(0);
	
	for (int i = 0; i < r; i++) {
		sort(H[i].begin(), H[i].end(), [](int a, int b) { return tin[a] < tin[b]; });
		sort(R[i].begin(), R[i].end(), [](int a, int b) { return tout[a] < tout[b]; });
	}
	
	
	for (int i = 0; i < r; i++) {
		if ((int)H[i].size() >= sz) {
			fill(cnt, cnt + r, 0);
			fill(cnt2, cnt2 + r, 0);
			calc(0, i, 0);
			for (int j = 0; j < r; j++) Q[i].push_back(cnt[j]);
			for (int j = 0; j < r; j++) G[i].push_back(cnt2[j]);
		}
	}
	
	while (q--) {
		int r1, r2;
		cin >> r1 >> r2;
		r1--, r2--;
		
		if ((int)G[r1].size()) cout << G[r1][r2] << endl;
		else if ((int)Q[r2].size()) cout << Q[r2][r1] << endl;
		else {
			
			//err("r1 = { "); for (int i : H[r1]) err(" %d,", i); err("}\n");
			//err("r2 = { "); for (int i : H[r2]) err(" %d,", i); err("}\n");
		
			int j = 0;
			for (int v : H[r1]) {
				while (j < (int)H[r2].size() && tin[H[r2][j]] < tin[v]) j++;
				lt[v] = j;
			}
			j = 0;
			for (int v : R[r1]) {
				while (j < (int)H[r2].size() && tin[H[r2][j]] < tout[v]) j++;
				rt[v] = j;
			}
			
			//err("lt = { "); for (int i : H[r1]) err(" %d,", lt[i]); err("}\n");
			//err("rt = { "); for (int i : H[r1]) err(" %d,", rt[i]); err("}\n");
			int ans = 0;
			for (int v : H[r1])
				ans += max(rt[v] - lt[v], 0);
			cout << ans << endl;
		}
	}
	
	return 0;
}