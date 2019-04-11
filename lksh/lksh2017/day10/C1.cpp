#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

const int dd = (int)1e3 + 7;

struct node {
	bitset<dd> T[dd];
	bitset<dd>& operator[](int x) { return T[x]; }
	void clear() { for (int i = 0; i < dd; i++) T[i].reset(); }
} T[4 * dd];

node C;
int n, m, k;
char A[dd][dd];

node merge(node A, node B) {
	C.clear();
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			for (int k = 0; k < n; k++) {
				C[i][j] = C[i][j] | (A[i][k] & B[k][j]);
			}
		}
	}
	return C;
}

void build(int v, int tl, int tr) {
	if (tl == tr) {
		T[v].clear();
		for (int i = 0; i < n; i++) {
			for (int j = i; j < n; j++) {
				if (A[j][tl] == '#') break;
				T[v][i][j] = 1;
			}
		}
	} else {
		int tm = (tl + tr) / 2;
		build(v * 2, tl, tm);
		build(v * 2 + 1, tm + 1, tr);
		T[v] = merge(T[v * 2], T[v * 2 + 1]);
	}
}

node get(int v, int tl, int tr, int l, int r) {
	if (tl == l && tr == r) return T[v];
	else {
		int tm = (tl + tr) / 2;
		if (r <= tm) return get(v * 2, tl, tm, l, r);
		else if (l > tm) return get(v * 2 + 1, tm + 1, tr, l, r);
		else return merge(get(v * 2, tl, tm, l, tm), get(v * 2 + 1, tm + 1, tr, tm + 1, r));
	}
}


int main() {
	scanf("%d %d %d\n", &n, &m, &k);
	
	for (int i = 0; i < n; i++) scanf("%s", A[i]);

	build(1, 0, m - 1);
	
	while (k--) {
		int i1, j1, i2, j2;
		scanf("%d %d %d %d", &i1, &j1, &i2, &j2);
		i1--, j1--, i2--, j2--;
		
		node cur = get(1, 0, m - 1, j1, j2);
		
		puts(cur[i1][i2] ? "YES" : "NO");
	}
	
	return 0;
}