#include <bits/stdc++.h>
#define ll long long
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

#define TASK "trap"

const int dd = (int)1e5 + 7;
int x[dd], a[dd];

int main() {
#ifndef HOME
	freopen(TASK".in", "r", stdin), freopen(TASK".out", "w", stdout);
#endif	
	
	int n, k;
	int v1, v2, s;
	scanf("%d %d", &n, &k);
	scanf("%d %d", &v1, &v2);
	scanf("%d", &s);
	
	for (int i = 0; i < n; i++) scanf("%d %d", &x[i], &a[i]);
	
	if (s == 0) return 0 * puts("0");
	if (v1 >= v2) return 0 * puts("inf");
	
	ll q = 0;
	int pos = lower_bound(x, x + n, s) - x;
	
	multiset<int> S;
	
	for (int it = 0; it < k; it++) {		
		while (pos < n && x[pos] * (v2 - v1) < v2 * (s + 1ll * q * v1)) S.insert(a[pos++]);
		
		if (S.empty()) break;
		
		q += *S.rbegin();
		S.erase(--S.end());		
	}
	printf("%.10lf\n", (double)((long double)(s + 1ll * q * v1) * 1.0 / (v2 - v1) + q));
	return 0;
}