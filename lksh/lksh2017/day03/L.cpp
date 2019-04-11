#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

const int dd = (int)1e5 + 1;
int cnt[dd];


/*

0
1
2 2
3

*/

int main() {
	int n;
	scanf("%d", &n);
	
	int maxc = 0;
	
	for (int i = 0; i < n; i++) {
		int t;
		scanf("%d", &t);
		cnt[t]++;
		maxc = max(maxc, t);
	}
	
	for (int i = 0; i <= maxc; i++) if (!cnt[i]) return 0 * puts("Impossible");
	if (cnt[0] != 1) return 0 * puts("Impossible");
	
	ll s1 = 0, s2 = 0;
	ll sum = 0;
	
	for (int i = 0; i + 1 < maxc; i++) {
		s1 += cnt[i + 1];
		s1++;
	}
	
	if (maxc) s1 += cnt[maxc];
	
	for (int i = 0; i <= maxc; i++) {
		s2 += 1ll * 2 * cnt[i] * cnt[i + 1];
		s2 += 1ll * cnt[i] * (cnt[i] - 1);
	}
	
	printf("%lld %lld\n", s1, s2);
	
	return 0;
}