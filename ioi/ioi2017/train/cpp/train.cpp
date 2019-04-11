#include <bits/stdc++.h>
#include "train.h"

#define err(...) //fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

const int dd = (int)5007;

vector<int> who_wins(vector<int> a, vector<int> r, vector<int> u, vector<int> v) {
	int n = (int)a.size();
	int m = (int)u.size();
	
	vector<vector<int>> E(n), ER(n);
	vector<int> used(n), deg(n), was(n);
	
	for (int i = 0; i < m; i++) {
		E[u[i]].push_back(v[i]);
		ER[v[i]].push_back(u[i]);
	}
	
	int need = 1;
	while (need) {
		need = 0;
		
		vector<int> t;
		for (int i = 0; i < n; i++) if (r[i] && !was[i]) t.push_back(i);
		
		fill(used.begin(), used.end(), 0);
		for (int i = 0; i < n; i++) deg[i] = (int)E[i].size();
		
		while (t.size()) {
			int v = t.back();
			t.pop_back();
			
			for (int to : ER[v]) if (!used[to] && !was[to]) {
				if (a[to] == 1) {
					used[to] = 1;
					if (!r[to]) t.push_back(to);
				} else {
					if (--deg[to] == 0) {
						if (!r[to]) t.push_back(to);
						used[to] = 1;
					}
				}
			}
		}
		for (int i = 0; i < n; i++) if (!was[i] && !used[i]) was[i] = 1, need = 1;
	}
	
	vector<int> ans;
	for (int i = 0; i < n; i++) ans.push_back(!was[i]);
	return ans;
	
}
