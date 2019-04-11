#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

vector<set<int> > E;
vector<int> in, used;
queue<int> q;

void dfs(int v) {
	if (E[v].empty()) return;
	int to = *E[v].begin();
	E[v].erase(to);
	
	dfs(to);
	in[to]--;
	
	if (in[to] == 0 && !used[to]) q.push(to), used[to] = 1;
}

int main() {
	int n, m;
	cin >> n >> m;
	
	E.resize(n);
	in.resize(n), used.resize(n);
	
	for (int i = 0; i < m; i++) {
		int a, b;
		cin >> a >> b;
		E[a - 1].insert(b - 1);
		in[b - 1]++;
	}
	
	for (int i = 0; i < n; i++) if (in[i] == 0) 
		q.push(i), used[i] = 1;
		
	int ans = 0;
		
	while (q.size()) {
		int v = q.front();
		
		if (E[v].empty()) {
			q.pop();
			continue;
		}
		
		ans++;
		dfs(v);
	}
		
	cout << ans << "\n";
	
	return 0;
}