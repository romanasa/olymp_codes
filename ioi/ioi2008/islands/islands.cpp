#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;


const int dd = (int)1e6 + 7;


int nxt[3 * dd];
int head[dd], tail[dd];
int to[3 * dd], cost[3 * dd];
int nv;

void add(int a, int b, int c) {
	to[tail[a]] = b, cost[tail[a]] = c;
	nxt[tail[a]] = nv++;
	tail[a] = nxt[tail[a]];
}

int go[dd], len[dd];
bool used[dd];

int cycle[dd], ic;
int st[dd], sz;

bool c[dd];
ll cur, C[dd];

void dfs(int v) {
	used[v] = 1;
	st[sz++] = v;
	
	if (used[go[v]] && ic == 0) {
		for (int i = sz - 1; st[i] != go[v]; i--) cycle[ic++] = st[i], c[st[i]] = 1;
		cycle[ic++] = go[v], c[go[v]] = 1;
	}
	
	if (!used[go[v]]) {
		dfs(go[v]);
	}
	
	for (int t = head[v]; t != tail[v]; t = nxt[t]) {
		if (!used[to[t]]) {
			dfs(to[t]);
		}
	}
	sz--;
}

ll calc(int v, int pr = -1) {
	ll mx1 = 0, mx2 = 0;
	
	
	for (int t = head[v]; t != tail[v]; t = nxt[t]) {
		if (c[to[t]] || to[t] == pr) continue;
	
		ll q = calc(to[t], v) + cost[t];
		if (q >= mx1) mx2 = mx1, mx1 = q;
		else if (q >= mx2) mx2 = q;
	}
	cur = max(cur, mx1 + mx2);
	return max(mx1, mx2);
}

ll P[dd];
pair<int, int> T[dd];
int deg[dd];

ll solve(int st) {

	ic = 0;
	dfs(st);

	//err("cycle = {"); for (int x : cycle) err(" %d,", x); err(" }\n");

	cur = 0;
	
	int n = ic;
	for (int i = 0; i < n; i++) {
		int v = cycle[i];
		int to = cycle[(i + 1) % n];
		int pr = (i ? cycle[i - 1] : cycle[n - 1]);
		C[v] = calc(v);
		//err("C[%d] = %d\n", v, C[v]);
		if (go[v] == to) T[i] = { v, len[v] };
		else T[i] = { pr, len[v] };
	}
	
	for (int i = 0; i < n; i++) {
		P[i + 1] = P[i] + T[i].second;
	}

	ll S1 = -1e18, S2 = -1e18;	
	
	for (int i = 0; i < n; i++) {
		if (i) cur = max(cur, S1 + P[n] - P[i] + C[T[i].first]);
		if (i) cur = max(cur, S2 + P[i] + C[T[i].first]);
		
		S1 = max(S1, P[i] + C[T[i].first]);
		S2 = max(S2, -P[i] + C[T[i].first]);
	}
	
	return cur;
}

int main() {
	int n;
	scanf("%d", &n);
	nv = n;
	
	for (int i = 0; i < n; i++) head[i] = tail[i] = i;
	
	for (int i = 0; i < n; i++) {
		scanf("%d %d", &go[i], &len[i]);
		go[i]--;
	}
	
	for (int i = 0; i < n; i++) {	
		add(go[i], i, len[i]);
		add(i, go[i], len[i]);
	}
	
	ll ans = 0;
	for (int i = 0; i < n; i++) {
		if (!used[i]) {
			ans += solve(i);
		}
	}
	printf("%lld\n", ans);
	return 0;
}