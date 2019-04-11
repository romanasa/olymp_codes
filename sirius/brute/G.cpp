#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

int l, m1, m2, m3, n, m;
string s;

int cnt[(1 << 15) + 1];
short F[(1 << 26) + 1];
char C[(1 << 26) + 1];
int G[31], R[31];
int P[31];

int Max(int, int, int, int);

int Min(int msk, int cnt, int alpha, int beta) {
	if (cnt == l) return C[msk];
	int best = beta;
	for (int j = 0; j < 26; j++) if (!((msk >> j) & 1)) {
		int val = Max(msk ^ (1 << P[j]), cnt + 1, alpha, best);
		if (val < best) best = val;
		if (best <= alpha) return alpha;
	}
	return best;
}

int Max(int msk, int cnt, int alpha, int beta) {
	if (cnt == l) return C[msk];
	int best = alpha;	
	for (int j = 0; j < 26; j++) if (!((msk >> j) & 1)) {
		int val = Min(msk ^ (1 << P[j]), cnt + 1, best, beta);	
		if (val > best) best = val;
		if (best >= beta) return beta;
	}
	return best;
}

int main() {
	for (int i = 1; i < (1 << 15); i++) cnt[i] = cnt[i >> 1] + (i & 1);
	
	/*for (int i = 1; i < (1 << 26); i++) {
		if (i & 1) low[i] = 0;
		else low[i] = low[i >> 1] + 1;
	}*/
	
	cin >> l >> n;
	
	for (int i = 0; i < n; i++) {
		cin >> s;
		for (char c : s) G[c - 'a'] |= (1 << i);
	}
	
	cin >> m;
	for (int j = 0; j < m; j++) {
		cin >> s;
		for (char c : s) R[c - 'a'] |= (1 << j);
	}
	m1 = (1 << n) - 1, m2 = (1 << m) - 1;
	m3 = (1 << 26) - 1;
	
	l = min(l, max(n, m));
	
	for (int i = 0; i < (1 << 26); i++) {
		if (i) {
			int t = 0;
			while (((i >> t) & 1) == 0) t++;
			F[i] = F[i ^ (1 << t)] | G[t];
		}
		C[i] += cnt[m1 ^ F[i]];
	}
	
	for (int i = 0; i < (1 << 26); i++) {
		if (i) {	
			int t = 0;
			while (((i >> t) & 1) == 0) t++;
			F[i] = F[i ^ (1 << t)] | R[t];
		}
		C[i] -= cnt[m2 ^ F[i]];
	}
	
	for (int i = 1; i < (1 << 26); i++) {
		if (i & 1) F[i] = 0;
		else F[i] = F[i >> 1] + 1;
	}

	for (int i = 0; i < 26; i++) P[i] = i;
	
	err("precalc = %.3fs\n", clock() * 1.0 / CLOCKS_PER_SEC); 
	cout << Max(0, 0, -(int)1e9, (int)1e9) << "\n"; 
	err("time = %.3fs\n", clock() * 1.0 / CLOCKS_PER_SEC);
	return 0;
}