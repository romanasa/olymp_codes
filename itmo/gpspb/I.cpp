#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

map<pair<int, int>, int> T;

const int dd = (int)5e3 + 7;

int used[dd];
vector<vector<int> > E;
vector<int> path;

void dfs(int v) {
	used[v] = 1;
	path.push_back(v);
	
	for (int to : E[v]) {
		if (used[to] == 1) {
		
			vector<int> ans(1, to);
			//err("tit\n");
			while (path.back() != to) ans.push_back(path.back()), path.pop_back();
		
			cout << "! NO" << endl;
			cout << (int)ans.size() << " ";
			reverse(ans.begin(), ans.end());
			for (int x : ans) cout << x << " ";
			cout << endl;
			exit(0);
		}
		if (!used[to]) dfs(to);
	}
	used[v] = 2;
	path.pop_back();
}

map<pair<int, int>, int> M;
int itt = 0;

int get(int a, int b) {
	auto it = M.find(make_pair(a, b));
	if (it != M.end()) return it->second;
	
	assert(++itt <= 20000);
	cout << "? " << a << " " << b << endl;
	
	int t; cin >> t;
	
	if (t == 1) E[a].push_back(b);
	else E[b].push_back(a);
	
	M[{ b, a }] = t ^ 1;
	return M[{ a, b }] = t;
}

int main() {
	int n; cin >> n;
	
	E.resize(n + 1);
	vector<int> P;
	for (int i = 0; i < n; i++) P.push_back(i + 1);
	
	sort(P.begin(), P.end(), [](int a, int b) {
		return get(a, b);
	});
	
	vector<vector<int> > sp(20, vector<int>(n));
	for (int i = 0; i < n; i++) sp[0][i] = P[i];
	
	for (int t = 1; (1 << t) <= n; t++) {
		for (int i = 0; i < n; i++) {
			sp[t][i] = sp[t - 1][i];
			int x = sp[t - 1][(i + (1 << (t - 1))) % n];
			if (get(x, sp[t][i])) sp[t][i] = x;
		}
	}
	
	for (int i = 1; i <= n; i++) if (!used[i])
		dfs(i);
		
	cout << "! YES" << endl;
	for (int i = 0; i < n; i++) cout << P[i] << " ";
	cout << endl;
	return 0;
}