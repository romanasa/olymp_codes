#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

const int LOG = 30;
const int dd = (int)1e7 + 7;

struct trie {
	int T[dd];
	int go[dd][2];
	int nv = 1, root = 0;
	
	trie() { for (int i = 0; i < dd; i++) go[i][0] = go[i][1] = -1, T[i] = (int)1e9; }
	
	void add(int x, int ind) {
		
		//err("add (%d, %d)\n", x, ind);
	
		int v = root;
		for (int i = LOG - 1; i >= 0; i--) {
			int t = (x >> i) & 1;
			if (go[v][t] == -1) go[v][t] = nv++;
			v = go[v][t];	
			T[v] = min(T[v], ind);
		}
	}
	
	int get(int a, int x) {
		int cur = (int)1e9;
		int v = root;
		int ok = 1;
		
		for (int i = LOG - 1; i >= 0; i--) {
			int t = (x >> i) & 1;
			int p = (a >> i) & 1;
			
			if (t == 0 && go[v][p ^ 1] != -1) cur = min(cur, T[go[v][p ^ 1]]);
			
			int q = -1;
			if (t == 0) q = p;
			else q = p ^ 1;
			
			if (go[v][q] == -1) { ok = 0; break; }
			v = go[v][q];
		}
		
		if (ok) cur = min(cur, T[v]);
		
		//err("get a = %d, x = %d\n",a , x);
		//err("res = %d\n", cur);
		
		return cur;
	}
} T;

#define TASK "c"

int main() {
#ifndef HOME
	freopen(TASK".in", "r", stdin), freopen(TASK".out", "w", stdout);
#endif
	int n, x;
	cin >> n >> x;
	
	vector<int> a(n), p(n + 1);
	for (int i = 0; i < n; i++) cin >> a[i];
	for (int i = 0; i < n; i++) p[i + 1] = p[i] ^ a[i];
	
	int ans = -1;
	int pos = -1;
	for (int i = 0; i <= n; i++) {
		int j = T.get(p[i], x);
		if (j < i) {
			int len = i - j;
			if (len > ans || len == ans && j < pos)
				ans = len, pos = j;
		}
		//err("i = %d, j = %d\n", i, j);
		T.add(p[i], i);
	}
	cout << pos + 1 << " " << ans << "\n";
	return 0;
}