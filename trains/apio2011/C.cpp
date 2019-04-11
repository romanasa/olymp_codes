#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

int P[13];
map<int, vector<int> > G;


void add(string &s) {
	int lmsk = 0;
	for (char &c : s) lmsk |= (1 << (c - 'A'));
	
	int len = (int)s.size();
	for (int msk = 0; msk < (1 << len); msk++) {
		int h = 0;
		for (int i = 0; i < len; i++) 
			h = h * 27 + (((msk >> i) & 1) ? s[i] - 'A' + 1 : 0);
		G[h].push_back(lmsk);
	}
}

int len;

int get(int h, int pos) {
	return h / P[pos] % 27;
}

int get(int h, int pos, int val) {
	return h + (val - get(h, pos)) * P[pos];
}

int calc(int cur, int msk, int del) {
	if (__builtin_popcount(msk) == len) return false;
		
	int ok = 0;
	for (int x : G[cur]) ok |= ((x & del) == 0);
	
	if (!ok) {
		return false;
	}
	
	if (__builtin_popcount(del) > len) {
		return true;
	}
	
	for (int c = 0; c < 26; c++) if ((((msk | del) >> c) & 1) == 0) {
		int t = calc(cur, msk, del | (1 << c));
		
		for (int i = 0; i < len && !t; i++) if (get(cur, i) == 0) 
			t |= calc(get(cur, i, c + 1), msk | (1 << c), del);
		
		if (!t) {
			return false;
		}
	}
	return true;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	P[0] = 1;
	for (int i = 1; i < 7; i++) P[i] = P[i - 1] * 27;
	
	int t;
	cin >> t;
	
	while (t--) {
		int n;
		cin >> n;
		
		vector<string> A(n);
		for (int i = 0; i < n; i++) cin >> A[i];
		
		int ok = 0;
		for (len = 1; len < 7 && !ok; len++) {
			G.clear();
			for (int i = 0; i < n; i++) if ((int)A[i].size() == len)
				add(A[i]);
			ok |= calc(0, 0, 0);
		}
		puts(ok ? "Yes" : "No");
	}
	return 0;
}