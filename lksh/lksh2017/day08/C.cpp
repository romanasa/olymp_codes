#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

vector<multiset<int> > E;
vector<int> ans;

void dfs(int v) {
	while (E[v].size()) {	
		int to = *E[v].begin();
		
		E[v].erase(E[v].begin());
		E[to].erase(E[to].find(v));
		
		dfs(to);
	}
	ans.push_back(v);
}

#define TASK "euler"

int main() {
#ifndef HOME
	freopen(TASK".in", "r", stdin), freopen(TASK".out", "w", stdout);
#endif
	int n;
	scanf("%d", &n);
	
	E.resize(n);
	int cnt = 0, pos = 0;
	
	for (int i = 0; i < n; i++) {
		int x;
		scanf("%d", &x);
		for (int j = 0; j < x; j++) {
			int to;
			scanf("%d", &to);
			E[i].insert(to - 1);
		}	
		if (x & 1) {
			cnt++, pos = i;
		}
	}
	if (cnt == 1 || cnt == 3) return 0 * puts("-1");
	
	dfs(pos);
	reverse(ans.begin(), ans.end());
	printf("%d\n", (int)ans.size() - 1);
	for (int x : ans) printf("%d ", x + 1);
	
	return 0;
}