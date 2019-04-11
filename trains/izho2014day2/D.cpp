#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

struct magic {
	vector<int> T;
	int sz;
	
	void resize(int n) {
		T.resize(4 * n, -1);
		sz = n;
	}

	void upd(int pos, int val) { upd(1, 0, sz - 1, pos, val); }
	
	int getR(int pos, int val) { return getR(1, 0, sz - 1, pos, val); }
	
	int getL(int pos, int val) { return getL(1, 0, sz - 1, pos, val); }
	
	void upd(int v, int tl, int tr, int pos, int val) {
		if (tl == tr) T[v] = val;
		else {
			int tm = (tl + tr) / 2;
			if (pos <= tm) upd(v * 2, tl, tm, pos, val);
			else upd(v * 2 + 1, tm + 1, tr, pos, val);
			T[v] = max(T[v * 2], T[v * 2 + 1]);
		}
	}
	
	int getR(int v, int tl, int tr, int pos, int val) {
	
		if (T[v] < val) return sz;
		if (tr < pos) return sz;
		
		if (tl == tr) return tl;
		
		int tm = (tl + tr) / 2;
		
		int t = getR(v * 2, tl, tm, pos, val);
		if (t != sz) return t;
		return getR(v * 2 + 1, tm + 1, tr, pos, val);
	}
	
	int getL(int v, int tl, int tr, int pos, int val) {
	
		if (T[v] < val) return -1;
		if (tl > pos) return -1;
		
		if (tl == tr) return tl;
	
		int tm = (tl + tr) / 2;
		
		int t = getL(v * 2 + 1, tm + 1, tr, pos, val);
		if (t != -1) return t;
		return getL(v * 2, tl, tm, pos, val);
	}
};

#define TASK "ufo"

int main() {
#ifndef HOME
	freopen(TASK".in", "r", stdin), freopen(TASK".out", "w", stdout);
#endif
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int n, m, r, k, p;
	cin >> n >> m >> r >> k >> p;
	
	vector<magic> A(n), B(m);
	
	for (int i = 0; i < n; i++) A[i].resize(m);
	for (int j = 0; j < m; j++) B[j].resize(n);
	
	vector<vector<int> > a(n, vector<int>(m));
	
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++) cin >> a[i][j];
		
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			A[i].upd(j, a[i][j]);
			B[j].upd(i, a[i][j]);
		}
	}
	
	while (k--) {
		
		char c;
		int x, y;
		cin >> c >> x >> y;
		
		x--;
		
		if (c == 'W') {
			int pos = 0;
			for (int it = 0; it < r; it++) {
				int cur = A[x].getR(pos, y);
				if (cur == m) break;
				
				a[x][cur]--;
				
				A[x].upd(cur, a[x][cur]);
				B[cur].upd(x, a[x][cur]);
				
				pos = cur + 1;
			}
		}
		if (c == 'E') {
			int pos = m - 1;
			for (int it = 0; it < r; it++) {
				int cur = A[x].getL(pos, y);
				if (cur < 0) break;
				a[x][cur]--;
				
				A[x].upd(cur, a[x][cur]);
				B[cur].upd(x, a[x][cur]);
				
				pos = cur - 1;
			}
		}
		
		if (c == 'N') {
			int pos = 0;
			for (int it = 0; it < r; it++) {
				int cur = B[x].getR(pos, y);
				if (cur == n) break;
				
				a[cur][x]--;
				
				A[cur].upd(x, a[cur][x]);
				B[x].upd(cur, a[cur][x]);
				
				pos = cur + 1;
			}
		}
		if (c == 'S') {
			int pos = n - 1;
			for (int it = 0; it < r; it++) {
				int cur = B[x].getL(pos, y);
				if (cur < 0) break;
				
				a[cur][x]--;
				
				A[cur].upd(x, a[cur][x]);
				B[x].upd(cur, a[cur][x]);
				
				pos = cur - 1;
			}
		}
	}
	
	//for (int i = 0; i < n; i++)
	//	for (int j = 0; j < m; j++) err("%d%c", a[i][j], " \n"[j == m - 1]);
	
	ll ans = 0;
	for (int i = 0; i + p <= n; i++) {
		for (int j = 0; j + p <= m; j++) {
			ll cur = 0;
			for (int di = 0; di < p; di++) {
				for (int dj = 0; dj < p; dj++) {
					cur += a[i + di][j + dj];
				}
			}
			ans = max(ans, cur);
		}
	}
	cout << ans << "\n";
		
		
	return 0;
}