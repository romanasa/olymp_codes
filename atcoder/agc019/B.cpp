#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

int cnt[31];

int main() {
	string s;
	cin >> s;
	
	for (char c : s) cnt[c - 'a']++;
	
	ll ans = 1;
	for (int i = 0; i < 31; i++) {
		int cur = 0;
		for (int j = i + 1; j < 31; j++) cur += cnt[j];
		ans += 1ll * cnt[i] * cur;
	}
	cout << ans << "\n";
	return 0;
}