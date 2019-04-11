#include <bits/stdc++.h>
#define ll long long
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

const int dd = (int)2e6 + 1;

int used[2 * dd], l[dd], r[dd], go[2 * dd];
int cnt, T[dd], iT;

void dfs(int v) {
	++cnt;
	used[v] = 1;
	if (go[v] != -1 && !used[go[v]])
		dfs(go[v]);
}

vector<pair<int, int> > G;
	
int main() {
	int n, m;
	scanf("%d %d", &n, &m);
		
	fill(go, go + 2 * n + 2, -1);
	
	G.push_back({ 0, n });
	G.push_back({(int)2e9 + 1, n });
	
	for (int i = 0; i < n; i++) {
		scanf("%d %d", &l[i], &r[i]);
		G.push_back({ l[i], i });
		G.push_back({ r[i], i });
	}
	
	sort(G.begin(), G.end());
	
	for (int i = 0; i < (int)G.size(); i++) {
		if (G[i].second == n) continue;		
		int nxt = (l[G[i].second] == G[i].first ? r[G[i].second] : l[G[i].second]);
		int ind = lower_bound(G.begin(), G.end(), make_pair(nxt, -1)) - G.begin();
		go[i - 1] = ind;
		//err("%d--->%d\n", i - 1, ind);
	}
	
	//err("ok1\n");
	
	cnt = 0;
	dfs(0);
	int ans = cnt - 1;
	
	//err("ok1.5\n");
	
	//err("ans = %d\n", ans);
	for (int i = 0; i < 2 * n + 1; i++) {
		if (!used[i]) {
			cnt = 0;
			dfs(i);
			//err("st = %d, cnt = %d\n", i, cnt);
			T[iT++] = (cnt);
		}
	}	
	//err("ok2\n");
	
	sort(T, T + iT);
	reverse(T, T + iT);
	
	//err("T = {"); for (int i = 0; i < iT; i++) err(" %d,", T[i]); err(" }\n");
	
	for (int it = 0; it < min(m, iT); it++)
		ans += T[it] + 2;
	
	//err("ans = %d\n", ans);
		
	for (int it = iT; it < m; it++) {
		if ((it - iT) % 2 == 0)
			ans++;
		else
			ans += 3;
	}
	//err("ok3\n");
	
	
	printf("%d\n", ans);
	return 0;
}