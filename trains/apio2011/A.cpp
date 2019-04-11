#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

const int dd = (int)1e5 + 7;

vector<vector<int> > E;
int used[2 * dd];
int cnt;	

int dx[] = { -1, 0, 1, 0 };
int dy[] = { 0, 1, 0, -1 };

void dfs(int v) {
	cnt++;
	used[v] = 1;
	for (int to : E[v]) if (!used[to]) dfs(to);
}

int n, m, k;

struct dsu {
	int P[5 * dd], R[5 * dd];
	dsu() { for (int i = 0; i < 5 * dd; i++) P[i] = i, R[i] = 1; }
	int get(int v) { return v == P[v] ? v : P[v] = get(P[v]); }
	void un(int a, int b) {
		a = get(a), b = get(b);
		if (a != b) {
			if (R[b] > R[a]) swap(a, b);
			P[b] = a, R[a] += R[b];
		}
	}
} J;
	
int main() {
	cin >> n >> m >> k;
	
	E.resize(n + m);	
	
	for (int i = 0; i < k; i++) {
		int a, b, c;
		cin >> a >> b >> c;
		
		c ^= ((a & 1) && (b & 1));
		
		if (c) {
			J.un(a, b + n);
			J.un(n + m + a, n + m + b + n);
		} else {
			J.un(a, n + m + b + n);
			J.un(n + m + a, b + n);
		}
		
		a--, b--;
		E[a].push_back(b + n);
		E[b + n].push_back(a);
	}
	
	for (int i = 0; i < n + m; i++) if (J.get(i) == J.get(i + n + m)) return 0 * puts("0");
	
	
	int p = -1;
	for (int i = 0; i < n + m; i++) if (!used[i]) {
		cnt = 0;
		dfs(i);
		p++;
	}
	
	int ans = 1;
	for (int i = 0; i < p; i++) ans = ans * 2 % (int)1e9;
	cout << ans << "\n";
	
	return 0;
}