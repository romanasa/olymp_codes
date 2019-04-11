#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

const int dd = (int)1e5 + 1;

ll x[dd], y[dd];

#define TASK "grid"

int main() {
#ifndef HOME
	freopen(TASK".in", "r", stdin), freopen(TASK".out", "w", stdout);
#endif
	int n, m;
	scanf("%d %d", &n, &m);
	
	int c;
	scanf("%d", &c);
	
	for (int i = 0; i < c; i++) {
		scanf("%lld %lld", &x[i], &y[i]);
	}
	
	ll m1 = -(ll)1e18;
	ll m2 = -(ll)1e18;
	ll m3 = -(ll)1e18;
	ll m4 = -(ll)1e18;
	
	for (int i = 0; i < c; i++) {
		m1 = max(m1, x[i] + y[i]);
		m2 = max(m2, x[i] - y[i]);
		m3 = max(m3, -x[i] + y[i]);
		m4 = max(m4, -x[i] - y[i]);
	}
	
	int h;
	scanf("%d", &h);
	
	ll ans = (ll)1e18;
	int pos = -1;
	
	for (int i = 0; i < h; i++) {
		ll a, b;
		scanf("%lld %lld", &a, &b);
		
		ll cur1 = -(a + b) + m1;
		ll cur2 = -(a - b) + m2;
		ll cur3 = -(-a + b) + m3;
		ll cur4 = -(-a - b) + m4;
		
		cur1 = abs(cur1);
		cur2 = abs(cur2);
		cur3 = abs(cur3);
		cur4 = abs(cur4);
		
		ll cur = max({ cur1, cur2, cur3, cur4 });
		if (cur < ans) {
			ans = cur;
			pos = i;
		}
	}
	printf("%lld\n%d\n", ans, pos + 1);
	
	return 0;
}