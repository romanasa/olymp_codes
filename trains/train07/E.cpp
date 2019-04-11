#include <bits/stdc++.h>
#define ll long long
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

map<pair<int, int>, int> M;

#define TASK "parallelepiped"

const int dd = (int)1e6 + 1;

vector<int> E[dd]; 
unordered_set<int> S[dd];

int main() {
#ifndef HOME
	freopen(TASK".in", "r", stdin), freopen(TASK".out", "w", stdout);
#endif
	int n;
	scanf("%d", &n); 
	
	for (int i = 0; i < n; i++) {
		int a, b;
		scanf("%d %d", &a, &b);
		if (a > b) swap(a, b);
		M[{ a, b }]++;
	}
	
	vector<pair<int, int> > A;
	
	for (auto c : M) {
		for (int j = 0; j < c.second / 2; j++) {
			A.push_back(c.first);
		}
	}
	
	M.clear();
	
	for (auto c : A)
		M[c]++;
		
	ll ans = -1;
	
	for (auto c : A) {
		int a = c.first, b = c.second;
		
		if (a != b && M[{ a, b }] >= 2 && M[{ a, a }])
			ans = max(ans, 1ll * a * a * b);
		if (a != b && M[{ a, b }] >= 2 && M[{ b, b }])
			ans = max(ans, 1ll * a * b * b);
		if (a == b && M[{ a, b }] >= 3)
			ans = max(ans, 1ll * a * a * a);
	}
	
	
	auto tmp = A;
	
	A.clear();
	
	for (auto c : tmp) if (c.first != c.second)
		A.push_back(c);
		
	M.clear();
		
	int maxx = 0;
	
	for (auto c : A) {
		E[c.first].push_back(c.second);
		E[c.second].push_back(c.first);
		S[c.first].insert(c.second);
		S[c.second].insert(c.first);
		maxx = max(maxx, c.first);
		maxx = max(maxx, c.second);
	}
	
	for (auto c : A) {
		int a = c.first, b = c.second;
		
		if (1ll * a * b * maxx <= ans) continue;
		
		if (E[a].size() > E[b].size()) swap(a, b);
		for (int x : E[a]) {
			if (S[b].count(x)) {
				ans = max(ans, 1ll * a * b * x);
			}
		}
	}
	
	
	printf("%I64d\n", ans);
	return 0;
}