#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

int G[1234][1234];
int used[1234];
int n, q;

int dfs(int v, int t) {
	if (v == t) return 0;
	used[v] = 1;
	for (int i = 0; i < n; i++) if (G[v][i] && !used[i]) {
		int q = dfs(i, t);
		if (q != -1) return q + 1;
	}
	return -1;
}

int main() {
	cin >> n >> q;
	while (q--) {
		string s;
		int a, b;
		cin >> s >> a >> b;
		if (s == "link") G[a - 1][b - 1] = G[b - 1][a - 1] = 1;
		if (s == "cut") G[a - 1][b - 1] = G[b - 1][a - 1] = 0;
		fill(used, used + n, 0);
		if (s == "get") cout << dfs(a - 1, b - 1) << "\n";
	}
	return 0;
}