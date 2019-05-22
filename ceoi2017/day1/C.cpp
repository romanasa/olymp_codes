#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

vector<vector<int> > E;

const int dd = (int)1e6 + 1;
int W[dd];
int par[dd];

void calc(int v, int pr, int cur) {
    int cnt = 0;
	for (int to : E[v]) if (to != pr) {
		cnt++;
	}
	for (int to : E[v]) if (to != pr) {
		calc(to, v, cur + cnt);
	}
	par[v] = pr;
	if (cnt == 0) W[v] = cur;
}

void dfs(int v, int pr, int sz) {
	int cnt = 0;
	for (int to : E[v]) if (to != pr) {
		cnt++;
	}
	for (int to : E[v]) if (to != pr) {
		dfs(to, v, sz + cnt);
	}
	
	if (!cnt) return;
	
	if (cnt == 1) {
		W[v] = sz + 1;
		return;
	} 	
	
	vector<int> cur;
	for (int to : E[v]) if (to != pr) {
		cur.push_back(W[to]);
	}
	sort(cur.rbegin(), cur.rend());	
	//nth_element(cur.begin(), cur.begin() + 1, cur.end());
	W[v] = cur[1];
}

int go(int v, int pr) {
	
	if (W[v] != -1) {
		if (pr == -1) 
	}
	

}

int main() {
	int n, t, m;
	scanf("%d %d %d", &n, &t, &m);
	t--, m--;
	
	E.resize(n);
	
	int ok = 0;
	
	for (int i = 0; i + 1 < n; i++) {
		int a, b;
		scanf("%d %d", &a, &b);
			
		E[a - 1].push_back(b - 1);
		E[b - 1].push_back(a - 1);
		
		ok |= (a - 1 == t && b - 1 == m);
		ok |= (a - 1 == m && b - 1 == t);
	}
	
	fill(W, W + n, -1);
    calc(m, t, 0);
	
	if (ok) {
    	dfs(m, t, 0);
    	printf("%d\n", W[m]);
    	return 0;
	}
	
	
	
	
	return 0;
}