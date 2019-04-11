#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

vector<vector<int> > E;

const int dd = (int)1e5 + 1;

ll I[dd], D[dd];
ll ans;
int c[dd];

void dfs(int v, int pr = -1) {
	ll sum = 0;	
	for (int to : E[v]) if (to != pr) {
		dfs(to, v);
		sum += max(I[to], D[to]);
	}
	I[v] = D[v] = sum;
	for (int to : E[v]) if (to != pr) {
		sum -= max(I[to], D[to]);
		if (c[v] <= c[to]) {
			I[v] = max(I[v], I[to] + c[to] - c[v] + sum);
		} 
		if (c[v] >= c[to]) {
			D[v] = max(D[v], D[to] + c[v] - c[to] + sum);
		}
		sum += max(I[to], D[to]);
	}
	//err("v = %d, D[v] = %I64d, I[v] = %I64d\n", v + 1, D[v], I[v]);
}

int main() {
	int n;
	scanf("%d", &n);
	
	for (int i = 0; i < n; i++) scanf("%d", &c[i]);

	E.resize(n);
	for (int i = 0; i + 1 < n; i++) {
		int a, b;
		scanf("%d %d", &a, &b);
		E[a - 1].push_back(b - 1);
		E[b - 1].push_back(a - 1);
	}
	dfs(0);
	printf("%lld\n", max(I[0], D[0]));
	return 0;
}