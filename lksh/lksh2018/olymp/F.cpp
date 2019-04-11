#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

const int dd = (int)3e5 + 7;
const int mod = (int)1e9 + 7;

vector<vector<int> > E;
vector<int> H;

int used[dd], pos[dd];
int cnt[dd];

void add(int &a, int b) {
	a += b;
	if (a >= mod) a -= mod;
}

void dfs(int v) {
	used[v] = 1;
	for (int to : E[v]) if (!used[to]) {
		dfs(to);
	}
	pos[v] = (int)H.size();
	H.push_back(v);
}

int main() {
	int n, m, k;
	cin >> n >> m >> k;
	
	E.resize(n);
	
	for (int i = 0; i < m; i++) {
		int a, b;
		cin >> a >> b;
		E[a - 1].push_back(b - 1);
	}
	
	int s, t;
	cin >> s >> t;
	s--, t--;
	
	vector<int> need(k);
	for (int i = 0; i < k; i++) {
		cin >> need[i];
		need[i]--;
	}
	need.push_back(t);
	
	fill(pos, pos + n, -1);
	dfs(s);
	reverse(H.begin(), H.end());
	
	for (int v : need) {
		if (pos[v] == -1) return 0 * puts("0");
	}
	
	for (int v : H) {
		pos[v] = (int)H.size() - 1 - pos[v];
	}
	
	sort(need.begin(), need.end(), [](int a, int b) {
		return pos[a] < pos[b];
	});
	
	int curb = 0;
	cnt[s] = 1;
	
	for (int v : H) {
		if (need[curb] == v) curb++;
		if (curb == (int)need.size()) break;
		
		for (int to : E[v]) {
			if (pos[to] <= pos[need[curb]]) add(cnt[to], cnt[v]);
		}
	}
	cout << cnt[t] << "\n";
	return 0;
}