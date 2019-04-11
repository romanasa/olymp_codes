#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

ll len[51];
ll cnt[51];

ll go(int n, ll k) {
	ll cur = 0;
	if (n == 0) return 1;
	
	if (k <= 1) return 0;
	k -= 1;
	
	if (k <= len[n - 1]) return go(n - 1, k) + cur;
	k -= len[n - 1], cur += cnt[n - 1];
	
	if (k <= 1) return 1 + cur;
	k -= 1, cur++;
	
	if (k <= len[n - 1]) return go(n - 1, k) + cur;
	k -= len[n - 1], cur += cnt[n - 1];
	
	return cur;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int n; ll x;
	cin >> n >> x;
	
	len[0] = 1;
	for (int i = 1; i <= n; i++) len[i] = 2 * len[i - 1] + 3;
	
	cnt[0] = 1;
	for (int i = 1; i <= n; i++) cnt[i] = 2 * cnt[i - 1] + 1;
		
	cout << go(n, x) << "\n";
	return 0;
}