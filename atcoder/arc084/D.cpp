#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

const int mod = 998244353;
const int dd = 4007;

int n;
bitset<dd> a[8], X;

void read(bitset<dd> &cur) {
	string s;
	cin >> s;
	int n = (int)s.size();
	for (int i = 0; i < n; i++) cur[n - i - 1] = (s[i] == '1');
}

int get(bitset<dd> &cur) {
	for (int i = dd - 1; i >= 0; i--) if (cur[i]) return i;
	return dd;
}

int main() {
	cin >> n;
	read(X);
	
	for (int i = 0; i < n; i++) read(a[i]);
	
	for (int i = 1; i < n; i++) {
		while (1) {
			int l = get(a[0]);
			int r = get(a[i]);
			if (l > r) swap(a[0], a[i]), swap(l, r);
			if (r == dd) break;
			a[i] ^= (a[0] << (r - l));
		}
	}
	int p = get(a[0]);
	int pw = 1, ans = 0;
	
	for (int i = p; i < dd; i++) {
		if (X[i]) ans = (ans + pw) % mod;
		pw = (pw + pw) % mod;
	}
	
	a[1].reset();
	for (int i = dd - 1; i >= p; i--) {
		if (a[1][i] != X[i]) {
			a[1] ^= (a[0] << (i - p));
		}
	}
	
	int ok = 1;
	for (int i = p - 1; i >= 0; i--) {
		if (a[1][i] < X[i]) break;
		if (a[1][i] > X[i]) { ok = 0; break; }
	}
	if (ok) ans = (ans + 1) % mod;
	cout << ans << "\n";
	return 0;
}