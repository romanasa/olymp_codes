#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

const int dd = (int)1e5 + 7;
const int mod = 998244353;
map<int, pair<int, int> > M[dd];

pair<int, int> par(pair<int, int> a, pair<int, int> b) {
	return { (1ll * a.first * b.second + 1ll * b.first * a.second) % mod, 1ll * a.second * b.second % mod };
}

pair<int, int> seq(pair<int, int> a, pair<int, int> b) {
	return { 1ll * a.first * b.first % mod, (1ll * a.first * b.second + 1ll * a.second * b.first) % mod };
}

void add(map<int, pair<int, int> > &x, int to, pair<int, int> cur) {
	auto it = x.find(to);
	if (it == x.end()) x[to] = cur;
	else it->second = par(it->second, cur);
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int n, m;
	cin >> n >> m;
	
	for (int i = 0; i < m; i++) {
		int a, b;
		cin >> a >> b;
		
		a--, b--;
		
		add(M[a], b, { 1, 1 });
		add(M[b], a, { 1, 1 });
	}
	
	queue<int> q;
	vector<int> used(n);
	
	for (int i = 1; i < n - 1; i++) {
		if (M[i].size() == 2) q.push(i), used[i] = 1;
	}
	
	while (q.size()) {
		int v = q.front();
		q.pop();
		
		int a = M[v].begin()->first;
		int b = M[v].rbegin()->first;
		
		auto t = seq(M[v][a], M[v][b]);
		
		M[a].erase(v);
		M[b].erase(v);
		
		add(M[a], b, t);
		add(M[b], a, t);
		
		if (a != 0 && a != n - 1 && M[a].size() == 2 && !used[a]) q.push(a), used[a] = 1;
		if (b != 0 && b != n - 1 && M[b].size() == 2 && !used[b]) q.push(b), used[b] = 1;
	}
	cout << M[0][n - 1].first << "\n";
	return 0;
}