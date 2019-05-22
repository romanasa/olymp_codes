#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

#define TASK "robots"

const int dd = (int)1e3 + 7;

int ans = 0, TT = 10000005;
int cur, n, m, g, beg;
char A[dd][dd];
int go[dd * dd];
int used[dd * dd], h[dd * dd];
int was[dd * dd], robot[dd * dd];

vector<vector<int> > E;
vector<pair<int, int> > T;
vector<pair<pair<int, int>, int> > G;

void color(int v, int d) {
	was[v] = 1;
	if (robot[v]) {
		T.push_back({ v, d });
	}
		
	for (int to : E[v]) {
		if (!was[to])
			color(to, d + 1);
	}
}

void dfs(int v, int d) {

	used[v] = 1;
	h[v] = d;
	
	if (used[go[v]] == 1) {
		cur = h[v] - h[go[v]] + 1;
		beg = go[v];
		return;
	}
	
	if (!used[go[v]]) {
		dfs(go[v], d + 1);
	}
	
	used[v] = 2;
}

void make(int v) {
	dfs(v, 0);
	
	T.clear();
	
	color(beg, 0);
	
	int t = min(cur, (int)T.size());
	ans += t;

	for (int i = 0; i < t; i++) {
		G.push_back(make_pair( make_pair(T[i].first / m + 1, T[i].first % m + 1) , TT - i - T[i].second ));
	}
}

int main() {
#ifndef HOME
	freopen(TASK".in", "r", stdin), freopen(TASK".out", "w", stdout);
#endif	

	scanf("%d %d %d", &n, &m, &g);
	
	E.resize(n * m);
	
	for (int i = 0; i < n; i++)
		scanf("%s", A[i]);
		
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			int v = i * m + j;
			
			if (tolower(A[i][j]) == 'n')
				go[v] = (i - 1) * m + j;
			if (tolower(A[i][j]) == 's')
				go[v] = (i + 1) * m + j;
			if (tolower(A[i][j]) == 'w')
				go[v] = i * m + (j - 1);
			if (tolower(A[i][j]) == 'e')
				go[v] = i * m + (j + 1);
				
			if (toupper(A[i][j]) == A[i][j])
				robot[v] = 1;
		}
	}
	
	for (int i = 0; i < n * m; i++)
		E[go[i]].push_back(i);
	
	for (int i = 0; i < n * m; i++) {
		if (!E[i].size() && !was[i]) {
			make(i);			
		}
	}
	
	for (int i = 0; i < n * m; i++) {
		if (!was[i])
			make(i);
	}
	
	printf("%d\n", ans);
	if (g) {
		for (auto c : G) {
			printf("%d %d %d\n", c.first.first, c.first.second, c.second);
		}
	}
	return 0;
	
}