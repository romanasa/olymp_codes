#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

vector<int> num, used;
vector<vector<int>> E;

struct dsu {
	vector<int> P, R;
	
	void init(int n) { P.resize(n), R.resize(n); for (int i = 0; i < n; i++) P[i] = i, R[i] = 1; }
	
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

struct triple { int a, b, c; };

vector<triple> ans;

int dfs(int v, int pr = -1) {
	used[v] = 1;
	int cur = -1;
	for (int to : E[v]) if (to != pr) {
		int need = dfs(to, v);
		if (need == -1) {
			if (cur == -1) cur = to;
			else ans.push_back({ cur, v, to }), cur = -1;
		} else {
			ans.push_back({ v, to, need });
		}
	}
	return cur;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	
	int n, m;
	cin >> n >> m;
	
	num.resize(n), E.resize(n);
	J.init(n);
	
	for (int i = 0; i < n; i++) num[i] = i;
	
	for (int i = 0; i < m; i++) {
		int a, b;
		cin >> a >> b;
		a--, b--;
		
		if (!J.un(a, b)) {
			int c = (int)num.size();
			E.emplace_back();
			
			E[a].push_back(c);
			E[c].push_back(a);
			
			num.push_back(b);
		} else {
			E[a].push_back(b);
			E[b].push_back(a);	
		}
	}
	
	used.resize(num.size());
	
	for (int i = 0; i < (int)num.size(); i++) if (!used[i])
		dfs(i);
	cout << (int)ans.size() << "\n";
	for (auto c : ans) {
		cout << num[c.a] + 1 << " " << num[c.b] + 1 << " " << num[c.c] + 1 << "\n";
	}	
	return 0;
}