#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

vector<vector<pair<int, int> > > E;

int main() {
	int n, m;
	cin >> n >> m;
	
	E.resize(n);
	
	for (int i = 0; i < m; i++) {
		int a, b, c;
		cin >> a >> b >> c;
		E[a - 1].push_back({ b - 1, c });
		E[b - 1].push_back({ a - 1, c });
	}
	
	
	ll ans = (ll)1e18;
	
	for (int msk = 1; msk < (1 << n) - 1; msk++) {
		vector<int> tp(n);
		
		for (int i = 0; i < n; i++) {
			if ((msk >> i) & 1) tp[i] = 0;
			else tp[i] = 1;
		}
		
		ll cost = 0;
		for (int v = 0; v < n; v++) {
			for (auto e : E[v]) {
				if (tp[v] != tp[e.first])
					cost += e.second;
			}
		}
		ans = min(ans, cost / 2);
	}
	cout << ans << "\n";
	return 0;
}