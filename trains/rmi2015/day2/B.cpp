#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

const int dd = (int)3e5 + 1;
int A[dd], L[dd], R[dd];
int cnt[dd], ans[dd];

struct req { int l, r, ind; } Q[dd];

const int sz = 400;


int sum = 0;
void upd(int pos) {
	sum -= cnt[pos];
	cnt[pos] ^= 1;
	sum += cnt[pos];
}

#define TASK "infinitywar"

int main() {
#ifndef HOME
	freopen(TASK".in", "r", stdin), freopen(TASK".out", "w", stdout);
#endif
	int n, q;
	scanf("%d %d", &n, &q);
	
	int ind = 0;
	for (int i = 0; i < n; i++) {
		int k;
		scanf("%d", &k);
		L[i] = ind;
		for (int j = 0; j < k; j++) scanf("%d", &A[ind++]);
		R[i] = ind - 1;
	}
	
	for (int i = 0; i < q; i++) {
		scanf("%d %d", &Q[i].l, &Q[i].r);
		Q[i].l = L[Q[i].l - 1];
		Q[i].r = R[Q[i].r - 1];
		Q[i].ind = i;
	}
	
	sort(Q, Q + q, [](req a, req b) {
		if (a.l / sz == b.l / sz) return a.r < b.r;
		return a.l / sz < b.l / sz;
	});
	
	
	int l = 0, r = 0;
	upd(A[0]);
	
	for (int i = 0; i < q; i++) {
		
		while (r + 1 <= Q[i].r) upd(A[r + 1]), r++;
		while (l - 1 >= Q[i].l) upd(A[l - 1]), l--;
		
		while (r > Q[i].r) upd(A[r]), r--;
		while (l < Q[i].l) upd(A[l]), l++;
	
		ans[Q[i].ind] = sum;
	}
	for (int i = 0; i < q; i++) printf("%d\n", ans[i]);
	return 0;
}