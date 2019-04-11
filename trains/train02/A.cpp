#include <bits/stdc++.h>
#define ll long long
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)
using namespace std;

const int dd = (int)2e5 + 7;

vector<pair<int, int> > E[dd];
vector<int> T[dd];

int n, m, cnt;
int LOG[dd];
	
struct dsu {
	int P[dd], R[dd];
	dsu() { for (int i = 0; i < dd; i++) P[i] = i, R[i] = 1; }
	void clear() { for (int i = 0; i < dd; i++) P[i] = i, R[i] = 1; cnt = n; }
	int get(int v) { return v == P[v] ? v : P[v] = get(P[v]); }
	void un(int a, int b) {
		if ((a = get(a)) != (b = get(b))) {
			if (R[b] > R[a]) swap(a, b);
			P[b] = a, R[a] += R[b], cnt--;
		}
	}
} A, B;

int main() {
	scanf("%d %d", &n, &m);
	
	for (int i = 2; i <= n; i++) {
		LOG[i] = LOG[i >> 1] + 1;
	}
		
	for (int i = 0; i < m; i++) {
		int s, l1, l2;
		scanf("%d %d %d", &s, &l1, &l2);
		
		l1--, l2--;
	
		
		int k = LOG[s];
		//err("%d = LOG[%d]\n", k, s);
		E[k].push_back({ l1, l2 });
		E[k].push_back({ l1 + s - (1 << k), l2 + s - (1 << k) });
	}
	
	for (int k = LOG[n]; k > 0; k--) {
		A.clear();
		/*
		err("level %d: \n", k);
		for (auto c : E[k]) {
			err("(%d, %d), ", c.first, c.second);
		}
		err("\n");
		*/
		for (auto c : E[k]) {
			A.un(c.first, c.second);
		}

		for (int i = 0; i + (1 << k) - 1 < n; i++) {
			T[A.get(i)].push_back(i);
		}
		
		for (int i = 0; i + (1 << k) - 1 < n; i++) {
			for (int j = 0; j + 1 < (int)T[i].size(); j++) {
				E[k - 1].push_back({ T[i][j], T[i][j + 1] });
				E[k - 1].push_back({ T[i][j] + (1 << (k - 1)), T[i][j + 1] + (1 << (k - 1)) });
			}
		}
		
		for (int i = 0; i + (1 << k) - 1 < n; i++) T[i].clear();
	}
	A.clear();	
	for (auto c : E[0]) {
		A.un(c.first, c.second);
	}
	
	int MOD = (int)1e9 + 7, ans = 1;
	for (int i = 0; i < cnt; i++)
		ans = (1ll * ans * 26) % MOD;
	printf("%d\n", ans);
	
	return 0;
}