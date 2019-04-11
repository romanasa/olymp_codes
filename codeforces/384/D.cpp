#include <bits/stdc++.h>
#define ll long long
#define err(...) //fprintf(stderr, __VA_ARGS__), fflush(stderr)
using namespace std;

const int dd = (int)2e5 + 7;

multiset<ll> S;
vector<vector<int> > E;

ll P[dd], G[dd];
ll ans = -(ll)1e18;

void dfs(int v, int pr) {
	err("v = %d, %I64d + %I64d\n", v, P[v], (S.size() ? *S.rbegin() : 0ll));
	if (S.size())
		ans = max(ans, P[v] + *S.rbegin());
		
	for (int to : E[v]) 
		if (to != pr)
			S.insert(G[to]);
		
	for (int to : E[v]) {
		if (to != pr) {
			S.erase(S.find(G[to]));
			dfs(to, v);
			S.insert(G[to]);
		}
	}
}

void calc(int v, int pr) {
	for (int to : E[v]) {
		if (to != pr) {
			calc(to, v);
			P[v] += P[to];
			G[v] = max(G[v], G[to]);
		}
	}
	G[v] = max(G[v], P[v]);
	err("P[%d] = %d, G[%d] = %d\n", v, P[v], v, G[v]);
}

int main() {
	int n;
	scanf("%d", &n);
	
	E.resize(n);
	
	fill(G, G + n, -(ll)1e18);
	
	for (int i = 0; i < n; i++)
		scanf("%I64d", &P[i]);
		
	for (int i = 0; i < n - 1; i++) {
		int a, b;
		scanf("%d %d", &a, &b);
		E[a - 1].push_back(b - 1);
		E[b - 1].push_back(a - 1);
	}
		
	calc(0, -1);
	dfs(0, -1);
	
	if (ans == -(ll)1e18)
		puts("Impossible");
	else
		printf("%I64d\n", ans);
	return 0;
}