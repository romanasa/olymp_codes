#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

int get(char c) {
	return ('0' <= c && c <= '9' ? c - '0' : c - 'A' + 10);
}

const int C = 256;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int n; cin >> n;
	
	vector<int> a(n);
	for (int i = 0; i < n; i++) {
		string s; cin >> s;
		a[i] = get(s[0]) * 16 + get(s[1]);
	}
	
	int pr = 0;
	vector<ll> dp1(n + 1, -1), dp2(n + 1, -1);
	dp1[0] = 0;
	
	ll ans = 0;
	for (int i = 0; i < n; i++) {
		for (int j = max(pr - C, 0); j <= min(pr + C, i) + 1; j++) {
			dp2[j] = -1;
		}
	
		for (int j = max(pr - C, 0); j <= min(pr + C, i); j++) {
			dp2[j] = max(dp2[j], dp1[j]);
			dp2[j + 1] = max(dp2[j + 1], dp1[j] + (j ^ a[i]));
		}
		
		for (int j = max(pr - C, 0); j <= min(pr + C, i) + 1; j++) {
			dp1[j] = dp2[j];
		}
		int pos = max_element(dp1.begin() + max(pr - C, 0), dp1.begin() + min(n, min(pr + C, i) + 2)) - dp1.begin();
		ans = max(ans, dp1[pos]);
		pr = pos;
	}
	
	cout << *max_element(dp1.begin(), dp1.end()) << "\n";
	
	
	
	return 0;
}