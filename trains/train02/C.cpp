#include <bits/stdc++.h>
#define err(...) //fprintf(stderr, __VA_ARGS__), fflush(stderr)
#define ll long long

using namespace std;

const ll inf = (ll)1e9 + 1;

ll sqr(ll x) {
	return x * x;
}

int main() {
	int n;
	scanf("%d", &n);
	
	vector<pair<ll, ll> > A(n);

	for (int i = 0; i < n; i++) {
		scanf("%I64d %I64d", &A[i].first, &A[i].second);
	}
	
	
	ll ans = (ll)8e18;
	for (int it = 0; it < 2; it++) {
	
		multiset<ll> S;
		for (int i = 0; i < n; i++) {
			S.insert(A[i].first);
			swap(A[i].first, A[i].second);
		}
		ans = min(ans, sqr(*S.rbegin() - *S.begin()));
	}
	
	for (int it = 0; it < 2; it++) {
	
		sort(A.begin(), A.end());	
		
		ll l = 0, r = (ll)1e9 + 7;
		
		vector<ll> P(n), S(n);
		
		P[0] = A[0].second;
		for (int i = 1; i < n; i++)
			P[i] = max(P[i - 1], A[i].second);
		
		S[n - 1] = A[n - 1].second;
		for (int i = n - 2; i >= 0; i--)
			S[i] = max(S[i + 1], A[i].second);
		
		
		vector<ll> P2(n), S2(n);
		
		P2[0] = A[0].second;
		for (int i = 1; i < n; i++)
			P2[i] = min(P2[i - 1], A[i].second);
		
		S2[n - 1] = A[n - 1].second;
		for (int i = n - 2; i >= 0; i--)
			S2[i] = min(S2[i + 1], A[i].second);
			
		while (r - l > 1) {
			ll m = (l + r) / 2;
			
			bool ok = false;
			
			err("check %I64d: ", m);
			
			ll cur = (ll)8e18 + 1;
			for (int L = 0; L < n; L++) {
				int ind1 = upper_bound(A.begin(), A.end(), make_pair(abs(A[L].first), inf)) - A.begin();
				int ind2 = upper_bound(A.begin(), A.end(), make_pair(m + A[L].first, inf)) - A.begin();
				
				ll maxy = 0;
				ll miny = 0;
				
				if (min(ind1, ind2) < n)
					maxy = max(maxy, S[min(ind1, ind2)]), miny = min(miny, S2[min(ind1, ind2)]);
				if (L)
					maxy = max(maxy, P[L - 1]), miny = min(miny, P2[L - 1]);	
				
				ll maxyt = max(abs(miny), abs(maxy));
										
				ll t = max(sqr(maxyt) + sqr(A[L].first), sqr(A[min(ind1, ind2) - 1].first - A[L].first));
				t = max(t, sqr(maxy - miny));
				
				
				err("(%d, %d), %I64d == %I64d, ", L, min(ind1, ind2), maxy, t);
				
				
				ans = min(ans, t);
				
				if (t <= m * m)
					ok = true;
			}
		
			if (ok)
				err("ok to %I64d\n", m);
			err("\n");
			if (ok) {
				r = m;
			} else {
				l = m;
			}
		}
		
		for (int L = 0; L < n; L++) {
			int ind1 = upper_bound(A.begin(), A.end(), make_pair(abs(A[L].first), inf)) - A.begin();
			int ind2 = upper_bound(A.begin(), A.end(), make_pair(r + A[L].first, inf)) - A.begin();
				
			
			ll maxy = 0;
			ll miny = 0;
				
			if (min(ind1, ind2) < n)
				maxy = max(maxy, S[min(ind1, ind2)]), miny = min(miny, S2[min(ind1, ind2)]);
			if (L)
				maxy = max(maxy, P[L - 1]), miny = min(miny, P2[L - 1]);	
				
			ll maxyt = max(abs(miny), abs(maxy));
									
			ll t = max(sqr(maxyt) + sqr(A[L].first), sqr(A[min(ind1, ind2) - 1].first - A[L].first));
			t = max(t, sqr(maxy - miny));
					
			ans = min(ans, t);
		}
		
		for (int i = 0; i < n; i++)
			A[i].first *= -1;
	}
	printf("%I64d\n", ans);
	
	return 0;
}