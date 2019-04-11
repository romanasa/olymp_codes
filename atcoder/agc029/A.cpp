#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

typedef long long ll;

using namespace std;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	string s; cin >> s;
	
	int cnt = 0;
	ll ans = 0;
	
	for (int i = (int)s.size() - 1; i >= 0; i--) {
		if (s[i] == 'B') ans += cnt;
		else cnt++;
	}
	cout << ans << "\n";
	return 0;
}
