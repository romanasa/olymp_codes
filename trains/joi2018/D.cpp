#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

vector<vector<pair<int, int> > > E;

ll G[321][321];

int n, m;
	
vector<ll> Dijkstra(int s) {
	vector<ll> d(n, (ll)1e18);
	priority_queue<pair<ll, int> > P;
	
	d[s] = 0;
	P.push({ -d[s], s });
	
	while (P.size()) {
		int v = P.top().second;
		ll cur = -P.top().first;
		P.pop();
		if (d[v] != cur) continue;
		
		for (auto &e : E[v]) {
			if (d[e.first] > cur + e.second) {
				d[e.first] = cur + e.second;
				P.push({ -d[e.first], e.first });
			}
		}
	}
	return d;
}

int main() {
	cin >> n >> m;
	int s, t; cin >> s >> t; s--, t--;
	int u, v; cin >> u >> v; u--, v--;
	
	int tmp = t;
	
	E.resize(n);
	
	for (int i = 0; i < m; i++) {
		int a, b, c;
		cin >> a >> b >> c;
		E[a - 1].push_back({ b - 1, c });
		E[b - 1].push_back({ a - 1, c });
	}
	
	ll ans = (ll)1e18 + 1;
	
	for (int it = 0; it < 2; it++) {
	
    	auto du = Dijkstra(u);
    	auto dv = Dijkstra(v);
    	//err("u = %d, v = %d\n", u, v);
    	
    	ans = min(ans, du[v]);
    	
    	vector<ll> d(n, (ll)1e18), t(n, (ll)1e18);
    	priority_queue<pair<ll, int> > S;
    	
    	d[s] = 0;
    	t[s] = du[s];
		S.push({ -d[s], s });
		
		while (S.size()) {
			int v = S.top().second;
			ll cur = -S.top().first;
			S.pop();
			if (d[v] != cur) continue;
			
			//ans = min(ans, t[v] + dv[v]);
			//err("v = %d, t[v] = %I64d, dv[v] = %I64d\n", v, t[v], dv[v]);
			
			for (auto &e : E[v]) {
				if (d[e.first] > cur + e.second) {
					d[e.first] = cur + e.second;
					t[e.first] = min(t[v], du[e.first]);
					S.push({ -d[e.first], e.first });
				} else if (d[e.first] == cur + e.second) t[e.first] = min(t[e.first], t[v]);
			}
		}
		
		auto dt = Dijkstra(tmp);
		for (int v = 0; v < n; v++) if (d[v] + dt[v] == d[tmp])
			ans = min(ans, t[v] + dv[v]);
		
     	swap(u, v);
	}
	cout << ans << "\n";
	return 0;
}