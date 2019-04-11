#include <bits/stdc++.h>
#define ll long long

using namespace std;

int get(int x) {
	for (int i = 30; i >= 0; i--) {
		if (x & (1 << i))
			return i;
	}
}

int getU(int x, int y) {
	int ans = 0;
		
	if (x & y)
		return 0;
	
	while (1) {
		if (x == 0 || ((x - 1) & y) > 0)
			return ans + 1;
		int t = (x&-x);
		x -= t;
		ans += t;	
	}
}

int getL(int x, int y) {
	int ans = 0;
	
	if (x & y)
		return 0;
	
	while (1) {
		if (y == 0 || ((y - 1) & x) > 0)
			return ans + 1;
		int t = (y&-y);
		y -= t;
		ans += t;	
	}
}

vector<vector<pair<int, int> > > E;

//set<pair<int, int>
map<pair<int, int>, int> M;
int nv = 1;

void check(int x, int y) {
	if (!M.count({ x, y }))
		M[{ x, y }] = nv++;
}

void go(int x, int y) {
	check(x, y);
		
	if (getL(x, y) > 1) {
		check(x, y - getL(x, y) + 1);
		go(x, y - getL(x, y) + 1);
	}
	if (getU(x, y) > 1) {
		check(x - getU(x, y) + 1, y);
		go(x - getU(x, y) + 1, y);
	}
}

vector<int> cnt;

int calc(int v) {
	for (auto c : E[v])
		cnt[v] += calc(c.first);
	return cnt[v];
}

ll ans = (ll)1e18 + 7;

ll F(int v) {
	ll cur = 0;
	for (auto c : E[v]) {
		cur += F(c.first) + 1ll * c.second * cnt[c.first];
	}
	return cur;
}

int n;

void dfs(int v, ll cur) {
	//printf("%d %d\n", v, cur);
	
	ans = min(ans, cur);
	for (auto c : E[v]) {
		int to = c.first;
		dfs(to, cur + 1ll * (n - cnt[to] - cnt[to]) * c.second);
	}
}

int main() {
	scanf("%d", &n);	
	
	vector<pair<int, int> > A(n);
	
	for (int i = 0; i < n; i++) {
		int x, y;
		scanf("%d %d", &x, &y);
		A[i] = { x, y };
		go(x, y);
	}
	
	vector<pair<int, int> > G;
	
	for (auto c : M)
		G.push_back(c.first);

		
	E.resize(nv);
		
	sort(G.begin(), G.end(), [](pair<int, int> a, pair<int, int> b) { 
		return a.first == b.first ? a.second < b.second : a.first < b.first;
	});
	
	for (int i = 1; i < (int)G.size(); i++) {
		if (G[i - 1].first == G[i].first && getL(G[i].first, G[i].second) >= G[i].second - G[i - 1].second)
			E[M[G[i - 1]]].push_back({ M[G[i]], G[i].second - G[i - 1].second });
	}
	
	sort(G.begin(), G.end(), [](pair<int, int> a, pair<int, int> b) { 
		return a.second == b.second ? a.first < b.first : a.second < b.second;
	});
	
	for (int i = 1; i < (int)G.size(); i++) {
		if (G[i - 1].second == G[i].second && getU(G[i].first, G[i].second) >= G[i].first - G[i - 1].first)
			E[M[G[i - 1]]].push_back({ M[G[i]], G[i].first - G[i - 1].first });
	}
	
	cnt.resize(nv);
	
	for (int i = 0; i < n; i++)
		cnt[M[A[i]]]++;
			
	int root = M[{ 0, 0 }];
	
	calc(root);
	dfs(root, F(root));
	printf("%lld", ans);
	/*for (auto c : M) {
		printf("(%d;%d) -> %d\n", c.first.first, c.first.second, c.second);
	}	
	
	for (int v = 0; v < nv; v++) {
		for (auto c : E[v]) {
			printf("%d--%d-->%d; ", v, c.second, c.first);
		}
		printf("\n");
	}*/
	
	
	return 0;
}
