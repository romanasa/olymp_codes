#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

int G[543][543];
int used[543 * 2];
int pr[543 * 2];
int tmm;

vector<vector<int> > E;

bool dfs(int v) {
	if (used[v] == tmm) return false;
	used[v] = tmm;
	for (int to : E[v]) {
		if (pr[to] == -1 || dfs(pr[to])) {
			pr[to] = v;
			return true;
		}
	}
	return false;
}

int main() {
	int n;
	cin >> n;
	
	vector<int> x(n), y(n), s(n);
	for (int i = 0; i < n; i++) {
		cin >> x[i] >> y[i] >> s[i];
	}
	
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) if (y[i] < y[j] && max(abs(x[i] - x[j]), abs(y[i] - y[j])) <= max(s[i], s[j])) {
			G[i][j] = 1;
		}
	}
	
	for (int k = 0; k < n; k++) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				G[i][j] |= (G[i][k] & G[k][j]);
			}
		}
	}
	
	fill(pr, pr + 2 * n, -1);
	E.resize(n);
	
	for (int i = 0; i < n; i++) 
		for (int j = 0; j < n; j++) if (G[i][j])
			E[i].push_back(j + n);
	
	for (int i = 0; i < n; i++) {
		tmm++;
		dfs(i);
	}
	
	int ans = n;
	for (int i = n; i < n + n; i++) {
		if (pr[i] != -1) ans--;
	}
	
	cout << (ans == n ? -1 : ans + 1) << "\n";
	return 0;
}