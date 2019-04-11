#include <bits/stdc++.h>
#define err(...) //fprintf(stderr, __VA_ARGS__), fflush(stderr)
#pragma GCC optimize("O3")

using namespace std;

typedef long long ll;

#ifndef HOME
	const int maxC = 107;
	const int dd = 107;
#else
	const int maxC = (int)1e6 + 7;
	const int dd = (int)3e4 + 7;
#endif

int cost[dd], p[dd];
int d;
vector<int> T[maxC];

struct myV : vector<int> {
	int mn = 0;
	int mx = 0;

	int& operator[] (int x) {
		return vector<int>::operator[](x + d + 2);
	}
	int operator[] (int x) const {
		return vector<int>::operator[](x + d + 2);
	}
} empt;
myV M[dd];

struct edge { int to, c; };
vector<vector<edge> > E;

void uin(int &a, int b) { if (a > b) a = b; }
void uax(int &a, int b) { if (a < b) a = b; }

myV mer(myV A, const myV &B, int add) {
	for (int i = B.mn; i <= B.mx; i++) {
		A[i + add] += B[i];
		uin(A.mn, i + add);
		uax(A.mx, i + add);
	}
	return A;
}
/*
unordered_map<int, int> mer(unordered_map<int, int> A, const unordered_map<int, int> &B, int add) {
	for (auto c : B) {
		A[c.first + add] += c.second;
	}
	return A;
}
*/
ll cnt = 0, sum = 0;

void merans(const myV &A, const myV &B, int cost) {
	ll ca = 0, cb = 0;
	
	for (int i = max(A.mn, -B.mx); i <= min(A.mx, -B.mn); i++) {
		ca += 1ll * A[i] * B[-i];
		cb += 1ll * A[i] * B[-i] * cost;
	}
	
	//err("cnt = %I64d\n", ca);
	cnt += ca;
	sum += cb;
}

void precalc(int v, int pr = -1) {
	M[v][0] = 1;
	for (auto &e : E[v]) if (e.to != pr) {
		precalc(e.to, v);
		cost[e.to] = 1, p[e.to] = v;
		M[v] = mer(M[v], M[e.to], cost[e.to]);
		T[e.c].push_back(e.to);
	}
}

vector<int> getpr(int st) {
	vector<int> pr;
	for (int t = st; t != -1; t = p[t]) pr.push_back(t);
	return pr;
}

myV cur;
	
void calc(int st, int c) {
	auto pr = getpr(st);
	reverse(pr.begin(), pr.end());
	
	cur.assign(2 * d + 7, 0);
	cur.mn = cur.mx = 0;
	
	for (int i = 0; i + 1 < (int)pr.size(); i++) {
		int v = pr[i];
		cur = mer(empt, cur, cost[v]);
		cur[0] += 1;
		for (auto &e : E[v]) if (e.to != pr[i + 1] && e.to != p[v]) 
			cur = mer(cur, M[e.to], cost[e.to]);
	}
	cur = mer(empt, cur, cost[st]);
	merans(M[st], cur, c);
}

void upd(int st, int nc) {
	auto pr = getpr(st);
	for (int i = (int)pr.size() - 2; i >= 0; i--) {
		int v = pr[i];
		for (int i = M[v].mn; i <= M[v].mx; i++) {
			M[p[v]][i + cost[v]] -= M[v][i];
			uin(M[p[v]].mn, i + cost[v]);
			uax(M[p[v]].mx, i + cost[v]);
		}
		//for (auto c : M[v]) M[p[v]][c.first + cost[v]] -= c.second;
	}
	cost[st] = nc;
	for (int i = 0; i + 1 < (int)pr.size(); i++) {
		int v = pr[i];
		for (int i = M[v].mn; i <= M[v].mx; i++) {
			M[p[v]][i + cost[v]] += M[v][i];
			uin(M[p[v]].mn, i + cost[v]);
			uax(M[p[v]].mx, i + cost[v]);
		}
		//for (auto c : M[v]) M[p[v]][c.first + cost[v]] += c.second;
	}
}

int n; 


vector<int> dist;
pair<int, int> bfs(int v) {
	dist.assign(n, (int)1e9);
	dist[v] = 0;
	
	queue<int> q;
	q.push(v);
	while (q.size()) {
		int v = q.front();
		q.pop();
		for (auto &e : E[v]) if (dist[e.to] > dist[v] + 1) {
			dist[e.to] = dist[v] + 1;
			q.push(e.to);
		}
	}
	int ind = max_element(dist.begin(), dist.end()) - dist.begin();
	return { ind, dist[ind] };
}

#define TASK "hidden"

int main() {
#ifndef HOME
	freopen(TASK".in", "r", stdin), freopen(TASK".out", "w", stdout);
#endif
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n;
	E.resize(n);
	for (int i = 0; i + 1 < n; i++) {
		int a, b, c;
		cin >> a >> b >> c;
		E[a - 1].push_back({ b - 1, c });
		E[b - 1].push_back({ a - 1, c });
	}
	
	
	auto c = bfs(0);
	int g;
	tie(g, d) = bfs(c.first);
	auto d1 = dist;
	bfs(g);
	auto d2 = dist;
	
	
	for (int i = 0; i < n; i++) {
		M[i].resize(2 * d + 7);
		M[i].mn = 0;
		M[i].mx = 0;
	}
	empt.resize(2 * d + 7);
	empt.mn = 0;
	empt.mx = 0;
	
	srand(135);
	
	int root = -1;
	for (int i = 0; i < n; i++) {
		if (d1[i] == d / 2 && d2[i] == (d + 1) / 2) root = i;
		if (d1[i] == (d + 1) / 2 && d2[i] == d / 2) root = i;
	}
	
	
	//int root = rand() % n;
	
	precalc(root);
	p[root] = -1; cost[root] = 0;
	
	for (int c = 1; c < maxC; c++) {
		//for (int v : T[c - 1]) upd(v, -1);
		for (int v : T[c]) {
			upd(v, 0);
			calc(v, c);
			upd(v, -1);
		}
	}
	
	//err("sum = %I64d, cnt = %I64d\n", sum, cnt);
	
	cout.precision(10);
	cout << fixed << sum * 1.0 / cnt << "\n";
	
	return 0;
}