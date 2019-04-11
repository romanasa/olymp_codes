#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

ll len;

ll dist(ll a, ll b) {
	if (a <= b) return b - a;
	return len - b + a;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n;
	ll k;
	cin >> n >> k;
	
	vector<ll> A(n);
	
	for (int i = 0; i < n; i++) {
		ll x; cin >> x;
		A[i] = len;
		len += x;
		//err("A[%d] = %I64d\n", i, A[i]);
	}
	for (int i = 0; i < n; i++) A.push_back(A[i] + len);
	
	ll l = 0, r = len;
	while (r - l > 1) {
		ll m = (l + r) / 2;
		//m = 7;
		auto nxt = [&](int j) {
			return j + 1;
		};
		
		ll cur = 0;
		
		int j = 0;
		for (int i = 0; i < n; i++) {
			//j = max(j, i);
			
			while (dist(A[i], A[j]) <= m) {
				//err("ch %d, %d\n", i, j);
				j = nxt(j);
				if (j == i) break;
			}
			cur += min(j - i, n) - 1;
			//err("i = %d, j = %d, m = %I64d\n", i, j, m);
		}
		//err("m = %I64d,cur = %I64d\n", m, cur);
		//break;
		if (cur >= k) r = m;
		else l = m;
	}
	cout << r << "\n";
	return 0;
}
