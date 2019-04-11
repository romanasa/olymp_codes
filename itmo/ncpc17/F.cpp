#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

struct Tree {
	
	int LOG;
	vector<vector<int> > UP;
	vector<int> h;
	
	int up(int v, int k) {
		for (int i = 0; i < LOG; i++) if ((k >> i) & 1)
			v = UP[v][i];	
		return v;
	}
	
	int lca(int a, int b) {
		if (h[b] > h[a]) swap(a, b);
		a = up(a, h[a] - h[b]);
		if (a == b) return a;
		for (int i = LOG - 1; i >= 0; i--) {
			if (UP[a][i] != UP[b][i])
				a = UP[a][i], b = UP[b][i];
		}
		return UP[a][0];
	}
	
	int dist(int a, int b) {
		int t = lca(a, b);
		return h[a] + h[b] - 2 * h[t];
	}
	
	Tree(vector<int> p) {
		int n = (int)p.size() + 1;
	
		h.assign(n, 0);
		
		LOG = 0;
		while ((1 << LOG) < n) LOG++;
		LOG++;
		
		UP.resize(n);
		for (int i = 0; i < n; i++) UP[i].resize(LOG);
		
		for (int i = 1; i < n; i++) {
			h[i] = h[p[i - 1]] + 1;	
			UP[i][0] = p[i - 1];
			for (int j = 1; j < LOG; j++) UP[i][j] = UP[UP[i][j - 1]][j - 1];
		}
	}
};

const ll MAXCMUL = (1ll << 30);

vector<vector<ll> > mul(vector<vector<ll> > A, vector<vector<ll> > B) {
	assert(A[0].size() == B.size());
	vector<vector<ll> > C(A.size(), vector<ll>(B[0].size(), 0));
	
	for (int i = 0; i < (int)A.size(); i++) {
		for (int j = 0; j < (int)B[0].size(); j++) {
			for (int t = 0; t < (int)B.size(); t++) {
				C[i][j] += A[i][t] * B[t][j];
				if (C[i][j] > MAXCMUL) C[i][j] = MAXCMUL;
			}
		}
	}
	return C;
}

vector<vector<ll> > power(vector<vector<ll> > A, int k) {
	if (k == 0) {
		int n = (int)A.size();
		vector<vector<ll> > one(n, vector<ll>(n, 0));
		for (int i = 0; i < n; i++) one[i][i] = 1;
		return one;
	}
	if (k & 1) return mul(power(A, k - 1), A);
	auto T = power(A, k / 2);
	return mul(T, T);
}

int main() {
	
	return 0;
}