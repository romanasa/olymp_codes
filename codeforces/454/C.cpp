#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

int n, m;
int G[31][31];
int ans = (int)1e9, ansM = -1;

int cur[31];
int cnt;

void go(int v) {
	if (cnt >= ans) return;
	
	if (v == n) {
		int ok = 1;
		for (int i = 0; i < n; i++) if (G[v][i] != (1 << n) - 1) {
			ok = 0;
			break;
		}
		if (!ok) return;
		
		ans = cnt;
		ansM = 0;
		for (int i = 0; i < cnt; i++) ansM |= (1 << cur[i]);
	} else {
	
		for (int i = 0; i < n; i++) G[v + 1][i] = G[v][i];
	
		go(v + 1);
		
		cur[cnt++] = v;
		
		for (int i = 0; i < n; i++) if ((G[v][v] >> i) & 1) {
			G[v + 1][i] |= G[v][v];
		}
		go(v + 1);
		cnt--;
	}
}
	
int main() {

	cin >> n >> m;
	
	for (int i = 0; i < m; i++) {
		int a, b;
		cin >> a >> b;
		a--, b--;
		G[0][a] |= (1 << b);
		G[0][b] |= (1 << a);
	}	
	
	for (int i = 0; i < n; i++) G[0][i] |= (1 << i);
	
	go(0);

	cout << ans << "\n";
	for (int i = 0; i < n; i++) if ((ansM >> i) & 1) cout << i + 1 << " ";

	return 0;
}