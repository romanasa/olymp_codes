#include <bits/stdc++.h>
#define ll long long

using namespace std;

vector<vector<int> > E;

const int dd = (int)2e5 + 7;

struct dsu {
	int P[dd], R[dd];
	
	int get(int v) { return v == P[v] ? v : P[v] = get(P[v]); }
	
	bool un(int a, int b) {
		a = get(a), b = get(b);
		if (a != b) {
			if (R[b] > R[a]) swap(a, b);
			P[b] = a, R[a] += R[b];
			return true;
		}
		return false;
	}
} J;

int S[dd], T[dd];
int G[dd];

int main() {
	int n, m;
	scanf("%d %d", &n, &m);
	
	E.resize(n);
	
	for (int i = 0; i < m; i++) {
		int a, b;
		scanf("%d %d", &a, &b);
		E[a - 1].push_back(b - 1);
		E[b - 1].push_back(a - 1);
	}
	
	int s, t, ds, dt;
	scanf("%d %d %d %d", &s, &t, &ds, &dt);
	
	vector<pair<int, int> > ans;
	
	for (int v = 0; v < n; v++) {
		for (int to : E[v]) {
			if (v != s && v != t && to != s && to != t) {
				if (J.un(v, to)) {
					ans.push_back({ v, to });
				}
			}
		}
	}

	for (int v = 0; v < n; v++) {
		if (v != s && v != t)
			G[J.get(v)] = 1;
	}
	
	for (int to : E[s]) 
		S[J.get(to)] = 1;
	for (int to : E[t])
		T[J.get(to)] = 1;
		
	auto no = []() {
		exit(0 * puts("No"));
	};

	for (int v = 0; v < n; v++) {
		if (G[v] && !S[v] && !T[v]) {
			no();
		}
	}
	
	set<int> SS;
	for (int v = 0; v < n; v++) {
		if (G[v])
			SS.insert(v);
	}
	
	int ind = -1;
	for (int v = 0; v < n; v++) {
		if (T[v] && S[v]) {
			ind = v;
			ans.push_back({ s, ind });
			ans.push_back({ ind, t });
			ds--, dt--;
			SS.erase(ind);
			break;
		}
	}	
	
	if (ind == -1) {
		for (int to : E[s]) {
			if (to == t) {
				ind = 0;
				ans.push_back({ s, t });
				ds--, dt--;
				break;
			}
		}
	}
	
	if (ind == -1) {
		no();
	}
	
	for (int v = 0; v < n; v++) {
		if (!SS.count(v)) continue;
		
		if (S[v] && !T[v]) {
			ds--;
			ans.push_back({ s, v });
			SS.erase(v);
		}
		if (T[v] && !S[v]) {
			dt--;
			ans.push_back({ t, v });
			SS.erase(v);
		}
	}
	
	if (ds < 0 || dt < 0)
		no();
		
	while (SS.size()) {
		int v = *SS.begin();
		SS.erase(SS.begin());
		
		bool ok = false;
		if (ds > 0 && S[v]) {
			ds--;
			ans.push_back({ s, v });
			ok = true;
		}
		if (dt > 0 && T[v]) {
			dt--;
			ans.push_back({ t, v });
			ok = true;
		}
		if (!ok)
			no();
	}
	puts("Yes");
	for (auto c : ans)
		printf("%d %d\n", c.first + 1, c.second + 1);
	return 0;
}