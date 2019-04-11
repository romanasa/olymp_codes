#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

int cnt[41][2];

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int n; ll k;
	cin >> n >> k;
	
	vector<ll> A(n);
	for (int i = 0; i < n; i++) cin >> A[i];
	
	for (int bit = 39; bit >= 0; bit--) {
		for (int i = 0; i < n; i++)
			cnt[bit][(A[i] >> bit) & 1]++;
	}
	
	
	ll ans = 0;
	for (int i = 0; i < n; i++) ans += (A[i] ^ k);
	
	for (int st = 39; st >= 0; st--) if ((k >> st) & 1) {
		ll sum = 0;
		for (int i = st - 1; i >= 0; i--) {
			sum += max(cnt[i][0], cnt[i][1]) * (1ll << i);
		}
		for (int i = 39; i > st; i--) {
			sum += cnt[i][((k >> i) & 1) ^ 1] * (1ll << i);
		}
		sum += cnt[st][1] * (1ll << st);
		ans = max(ans, sum);
	}
	cout << ans << "\n";		
	return 0;
}