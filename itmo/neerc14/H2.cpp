#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)
#pragma GCC optimize ("O3")

using namespace std;

typedef long long ll;

	const int maxC = (int)1e6 + 7;
	const int dd = (int)3e4 + 7;
/*
const int MAXMEM = (int)2e8;
char MEM[MAXMEM];
int mpos;

inline void* operator new(size_t n) {
	if (mpos + n >= MAXMEM) mpos = 0;
	char *res = MEM + mpos;
	mpos += n;
	return (void*)res;
}*/

unordered_map<int, int> M[dd];
int cost[dd], p[dd];
map<int, vector<int> > T;

struct edge { 
	int to, c; 
	edge() {}
	edge(int to, int c): to(to), c(c) {}
};
vector<vector<edge> > E;

unordered_map<int, int> mer(unordered_map<int, int> A, const unordered_map<int, int> &B, int add) {
	for (auto c : B) {
		A[c.first + add] += c.second;
	}
	return A;
}

ll cnt = 0, sum = 0;

void merans(const unordered_map<int, int> &A, const unordered_map<int, int> &B, int cost) {
	ll ca = 0, cb = 0;
	for (auto c : A) {
		auto it = B.find(-c.first);
		if (it != B.end()) {
			ca += 1ll * c.second * it->second;
			cb += 1ll * c.second * it->second * cost;
		}
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

void calc(int st, int c) {
	auto pr = getpr(st);
	reverse(pr.begin(), pr.end());
	unordered_map<int, int> P, cur;
	for (int i = 0; i + 1 < (int)pr.size(); i++) {
		int v = pr[i];
		cur = mer(unordered_map<int, int>(), cur, cost[v]);
		cur[0] += 1;
		for (auto &e : E[v]) if (e.to != pr[i + 1] && e.to != p[v]) 
			cur = mer(cur, M[e.to], cost[e.to]);
	}
	cur = mer(unordered_map<int, int>(), cur, cost[st]);
	merans(M[st], cur, c);
}

void upd(int st, int nc) {
	auto pr = getpr(st);
	for (int i = (int)pr.size() - 2; i >= 0; i--) {
		int v = pr[i];
		for (auto c : M[v]) M[p[v]][c.first + cost[v]] -= c.second;
	}
	cost[st] = nc;
	for (int i = 0; i + 1 < (int)pr.size(); i++) {
		int v = pr[i];
		for (auto c : M[v]) M[p[v]][c.first + cost[v]] += c.second;
	}
}

void upd2(int st, int nc) {
	auto pr = getpr(st);
	cost[st] = nc;
	
	for (int i = 1; i < (int)pr.size(); i++) {
		int v = pr[i];
		M[v].clear();
		M[v][0] = 1;
		for (auto &e : E[v]) if (e.to != p[v]) {
			M[v] = mer(M[v], M[e.to], cost[e.to]);
		}
	}
}

#define TASK "hidden"

int main() {
#ifndef HOME
	freopen(TASK".in", "r", stdin), freopen(TASK".out", "w", stdout);
#endif
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int n; cin >> n;
	E.resize(n);
	for (int i = 0; i + 1 < n; i++) {
		int a, b, c;
		cin >> a >> b >> c;
		E[a - 1].push_back(edge( b - 1, c ));
		E[b - 1].push_back(edge( a - 1, c ));
	}
	
	precalc(0);
	p[0] = -1; cost[0] = 0;
	
	for (auto tt : T) {
		int c = tt.first;
		//for (int v : T[c - 1]) upd(v, -1);
		for (int v : tt.second) {
			upd(v, 0);
			calc(v, c);
			upd(v, -1);
		}
		if (clock() > 2.5 * CLOCKS_PER_SEC) break;
	}
	
	//err("sum = %I64d, cnt = %I64d\n", sum, cnt);
	
	cout.precision(10);
	cout << fixed << sum * 1.0 / cnt << "\n";
	
	return 0;
}