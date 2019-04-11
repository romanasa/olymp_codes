#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

vector<string> A;
vector<vector<int> > d1, d2;
vector<vector<pair<int, int> > > p, dp1, dp2;
vector<int> path;
int n, m;

int dx[] = { -1, 0, 1, 0 };
int dy[] = { 0, 1, 0, -1 };

bool ok(int i, int j) { return i >= 0 && i < n && j >= 0 && j < m; }

void calc(int x, int y, vector<vector<int> > &d, bool need = false) {
	queue<pair<int, int> > q;
	for (int i = 0; i < n; i++)	fill(d[i].begin(), d[i].end(), 1e9);
	d[x][y] = 0;
	q.push({ x, y });
	while (q.size()) {
		int i = q.front().first, j = q.front().second;
		q.pop();
		for (int gg = 0; gg < 4; gg++) {
			int ni = i + dx[gg], nj = j + dy[gg];
			if (ok(ni, nj) && A[ni][nj] != '#' && d[ni][nj] > d[i][j] + 1) {
				d[ni][nj] = d[i][j] + 1, q.push({ ni, nj });
				if (need) p[ni][nj] = { i, j };
			}
		}
	}
}

void calc(int si, int sj, vector<pair<int, int> > path, vector<vector<pair<int, int> > > &dp) {
	set<pair<pair<int, int>, pair<int, int> > > S;
	
	for (int i = 0; i < n; i++) dp[i].assign(m, make_pair(-1, -1));
	
	for (int i = 0; i < (int)path.size(); i++) {
		dp[path[i].first][path[i].second] = { i, i };
		S.insert({ dp[path[i].first][path[i].second], path[i] });
	}
	
	while (S.size()) {
		int i = S.begin()->second.first;
		int j = S.begin()->second.second;
		auto cur = S.begin()->first;
		
		S.erase(S.begin());
		
		cur.first++;
		for (int gg = 0; gg < 4; gg++) {
			int ni = i + dx[gg], nj = j + dy[gg];
			if (!ok(ni, nj) || A[ni][nj] == '#') continue;
			
			if (cur.first < (int)path.size() && path[cur.first] == make_pair(ni, nj)) continue;
			
			if (dp[ni][nj] == make_pair( -1, -1 ) || dp[ni][nj] > cur) {
				S.erase({ dp[ni][nj], make_pair(ni, nj) });
				dp[ni][nj] = cur;
				S.insert({ dp[ni][nj], make_pair(ni, nj) });
			}
		}
	}
}

int sx, sy, fx, fy;

pair<int, int> solve() {
	vector<pair<int, int> > path;
	int ci = fx, cj = fy; 
	while (ci != -1 && cj != -1) {
		path.push_back({ ci, cj });
		tie(ci, cj) = p[ci][cj];
	}
	reverse(path.begin(), path.end());
	
	calc(sx, sy, path, dp1);
	
	reverse(path.begin(), path.end());
	calc(fx, fy, path, dp2);
	
	//err("path = {"); for (auto x : path) err(" (%d, %d)", x.first, x.second); err(" }\n");
	
	vector<vector<pair<int, int> > > E((int)path.size());
	
	/*
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) err("(%d, %d) ", dp1[i][j].first, dp1[i][j].second );
		err("\n");
	}
	err("\n\n\n");
	
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) err("(%d, %d) ", dp2[i][j].first, dp2[i][j].second );
		err("\n");
	}
	err("\n\n\n");
	*/
	
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			
			for (int gg = 0; gg < 4; gg++) {
				int ni = i + dx[gg], nj = j + dy[gg];
				if (!ok(ni, nj) || A[i][j] == '#' || A[ni][nj] == '#') continue;
				
				int l = dp1[i][j].second;
				int r = (int)path.size() - 1 - dp2[ni][nj].second;
				int dist = dp1[i][j].first + 1 + dp2[ni][nj].first;
				
				if (l != -1 && l < r) {
					E[l].push_back({ 1, dist });
					E[r].push_back({ -1, dist });
					
					//err("(%d, %d) -> (%d, %d), l = %d, r = %d, dist = %d\n", i, j, ni, nj, l, r, dist);
				}
			}
		}
	}
	
	//err("ok2\n");
	
	reverse(path.begin(), path.end());
	int ans = -1;
	pair<int, int> cur(-1, -1);
	
	multiset<int> S;
	for (int i = 0; i < (int)path.size(); i++) {
		for (auto c : E[i]) if (c.first == -1)
			S.erase(S.find(c.second));
		if (i && i + 1 < (int)path.size()) {
			if (S.empty()) return path[i];
			if (*S.begin() > ans) {
				ans = *S.begin();
				cur = path[i];
			}
		}
		for (auto c : E[i]) if (c.first == 1)
			S.insert(c.second);
	}
	//err("ans = %d\n", ans);
	return cur;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> m;
	cin >> sx >> sy >> fx >> fy;
	
	sx--, sy--, fx--, fy--;
	
	d1.resize(n), d2.resize(n), p.resize(n);
	dp1.resize(n), dp2.resize(n);
	for (int i = 0; i < n; i++) d1[i].resize(m), d2[i].resize(m), p[i].resize(m, make_pair(-1, -1));
	
	A.resize(n);
	for (int i = 0; i < n; i++) cin >> A[i];
	
	calc(sx, sy, d1, true);
	calc(fx, fy, d2);

	if (d1[fx][fy] == (int)1e9) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) if ((i != sx || j != sy) && (i != fx || j != fy) && A[i][j] == '.') {
				cout << i + 1 << " " << j + 1 << "\n";
				return 0;
			}
		}
	}
	
	
	auto c = solve();
	
	if (c.first == -1) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) if ((i != sx || j != sy) && (i != fx || j != fy) && A[i][j] == '.') {
				cout << i + 1 << " " << j + 1 << "\n";
				return 0;
			}
		}
	}
	cout << c.first + 1 << " " << c.second + 1 << "\n";
	return 0;
}