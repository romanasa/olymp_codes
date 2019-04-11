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
		R++;
		cout << ans << "\n";
	}
}

#define TASK "count"

int main() {
	fill(suf, suf + dd, -1);
	for (int i = 0; i < dd; i++) fill(go[i], go[i] + 26, -1);
	suf[0] = 0;
	
	string t;
	cin >> t;
	
	n = (int)t.size();
	
	for (int i = 0; i < (int)t.size(); i++) s[i] = t[i] - 'a';
	build();
	return 0;
}