#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

vector<vector<int> > E;
vector<vector<ll> > H;

vector<int> cur, used;

void topsort(int v) {
	used[v] = 1;
	for (int to : E[v]) if (!used[to]) topsort(to);
	cur.push_back(v);
}

const int C = 120;

vector<ll> mod, A, B;

ll geth(int x, int it) {
	return (1ll * x * A[it] + B[it]) % mod[it];
}

bool prime(int x) {
	if (x < 2) return false;
	for (ll i = 2; i * i <= x; i++) if (x % i == 0) return false;
	return true;
}

mt19937 rnd(1);

void dfs(int v) {
	used[v] = 1;
	for (int to : E[v]) if (!used[to]) dfs(to);
}

int main() {
	
	for (ll cur = (ll)1e12; (int)mod.size() < C; cur++) {
		if (prime(cur)) mod.push_back(cur);
	}
	
	for (int it = 0; it < C; it++) {
		A.push_back(rnd());
		B.push_back(rnd());
	}

	int n, m;
	while (scanf("%d", &n)) {
		if (n == 0) break;
		
		scanf("%d", &m);
		
		
		E.resize(0);
		E.resize(n);
		
		used.assign(n, 0);
		H.assign(n, vector<ll>(0));
		vector<ll> X(n);
		
		for (int i = 0; i < m; i++) {
			int a, b;
			scanf("%d %d", &a, &b);
			E[a - 1].push_back(b - 1);
		}
		
		cur.clear();
		for (int i = 0; i < n; i++) if (!used[i]) topsort(i);
		
		for (int i = 0; i < n; i++) {
			H[i].resize(C);
			for (int it = 0; it < C; it++) {
				H[i][it] = geth(i, it);
			}
		}

		int ans = -1, ind = -1;
		vector<pair<int, int> > Q;
		
		for (int v : cur) {
			for (int to : E[v]) {
				//err("v = %d, to = %d\n", v, to);
				for (int it = 0; it < C; it++) {
					H[v][it] = min(H[v][it], H[to][it]);
				}
			}
			
			vector<ll> G;
			for (int it = 0; it < C; it++) {
				G.push_back(mod[it] / H[v][it] - 1);
			}
			sort(G.begin(), G.end());
			Q.push_back({ G[G.size() / 2], v });
		}
		
		sort(Q.rbegin(), Q.rend());
		
		for (int i = 0; i < min(C, (int)Q.size()); i++) {
			used.assign(n, 0);
			dfs(Q[i].second);
			int cur = accumulate(used.begin(), used.end(), 0);
			if (cur > ans) {
				ans = cur;
				ind = Q[i].second;
			}	
		}
		
		if (1ll * n * m < 1000 * 1000) {
			for (int i = 0; i < n; i++) {
				used.assign(n, 0);
				dfs(i);
				int cur = accumulate(used.begin(), used.end(), 0);
				if (cur > ans) {
					ans = cur;
					ind = i;
				}
			}
		}
				
		printf("%d %d\n", ind + 1, ans);
		
	}
	return 0;
}