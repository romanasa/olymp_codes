#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int dd = (int)3e5 + 7;
ll ans[dd];
ll B[dd], T[dd];

set<pair<ll, ll> > S, J;

void add(ll l, ll r) {
	if (l <= r) {
		S.insert({ l, r });
		J.insert({ -(r - l + 1), l });
	}
}

int main() {
	ll m, n, q;
	scanf("%lld %lld %lld", &m, &n, &q);
	
	ll pr = 1;
	
	for (int i = 0; i < n; i++) {
		ll t;
		scanf("%lld", &t);
		
		T[i + 1] = t;
		
		add(pr, t - 1);
		pr = t + 1;
	}
	
	add(pr, m);
	
	for (int i = 0; i < q; i++)
		scanf("%lld", &B[i]);
	
	ll t = *max_element(B, B + q);
		
	for (ll it = 1; it <= min(t, m - n); it++) {
	
		ll l = -J.begin()->first, i = J.begin()->second;
		J.erase(J.begin());
		S.erase({ i, i + l - 1 });
		
		ll j = i + l / 2 + l % 2 - 1;
		
		ans[it] = j;
		
		add(i, j - 1);
		add(j + 1, i + l - 1);
	}
	
	for (int i = 0; i < q; i++) 
		if (B[i] > n)
			printf("%lld\n", ans[B[i] - n]);
		else
			printf("%lld\n", T[B[i]]);
		
	return 0;
}
