#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

const int dd = 251;

int n;
int G[dd][dd], used[dd];
int A, B;
int cA, cB;

void no() {
	cout << "-1\n";
	exit(0);
}

void dfs0(int v) {
	used[v] = 1;
	for (int i = 0; i < n; i++) if (G[v][i] == 0 && !used[i])
		dfs0(i);
}

void dfs1(int v) {
	used[v] = 1;
	for (int i = 0; i < n; i++) if (G[v][i] == 1 && !used[i])
		dfs1(i);
}

void getState() {
	fill(used, used + n, 0); dfs0(0);
	if (*min_element(used, used + n) == 1) cA = 1;
	 
	fill(used, used + n, 0); dfs1(0);
	if (*min_element(used, used + n) == 1) cB = 1;
}

void flip() {
	swap(A, B);
	swap(cA, cB);
	for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) G[i][j] ^= 1;
}

struct edge {
	int to, f, c, back;
};

struct Dinic {
	vector<vector<edge> > E;
	vector<int> d, head;
	int n;
	
	void resize(int _n) {
		n = _n;
		E.clear();
		E.resize(n);
		d.resize(n), head.resize(n);
	}
	
	void clear() {
		for (int v = 0; v < n; v++)
			for (auto &e : E[v]) e.f = 0;
	}

	void add(int a, int b, int c) {
		int ia = (int)E[b].size();
		int ib = (int)E[a].size();
		E[a].push_back({ b, 0, c, ia });
		E[b].push_back({ a, 0, c, ib });
	}
	
	int bfs(int s, int t) {
		queue<int> q;
		d.assign(n, (int)1e9);
		
		d[s] = 0;
		q.push(s);
		
		while (q.size()) {
			int v = q.front(); q.pop();
			for (auto &e : E[v]) if (e.f < e.c && d[e.to] > d[v] + 1) 
				d[e.to] = d[v] + 1, q.push(e.to);
		}
		return d[t] == (int)1e9 ? -1 : 1;
	}
	
	int dfs(int v, int t, int cmin) {
		if (v == t) return cmin;
		for (; head[v] < (int)E[v].size(); head[v]++) {
			auto &e = E[v][head[v]];
			if (d[e.to] == d[v] + 1 && e.f < e.c) {
				int f = dfs(e.to, t, min(cmin, e.c - e.f));
				if (f) {
					e.f += f;
					E[e.to][e.back].f -= f;
					return f;
				}
			}
		}
		return 0;
	}
	
	int flow(int s, int t) {
		int f = 0;
		while (bfs(s, t) != -1) {		
			head.assign(n, 0);
			while (1) {
				int add = dfs(s, t, (int)1e9);
				if (!add) break;
				f += add;
			}
		}
		return f;
	}
	
	vector<int> used;
	
	void go(int v) {
		used[v] = 1;
		for (auto &e : E[v]) if (e.f < e.c && !used[e.to]) 
			go(e.to);
	}
	
	void restore(int s, int t) {
		used.assign(n, 0);
		go(s);
		
		vector<pair<int, int> > ans;
		for (int v = 0; v < n; v++) if (used[v]) {
			for (auto &e : E[v]) if (e.f > 0 && !used[e.to]) {
				ans.push_back({ v, e.to });
			}
		}
		cout << ans.size() << "\n";
		for (auto c : ans) cout << c.first + 1 << " " << c.second + 1 << "\n";
	}
	
} F;

void findCut() {
	
	F.resize(n);

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < i; j++) if (G[i][j]) {
			F.add(i, j, 1);
			//err("add (%d, %d)\n", i, j);
		}
	}
	
	int ans = (int)1e9, ind = -1;
	for (int i = 1; i < n; i++) {
		F.clear();
		int c = F.flow(0, i);
		//err("flow (%d, %d) = %d\n", 0, i, c);
		if (c < ans) {
			ans = c, ind = i;
		}
	}
	
	F.clear();
	F.flow(0, ind);
	F.restore(0, ind);
}

vector<int> cur;

void comp(int v) {
	used[v] = 1;
	for (int i = 0; i < n; i++) if (G[v][i] == 1 && !used[i])
		comp(i);
	cur.push_back(v);
}

bool check(int a, int b) {
	
						G[a][b] ^= 1;
						G[b][a] ^= 1;
	
	int c = 0;
	fill(used, used + n, 0); dfs0(0);
	if (*min_element(used, used + n) == 1) c = 1;
	
						G[a][b] ^= 1;
						G[b][a] ^= 1;
	return c;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n;
	
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> G[i][j];
		}
	}
	
	cin >> A >> B;
	
	getState();
	
	
	if (A == 0 && B == 0) no();
	if (cA == A && cB == B) return 0 * puts("0");
	
	if (A == 1 && B == 1) {
		if (n == 3) no();
		if (cB == 1) flip();
		
		fill(used, used + n, 0);
		
		vector<vector<int> > T;
		
		for (int i = 0; i < n; i++) if (!used[i]) {
			cur.clear();
			comp(i);
			T.push_back(cur);
		}
		
		sort(T.begin(), T.end(), [](const vector<int> &A, const vector<int> &B) {
			return A.size() > B.size();
		});
		
		if (T.size() == 2 && (int)T[0].size() == n - 1 && (int)T[1].size() == 1) {
			
			cout << "2\n";
			cout << T[0][0] + 1 << " " << T[1][0]+ 1  << "\n";
			cout << T[0][0] + 1 << " " << T[0][1]+ 1  << "\n";
			return 0;
		}
		vector<pair<int, int> > ans;
		for (int i = 1; i < (int)T.size(); i++) {
			auto &cur = T[i];
			
			int ok = 0;
			for (int a : T[0]) {
				for (int b : cur) if (G[a][b] == 0) {
				
					if (check(a, b)) {
						G[a][b] ^= 1;
						G[b][a] ^= 1;
						ans.push_back({ a, b });
						ok = 1;
						
						for (int x : cur) T[0].push_back(x);
						
						break;
					}
				}
				if (ok) break;
			}
			if (!ok) no();
			cur.clear();
		}
		cout << ans.size() << "\n";
		for (auto c : ans) cout << c.first + 1 << " " << c.second + 1 << "\n";
	} else {
		if (A == 0 && B == 1) flip();
		findCut();
	}
	
	return 0;
}