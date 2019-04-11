#include <bits/stdc++.h>
#define ll long long

using namespace std;

int main() {
	int n;
	scanf("%d", &n);
	
	ll l = -(ll)1e18;
	ll r = (ll)1e18;
	
	ll cur = 0;
	
	for (int i = 0; i < n; i++) {
		int t;
		scanf("%d", &t);
		if (i % 2 == 0) {
			cur += t;
			r = min(r, cur);
			cur += t;	
		} else {
			cur -= t;
			l = max(l, cur);
			cur -= t;
		}
	}
	printf("%I64d\n", max(r - l + 1, 0ll));
	return 0;
}