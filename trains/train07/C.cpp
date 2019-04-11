#include <bits/stdc++.h>
#define ll long long
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)
using namespace std;

const int dd = (int)1e5 + 1;

vector<int> R, G, B;

int cntR[11][11];
int cntB[11];
int cntG[11];

map<int, ll> inter(vector<int> a, vector<int> b) {
	map<int, ll> m1, m2, m3;
	for (int x : a) m1[x]++;
	for (int x : b) m2[x]++;
	for (int x : a) m3[x] = 1ll * m1[x] * m2[x];
	return m3;
}


pair<int, int> get(int x) {
	vector<int> cur;
	while (x || cur.empty()) {
		cur.push_back(x % 10);
		x /= 10;
	}
	return { cur.back(), cur[0] };
}

#define TASK "counting"

int main() {
#ifndef HOME
	freopen(TASK".in", "r", stdin), freopen(TASK".out", "w", stdout);
#endif
	int r, g, b;
	scanf("%d %d %d", &g, &r, &b);
	
	R.resize(r), G.resize(g), B.resize(b);
	
	for (int i = 0; i < g; i++) scanf("%d", &G[i]);
	for (int i = 0; i < r; i++) scanf("%d", &R[i]);
	for (int i = 0; i < b; i++) scanf("%d", &B[i]);
	
	for (int i = 0; i < r; i++) {
		auto c = get(R[i]);
		cntR[c.first][c.second]++;
	}
	
	for (int i = 0; i < g; i++) {
		auto c = get(G[i]);
		cntG[c.second]++;
	}
	
	for (int i = 0; i < b; i++) {
		auto c = get(B[i]);
		cntB[c.first]++;
	}
	
	ll ans = 0;
	for (int a = 0; a < 10; a++) {
		for (int b = 0; b < 10; b++) {
			ll t = 1ll * cntR[a][b] * cntB[b] * cntG[a];
			if (t) {
				ans += t;
				//err("a = %d, b = %d, t = %I64d\n", a, b, t);
			}
		}
	}
	
	
	//err("ans = %I64d\n", ans);
	
	for (auto t : inter(R, G)) {
		auto c = get(t.first);
		if (c.first != c.second) continue;
		ans -= 1ll * cntB[c.second] * t.second;
	}
	
	for (auto t : inter(R, B)) {
		auto c = get(t.first);
		if (c.first != c.second) continue;
		ans -= 1ll * cntG[c.first] * t.second;
	}
	
	for (auto t : inter(B, G)) {
		auto c = get(t.first);
		ans -= 1ll * t.second * cntR[c.second][c.first];
	}	
	//err("ans = %I64d\n", ans);
	
	map<int, int> m1, m2, m3;
	for (int x : R) m1[x]++;
	for (int x : G) m2[x]++;
	for (int x : B) m3[x]++;
	
	for (auto t : m1) {
		int x = t.first;
		auto c = get(x);
		ll cur = 1ll * m1[x] * m2[x] * m3[x];
		//err("x = %d, cur = %I64d\n", x, cur);
		if (c.first == c.second) ans += 2 * cur;
	}
	
	printf("%I64d\n", ans);
	return 0;
}