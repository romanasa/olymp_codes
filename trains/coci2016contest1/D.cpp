#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

vector<vector<int> > E;
const int dd = (int)2e6 + 7;

int C[dd], G[dd];
int len = 2;

void dfs(int v, int pr = -1) {
	int c = 0;
	for (int to : E[v]) if (to != pr) {
		dfs(to, v);
		c = max(c, G[to]);
	}
	if (C[v] == 1) G[v] = c + 1;
	else G[v] = 0;
}

void upd(pair<pair<int, int>, pair<int, int> > &cur, int val, int pos) {
	if (val >= cur.first.first) {
		cur.second = cur.first;
		cur.first = { val, pos };
	} else if (val >= cur.second.first) {
		cur.second = { val, pos };
	}
}

void calc(int v, int pr = -1, int pv = -1) {
	
	
	pair<pair<int, int>, pair<int, int> > cur(make_pair(0, -1), make_pair(0, -1));
	
	for (int to : E[v]) if (to != pr) {
		upd(cur, G[to], to);
	}
	if (pr != -1) upd(cur, pv, pr);
	
	if (C[v] == 1) len = max(len, 2 * (cur.first.first + 1));
	
	if (C[v] == 2) {
		if (cur.first.first == cur.second.first) len = max(len, 2 * cur.first.first + 1);	
	}
	
	for (int to : E[v]) if (to != pr) {
		int cpv = (cur.first.second == to ? cur.second.first : cur.first.first);
		calc(to, v, (C[v] == 1 ? max(cpv, 0) + 1 : 0));
	}
}


int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int n;
	cin >> n;
	
	E.resize(n);

	for (int i = 0; i + 1 < n; i++) {
		int a, b;
		cin >> a >> b;
		E[a - 1].push_back(b - 1);
		E[b - 1].push_back(a - 1);	
	}
	
	for (int i = 0; i < n; i++) cin >> C[i];
		
	int ok = 0;
	for (int i = 0; i < n; i++) ok |= (C[i] == 1);
	if (!ok) cout << *min_element(C, C + n) << "/1\n", exit(0);
	
	
	dfs(0);
	calc(0);
	
	if (len % 2) cout << "2/" << len << "\n";
    else cout << "1/" << len / 2 << "\n";	
	
	
	return 0;
}