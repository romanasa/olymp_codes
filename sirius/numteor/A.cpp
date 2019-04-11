#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

const int dd = (int)1e8 + 1;
const int maxC = (int)4e7 + 1;

bitset<dd> F;

int main() {
	ll L, R;
	cin >> L >> R;
	
	F[0] = F[1] = 1;
	
	if (R < dd) {
		for (ll i = 2; i * i < dd; i++) {
			if (F[i]) continue;
			for (ll j = i * i; j < dd; j += i) F[j] = 1;
		}
		int ans = 0;
		for (ll j = L; j <= R; j++) ans += (F[j] ^ 1);
		cout << ans << "\n";
		return 0;
	}
	
	for (ll i = 2; i * i <= R; i++) {
		if (F[i]) continue;
		for (ll j = i * i; j < maxC; j += i) F[j] = 1;
		for (ll j = (L + i - 1) / i * i; j <= R; j += i) F[j - L + maxC] = 1;
	}
	
	int ans = 0;
	for (ll j = L; j <= R; j++) ans += (F[j - L + maxC] ^ 1);
	cout << ans << "\n";
	
	return 0;
}