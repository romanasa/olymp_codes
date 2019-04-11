#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

const int dd = (int)8e5 + 1;

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
int n;

void build() {
	v = 0;
	L = 0, R = 0;
	alone = -1;
	
	while (R < n) {
			
		int wr = 0;
		if (s[R] == -1) {
			if (R - L != depth[v]) {
				int pos = R - L - depth[par[v]];
				s[R] = s[start[v] + pos];
			} else {
				s[R] = 0;
       			for (int j = 26 - 1; j >= 0; j--) if (go[v][j] != -1)
       				s[R] = j;
       		}
       		wr = 1;
       	}
	
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
		
		ans += L;
		
		if (wr)
			cout << (char)(s[R] + 'a') << " " << ans << "\n";
		
		R++;
		
	}
}

#define TASK "count"

int main() {
	fill(suf, suf + dd, -1);
	for (int i = 0; i < dd; i++) fill(go[i], go[i] + 26, -1);
	suf[0] = 0;
	
	scanf("%d", &n);
	
	for (int i = 0; i < n; i++) {
		char c;
		scanf("\n%c", &c);
		s[i] = c - 'a';
		if (c == '?') s[i] = -1;
	}
	build();
	return 0;
}