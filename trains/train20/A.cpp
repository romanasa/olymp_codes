#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

const int dd = (int)2e5 + 7;
const int LOG = 18;
pair<int, int> Q[dd];

char s[dd], t[dd];
int T[4 * dd][LOG][3];
int G[4 * dd][LOG][3];
int J[4 * dd];
int cost[31];

void calc(int v) {
	for (int i = 0; i < J[v]; i++) {
		for (int j = 0; j < 2; j++) {
			G[v][i][j] = G[v * 2 + 1][i][G[v * 2][i][j]];
			T[v][i][j] = T[v * 2][i][j]	+ G[v * 2][i][j] + T[v * 2 + 1][i][G[v * 2][i][j]];
		}
	}
	G[v][J[v]][0] = G[v * 2 + 1][J[v] - 1][G[v * 2][J[v] - 1][0]];
	G[v][J[v]][1] = G[v * 2 + 1][J[v] - 1][G[v * 2][J[v] - 1][1]];
}

void build(int v, int tl, int tr) {
	if (tl == tr) {
		G[v][0][0] = (Q[tl].first + Q[tl].second) / 2;
		G[v][0][1] = (Q[tl].first + Q[tl].second + 1) / 2;
	} else {
		int tm = (tl + tr) / 2;
		build(v * 2, tl, tm);
		build(v * 2 + 1, tm + 1, tr);
		J[v] = J[v * 2] + 1;
		calc(v);
	}
}

void upd(int v, int tl, int tr, int pos) {
	if (tl == tr) {
		G[v][0][0] = (Q[tl].first + Q[tl].second) / 2;
		G[v][0][1] = (Q[tl].first + Q[tl].second + 1) / 2;
	} else {
		int tm = (tl + tr) / 2;
		if (pos <= tm) upd(v * 2, tl, tm, pos);
		else upd(v * 2 + 1, tm + 1, tr, pos);
		calc(v);
	}
}

void out(int v, int tl, int tr) {
	/*err("v = %d, tl = %d, tr = %d\n", v, tl, tr);
	for (int i = 0; i <= J[v]; i++) {
		for (int j = 0; j < 2; j++) {
			err("G[%d][%d][%d] = %d, T[%d][%d][%d] = %d\n", v, i, j, G[v][i][j], v, i, j, T[v][i][j]);
		}
	}*/
	if (tl != tr) {
		int tm = (tl + tr) / 2;
		out(v * 2, tl, tm);
		out(v * 2 + 1, tm + 1, tr);
	}
}

#define TASK "registers"

int main() {
#ifndef HOME
	freopen(TASK".in", "r", stdin), freopen(TASK".out", "w", stdout);
#endif
	int n, k;
	scanf("%d %d", &n, &k);
	
	scanf("%s", s);
	scanf("%s", t);
	
	fill(cost, cost + 31, -1);
	for (int i = 0; i < k; i++) {
		int a, b;
		scanf("%d %d", &a, &b);
		cost[a] = b;
	}
	
	for (int i = 0; i < n; i++) Q[i] = { (int)(s[n - i - 1] - '0'), (int)(t[n - i - 1] - '0') };
	
	while (n - (n&-n) != 0) n++;
	
	build(1, 0, n - 1);
	//out(1, 0, n - 1);
		
	int q;
	scanf("%d", &q);
	for (int i = 0; i < q; i++) {
		int a, pos;
		scanf("%d %d", &a, &pos);
		if (a == 1) Q[pos].first ^= 1;
		else Q[pos].second ^= 1;
		
		upd(1, 0, n - 1, pos);
		
		int ans = (int)2e9;
		for (int bit = 0; bit < LOG; bit++) if (cost[bit] != -1)
			ans = min(ans, (T[1][bit][0] + G[1][bit][0]) * cost[bit]);		
		printf("%d\n", ans);
	}	
	return 0;
}