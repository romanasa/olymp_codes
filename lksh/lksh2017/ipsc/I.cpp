#include <bits/stdc++.h>
#define err(...) //fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

vector<vector<int> > E, ER;
vector<set<int> > EC, ECR;
vector<int> H, used, comp, A, B, sz, pos;

const int mod = (int)1e9 + 7;

void topsort(int v) {
	used[v] = 1;
	for (int to : E[v]) {
		if (!used[to]) topsort(to);
	}
	H.push_back(v);
}

void topsortC(int v) {
	used[v] = 1;
	for (int to : EC[v]) {
		if (!used[to]) topsortC(to);
	}
	H.push_back(v);
}

void mark(int v, int c) {
	comp[v] = c, sz[c]++;
	pos[c] = v;
	for (int to : ER[v]) {
		if (comp[to] == -1) mark(to, c);
	}
}

int main() {
	int t;
	scanf("%d", &t);
	
	while (t--) {
		int n, m;
		scanf("%d %d", &n, &m);
		
		E.resize(0), ER.resize(0);
		E.resize(n), ER.resize(n);
		
		vector<int> bad(n);
		
		for (int i = 0; i < m; i++) {
			int a, b;
			scanf("%d %d", &a, &b);
			if (a == b) bad[a - 1] = 1;
			E[a - 1].push_back(b - 1);
			ER[b - 1].push_back(a - 1);
		}
		
		used.assign(n, 0), H.clear();
		for (int i = 0; i < n; i++) if (!used[i]) topsort(i);
		
		reverse(H.begin(), H.end());
		
		err("ok topsort\n");
		
		comp.assign(n, -1);
		sz.assign(n, 0);
		pos.assign(n, -1);	
		
		//err("H = {"); for (int i : H) err(" %d,", i); err(" }\n");
		
		int cur = 0;
		for (int i : H) if (comp[i] == -1) mark(i, cur++);

		EC.resize(0), EC.resize(cur);
		ECR.resize(0), ECR.resize(cur);
		
		for (int v = 0; v < n; v++) {
			for (int to : E[v]) {
				if (comp[v] != comp[to]) {
					EC[comp[v]].insert(comp[to]);
					ECR[comp[to]].insert(comp[v]);
				}
			}
		}
		
		err("ok new graph\n");
		
		A.assign(cur, 0), B.assign(cur, 0);
		A[comp[0]] = 1;
		B[comp[n - 1]] = 1;
		
		used.assign(cur, 0), H.clear();
		for (int i = 0; i < cur; i++) if (!used[i]) topsortC(i);
		
		reverse(H.begin(), H.end());
		
		err("ok topsortC = {"); for (int x : H) err(" %d,", x); err("}\n");
		
		for (int x : H) {
			for (int to : EC[x]) {
				A[to] += A[x];
				if (A[to] >= mod) A[to] -= mod;
			}
		}
		
		err("calc A = {"); for (int i = 0; i < cur; i++) err(" %d,", A[i]); err("}\n");
		
		reverse(H.begin(), H.end());	
		
		for (int x : H) {
			for (int to : ECR[x]) {
				B[to] += B[x];
				if (B[to] >= mod) B[to] -= mod;
			}
		}
		
		err("calc B\n");
		reverse(H.begin(), H.end());	
		
		vector<int> ans;
		
		for (int v : H) {
			if (A[comp[n - 1]] && 1ll * A[v] * B[v] % mod == A[comp[n - 1]] && sz[v] == 1 && !bad[pos[v]]) {
				ans.push_back(pos[v]);
			}
		}
		
		printf("%d\n", (int)ans.size());
		for (int x : ans) printf("%d ", x + 1); printf("\n");
	}
	return 0;
}