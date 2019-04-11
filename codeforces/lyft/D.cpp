#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

const ll mod = 998244353;

ll sq(ll x) {
	ll l = 0, r = 2e6;
	while (r - l > 1) {
		ll m = (l + r) / 2;
		if (m * m * m <= x) l = m;
		else r = m;
	}
	return l;
}

int main() {
	int n; cin >> n;
	
	vector<ll> A(n);
	for (int i = 0; i < n; i++) cin >> A[i];
	
	ll ans = 1;
	map<ll, ll> M;
	
	for (int i = 0; i < n; i++) {
		ll x = A[i];
		ll t1 = sqrt(x);
		
		if (t1 * t1 < x) t1++;
		if (t1 * t1 == x) {
			ll t2 = sqrt(t1);
			
			if (t2 * t2 < t1) t2++;
			if (t2 * t2 == t1) M[t2] += 4;
			else M[t1] += 2;
			
		} else {
		
			ll t = sq(x);
			if (t * t * t == x) {
				M[t] += 3;
			} else {
				set<ll> S;
    			for (int j = 0; j < n; j++) if (i != j && A[i] != A[j]) {
    				ll cur = __gcd(A[i], A[j]);
    				if (cur > 1 && cur < x) S.insert(cur);
    			}
    			
    			int fst = 1, cnt = 0;
    			for (int j = 0; j < n; j++) if (A[i] == A[j]) {
 					if (j < i) fst = 0;
 					cnt++;
       			}
    			
    			if (S.size() == 1) S.insert(x / *S.begin());
    			
    			if (S.empty()) {
    				ll q = (cnt + 1) % mod;
    				q = q * q % mod;
    				if (fst) ans = ans * q % mod;
    			} else {
    				assert(S.size() == 2);
    				M[*S.begin()]++;
    				M[*S.rbegin()]++;
    			}
			}
		}
	}

	for (auto c : M) {
		ans = ans * (c.second + 1) % mod;
	}
	cout << ans << "\n";
	return 0;
}