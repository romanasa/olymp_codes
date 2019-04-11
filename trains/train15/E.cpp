#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

int cnt[31];

int main() {	
	string s;
	cin >> s;
	
	for (char c : s) cnt[c - 'a'] = 1;
	

	int sz = 0;
	for (int i = 0; i < 26; i++) sz += (cnt[i] > 0);
	if (sz <= 1) return 0 * puts("0");
	
	auto prv = [](int x) { return x == 0 ? 25 : x - 1; };
	auto nxt = [](int x) { return x == 25 ? 0 : x + 1; };
	
	int ans = (int)1e9;
	
	for (int res = 0; res < 26; res++) {
		
		int posL = prv(res);
		while (cnt[posL] == 0) posL = prv(posL);
		
		
		int posR = nxt(res);
		while (cnt[posR] == 0) posR = nxt(posR);
		
		swap(posL, posR);
		
		ans = min(ans, res < posR ? posR - res : posR + 26 - res);
		ans = min(ans, posL < res ? res - posL : 26 - posL + res);
		
	}
	cout << ans << "\n";
	return 0;
}