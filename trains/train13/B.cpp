#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

const int MAXMEM = (int)1e8;
char MEM[MAXMEM];
int mpos;

inline void* operator new (size_t n) {
	char *res = MEM + mpos;
	mpos += n;
	return (void*) res;
}

inline void operator delete(void*) { }

struct SS {
	multiset<int> S;
	int push = 0;
};

struct edge { int to, l, t; };

vector<vector<edge>> E;

int ans = 0;
const int dd = (int)1e5 + 1;
int dp[dd];

SS dfs(int v, int pr = -1) {
	int cnt = 0;
	for (auto &e : E[v]) if (e.to != pr) cnt++;	

	SS S;
	
	if (cnt) S.S.insert(0), dp[v] = -(int)2e9;
	else dp[v] = (int)2e9, ans++;
	
	for (auto &e : E[v]) if (e.to != pr) {
		auto cS = dfs(e.to, v);
		cS.push += e.l;
		
		while (cS.S.size() && *(cS.S).rbegin() + cS.push > e.t) {
        	cS.S.erase((--cS.S.end()));
        }
		
		if (cS.S.size() > S.S.size()) swap(cS, S);
		for (int x : cS.S) S.S.insert((x + cS.push) - S.push);
	}
	
	for (auto &e : E[v]) if (e.to != pr) {
		dp[v] = max(dp[v], min(dp[e.to], e.t) - e.l); 
	}
	
    while (S.S.size() && *(S.S).begin() + S.push <= dp[v]) S.S.erase(S.S.begin()), ans++;
    
    return S;
}

#define TASK "evacuation"

int main() {
#ifndef HOME
	freopen(TASK".in", "r", stdin), freopen(TASK".out", "w", stdout);
#endif
	int n;
	scanf("%d", &n);
	E.resize(n);
	
	for (int i = 0; i + 1 < n; i++) {
		int a, b, l, t;
		scanf("%d %d %d %d", &a, &b, &l, &t);
		E[a - 1].push_back({ b - 1, l, t });
		E[b - 1].push_back({ a - 1, l, t });
	}
	
	int root = 0;
	for (int i = 0; i < n; i++) if (E[i].size() > 1) root = i;
	dfs(root);
	printf("%d\n", ans);
	return 0;
}