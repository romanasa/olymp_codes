#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

const int mod = (int)1e9 + 9;

int main() {
	int n, d;
	cin >> n >> d;
	
	vector<int> a(n);
	for (int i = 0; i < n; i++) cin >> a[i];
	
	sort(a.begin(), a.end());
	
	int j = 0;
	
	ll cnt = 1;
	for (int i = 1; i < n; i++) {
		while (a[j] < a[i] - d) j++;
		cnt = 1ll * cnt * (i - j + 1) % mod;
	}
	cout << cnt << "\n";
	return 0;
}