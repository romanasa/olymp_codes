#include <bits/stdc++.h>
#define ll long long

typedef long double ld;

using namespace std;

const int dd = (int)5e5 + 1;

struct ev { int q, s, ind; double t; } G[dd];

#define TASK "hiring"

int main() {
#ifndef HOME
	freopen(TASK".in", "r", stdin), freopen(TASK".out", "w", stdout);
#endif
	int n, w;
	scanf("%d %d", &n, &w);
	
	for (int i = 0; i < n; i++) {
		scanf("%d %d", &G[i].s, &G[i].q);
		G[i].t = G[i].s * 1.0 / G[i].q;
		G[i].ind = i + 1;
	}
	
	sort(G, G + n, [](ev a, ev b) { return a.t < b.t; });
	
	ll s = 0;
	int ans = -1, ind;
	ld cost = 0;

	priority_queue<int> S;
	
	for (int i = 0; i < n; i++) {
		S.push(G[i].q);
		s += G[i].q;
		
		double t = w / G[i].t;
		while (s > t) {
			s -= S.top();
			S.pop();
		}
		
		if ((int)S.size() > ans || (int)S.size() == ans && (int)S.size() * G[i].t < cost) {
			ans = (int)S.size();
			cost = (int)S.size() * G[i].t;
			ind = i;
		}
	}
	
	
	priority_queue<pair<int, int> > T;
	
	s = 0;
	
	for (int i = 0; i <= ind; i++) {
		T.push({ G[i].q, G[i].ind });
		s += G[i].q;
		
		double t = w / G[i].t;
		while (s > t) {
			s -= T.top().first;
			T.pop();
		}
	}
	
	vector<int> Ans;
	while (T.size()) 
		Ans.push_back(T.top().second), T.pop();
	
	printf("%d\n", (int)Ans.size());
	for (int x : Ans)
		printf("%d ", x);	
	return 0;
}