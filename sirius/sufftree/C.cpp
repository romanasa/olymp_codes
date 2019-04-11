#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

const int dd = (int)5e5 + 1;

int L, R, alone;

int go[dd][26];
int suf[dd], par[dd], depth[dd], start[dd];
int s[dd];

int cnt = 1;

int newnode(int p, int d, int st) {
	int cur = cnt++;
	par[cur] = p;
	depth[cur] = d;
	start[cur] = st;
	return cur;
}

int v;

int goDown() {
	int ok = 0;
	if (R - L != depth[v]) {
	
		int pos = R - L - depth[par[v]];
		
		if (s[R] != s[start[v] + pos]) {
			
			int nv = newnode(par[v], R - L, start[v]);
			ok = 1;
			
			go[par[v]][s[start[v]]] = nv;
			start[v] += pos;
			par[v] = nv;
			go[nv][s[start[v]]] = v;
			
			v = nv;
		}
	}
	
	if (R - L == depth[v]) {
		if (go[v][s[R]] == -1) {
			int nv = newnode(v, (int)1e9, R);			
			ok = 1;
			go[v][s[R]] = nv; 
		}
		v = go[v][s[R]];
	}
	return ok;
}


ll ans = 0;
int la = -1, ra = -1;
int n;

void build() {
	v = 0;
	L = 0, R = 0;
	alone = -1;
	
	while (R < n) {
		while (L <= R) {
			int cr = goDown();
			
			if (alone != -1) suf[alone] = par[v], alone = -1;

			if (!cr) break;
			
			v = par[v];
			
			if (suf[v] == -1) 
				alone = v, v = par[v];
				
			L++, v = suf[v];

			while (R - L > depth[v])
				v = go[v][s[L + depth[v]]];
		}
		R++;
	}
}

int dfs(int v) {
	int sz = 1;
	for (int j = 0; j < 26; j++) 
		sz &= (go[v][j] == -1);
		
	for (int j = 0; j < 26; j++) if (go[v][j] != -1) {
		sz += dfs(go[v][j]);
	}
	//err("v = %d, len = %d, sz = %d\n", v, len, sz);
	
	if (ans < 1ll * depth[v] * sz) {
		ans = 1ll * depth[v] * sz;
		ra = start[v] + depth[v] - depth[par[v]] - 1;
		la = ra - depth[v] + 1;
	}
	//err("v = %d, start = %d, depth = %d, sz = %d\n", v, start[v], depth[v], sz);
	return sz;
}

#define TASK "refrain"

int main() {
#ifndef HOME
	freopen(TASK".in", "r", stdin), freopen(TASK".out", "w", stdout);
#endif
	fill(suf, suf + dd, -1);
	for (int i = 0; i < dd; i++) fill(go[i], go[i] + 26, -1);
	suf[0] = 0;
	
	int m;
	scanf("%d %d", &n, &m);
	
	for (int i = 0; i < n; i++) scanf("%d", &s[i]);
	s[n++] = m + 1;
	
	build();

	
	for (int i = 0; i < cnt; i++) {
		if (depth[i] > n) {
			depth[i] = depth[par[i]] + (n - 1 - start[i]);
		}
	}
	
	//for (int i = 0; i < cnt; i++) depth[i] = min(depth[i], n - 1);
	
	dfs(0);
	
	printf("%I64d\n", ans);
	printf("%d\n", ra - la + 1);
	
	assert(la != -1);
	
	//printf("la = %d, ra = %d\n", la, ra);
	assert(ra < n);
	for (int i = la; i <= ra; i++)
		printf("%d ", s[i]);
		
	return 0;
}