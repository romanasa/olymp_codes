#include <bits/stdc++.h>
#define err(...) //fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

vector<vector<pair<int, int> > > E;

#define TASK "globalcut"

int main() {
#ifndef HOME
	//freopen(TASK".in", "r", stdin), freopen(TASK".out", "w", stdout);
#endif
	int n, m;
	scanf("%d %d", &n, &m);
	
	E.resize(n);
	
	for (int i = 0; i < m; i++) {
		int a, b, c;
		scanf("%d %d %d", &a, &b, &c);	
		if (a == b) continue;
		E[a - 1].push_back({ b - 1, c });
		E[b - 1].push_back({ a - 1, c });
	}
	
	vector<int> used(n);
	
	ll ans = (ll)1e18;
	
	for (int it = 0; it < n; it++) {
		vector<ll> d(n);
		vector<int> was(n), cur;
		
		for (int j = 0; j < n; j++) {	
			int ind = -1;
			for (int i = 0; i < n; i++) if (!used[i] && !was[i] && (ind == -1 || d[i] > d[ind])) {
				ind = i;
			}
			if (ind == -1) break;
			was[ind] = 1;
			cur.push_back(ind);
			for (auto c : E[ind]) d[c.first] += c.second;
		}
		
		if (cur.size() < 2) break;
		
		int s = cur.back();
		int t = cur[(int)cur.size() - 2];
		
		for (int v = 0; v < n; v++) {
			for (auto &e : E[v]) {
				if (v != e.first && e.first == s) e.first = t;
			}
		}
		
		for (int v = 0; v < n; v++) {
			for (auto e : E[v]) {
				err("%d---%d--->%d\n", v, e.second, e.first);
			}
		}
		
		ll cost = 0;
		for (auto e : E[s]) {
			if (e.first != s) cost += e.second;
			if (e.first != t && e.first != s) E[t].push_back(e);
		}
		
		used[s] = 1;
		err("s = %d, t = %d, cost = %I64d\n", s, t, cost);
		
		ans = min(ans, cost);
		E[s].clear();		
	}
	printf("%lld\n", ans);
	return 0;
}