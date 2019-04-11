#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

const int dd = (int)2e6 + 7;

struct pt { 
	int x, y, z, id; 
	pt() {}
	pt(int x, int y, int z): x(x), y(y), z(z) {}
	bool operator < (pt b) const {
		return y < b.y;
	}
};

struct node {
	vector<int> X;
	vector<int> F;
	
	void upd(int x, int val) {
		int pos = lower_bound(X.begin(), X.end(), x) - X.begin();
		for (int i = pos + 1; i < (int)F.size(); i += (i&-i))
			F[i] = max(F[i], val);
	}
	int get(int x) {
		int pos = lower_bound(X.begin(), X.end(), x) - X.begin() - 1;
		int res = 0;
		for (int i = (pos + 1); i > 0; i -= (i&-i)) res = max(res, F[i]);
		return res;
	}
} T[dd];

void build(int v, int tl, int tr, vector<pt> &A) {
	int len = tr - tl + 1;
	T[v].X.resize(len);
	T[v].F.resize(len + 1);
	
	if (tl == tr) {
		T[v].X[0] = A[tl].x;
	} else {
		int tm = (tl + tr) / 2;
		build(v * 2, tl, tm, A);
		build(v * 2 + 1, tm + 1, tr, A);
		merge(T[v * 2].X.begin(), T[v * 2].X.end(), T[v * 2 + 1].X.begin(), T[v * 2 + 1].X.end(), T[v].X.begin());
	}
}

int get(int v, int tl, int tr, int l, int r, int y) {
	if (tl == l && tr == r) return T[v].get(y);
	int tm = (tl + tr) / 2;
	if (r <= tm) return get(v * 2, tl, tm, l, r, y);
	if (l > tm) return get(v * 2 + 1, tm + 1, tr, l, r, y);
	return max(get(v * 2, tl, tm, l, tm, y), get(v * 2 + 1, tm + 1, tr, tm + 1, r, y));	
}

void upd(int v, int tl, int tr, int pos, int y, int val) {
	T[v].upd(y, val);
	if (tl != tr) {
		int tm = (tl + tr) / 2;
		if (pos <= tm) upd(v * 2, tl, tm, pos, y, val);
		else upd(v * 2 + 1, tm + 1, tr, pos, y, val);
	}
}

int get(int x, int y, vector<pt> &A) {
	int ind = lower_bound(A.begin(), A.end(), pt(0, x, 0)) - A.begin() - 1;
	//if (ind >= 0) err("get(%d, %d) = %d\n", ind, y, get(1, 0, (int)A.size() - 1, 0, ind, y));
	if (ind >= 0) return get(1, 0, (int)A.size() - 1, 0, ind, y);
	return 0;
}

void upd(int pos, int y, int val, vector<pt> &A) {
	upd(1, 0, (int)A.size() - 1, pos, y, val);
	//err("upd %d, %d,  (%d)\n", pos, y, val);
}

void clear(int v, int tl, int tr) {
	T[v].X.clear();
	T[v].F.clear();
	
	if (tl != tr) {
		int tm = (tl + tr) / 2;
		clear(v * 2, tl, tm);
		clear(v * 2 + 1, tm + 1, tr);
	}
}

int a, b, C = ~(1<<31), M = (1<<16)-1;
int r() {
	a = 36969 * (a & M) + (a >> 16);
	b = 18000 * (b & M) + (b >> 16);
	return (C & ((a << 16) + b)) % 1000000;
}


int main() {
	int n, m, AA, B;
	while (cin >> n >> m >> AA >> B) {
		if (n == 0 && m == 0) break;
		
		vector<pt> A(n + m);
		vector<int> Q(n + m), pos(n + m);
		for (int i = 0; i < n; i++) {
			cin >> A[i].x >> A[i].y >> A[i].z;
			A[i].id = i;
		}
		a = AA, b = B;
		for (int i = 0; i < m; i++) A[n + i].x = r(), A[n + i].y = r(), A[n + i].z = r(), A[n + i].id = n + i;
		n += m;
		
		sort(A.begin(), A.end(), [](pt a, pt b) {
			return a.y < b.y;
		});
		for (int i = 0; i < n; i++) pos[A[i].id] = i;
		
		build(1, 0, (int)A.size() - 1, A);
		
		vector<int> ind;
		for (int i = 0; i < (int)A.size(); i++) ind.push_back(i);
		sort(ind.begin(), ind.end(), [&](int a, int b) { return A[a].z < A[b].z; });
		
		int ans = 0;
		for (int i = 0; i < (int)A.size(); ) {
			int j = i;
			while (j < (int)A.size() && A[ind[j]].z == A[ind[i]].z) {
				Q[ind[j]] = get(A[ind[j]].y, A[ind[j]].x, A) + 1;
				ans = max(ans, Q[ind[j]]);
				j++;
			}
			for (int t = i; t < j; t++) upd(pos[A[ind[t]].id], A[ind[t]].x, Q[ind[t]], A);
			i = j;
		}
		clear(1, 0, (int)A.size() - 1);
		cout << ans << "\n";
	}
	return 0;
}