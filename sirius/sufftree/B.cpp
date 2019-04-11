#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

const int dd = (int)2e5 + 1;

string s;

int L, R, alone;
int go[dd][131];
int suf[dd], par[dd], depth[dd], start[dd];

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



void out() {
	int t = 0;
	for (int i = 0; i < cnt; i++)
		for (int j = 0; j < 131; j++)
			t += (go[i][j] != -1);		
	cout << cnt << " " << t << "\n";	
	for (int i = 0; i < cnt; i++) {
		for (int j = 0; j < 131; j++) if (go[i][j] != -1) {
			int l = start[go[i][j]];
			int r = l + depth[go[i][j]] - depth[i] - 1;
			r = min(r, (int)s.size() - 1);
			cout << i + 1 << " " << go[i][j] + 1 << " " << l + 1 << " " << r + 1 << "\n"; 
		}
	}
}

void build() {
	v = 0;
	L = 0, R = 0;
	alone = -1;
	
	int n = (int)s.size();
	while (R < n) {
		while (L <= R) {
			int cr = goDown();
			
			if (alone != -1) suf[alone] = par[v], alone = -1;
			if (!cr) break;
			
			v = par[v];
			if (suf[v] == -1) alone = v, v = par[v];
				
			L++, v = suf[v];
			while (R - L > depth[v])
				v = go[v][s[L + depth[v]]];
		}
		R++;
	}
}

#define TASK "tree"

int main() {
#ifndef HOME
	freopen(TASK".in", "r", stdin), freopen(TASK".out", "w", stdout);
#endif
	fill(suf, suf + dd, -1);
	for (int i = 0; i < dd; i++) fill(go[i], go[i] + 131, -1);
	suf[0] = 0;
	
	cin >> s;
	
	build();	
	out();
	return 0;
}