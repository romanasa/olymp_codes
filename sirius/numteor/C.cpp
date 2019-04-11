#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

const int dd = (int)5e6 + 1;

bitset<dd> F;
int ls[dd];
ll cur[dd];

int main() {
	cur[1] = 1, F[1] = 1;
	
	for (int i = 2; i < dd; i++) {
		if (F[i]) continue;	
		ls[i] = i;
		for (ll j = 1ll * i * i; j < dd; j += i) {
			ls[j] = i, F[j] = 1;
		}
	}
	
	for (int i = 2; i < dd; i++) {
		ll t = 1;
		int x = i;
		
		cur[i] = 1;
		
		while (x > 1) {
			int q = ls[x];
			ll c = 1, s = 0;	
			while (x % c == 0) {
				s += c;
				c *= q;
			}
			c /= q;
			x /= c;
			t = t * s;
		}
		cur[i] = t;
	}

	for (int i = 1; i < dd; i++) cur[i] += cur[i - 1];

	
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int l, r;
	while (cin >> l >> r) {
		cout << cur[r] - (l ? cur[l - 1] : 0) << "\n";
	}
	return 0;
}