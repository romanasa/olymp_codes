#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

const int dd = (int)2e5 + 1;
struct req { int x, d, l; } Q[dd];

int main() {
	int n, q;
	scanf("%d %d", &n, &q);
	for (int i = 0; i < q; i++) scanf("%d %d %d", &Q[i].x, &Q[i].d, &Q[i].l);
	
	for (int i = 1; i <= n; i++) {
		ll cur = 0;
		for (int j = 0; j < q; j++) if (Q[j].x >= i && Q[j].d == 1) cur += Q[j].l;
		for (int j = 0; j < q; j++) if (Q[j].x <= i - 1 && Q[j].d == 2) cur += Q[j].l;
		printf("%I64d\n", cur);
	}
	
	return 0;
}