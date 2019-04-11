#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int n;
	cin >> n;

	int pG = -1, pR = -1, pB = -1;
	int gapR = 0, gapB = 0;
	ll ans = 0;
	
	for (int i = 0; i < n; i++) {
		int x;
		char c;
		cin >> x >> c;
		if (c == 'R') {
			if (pR != -1) ans += x - pR, gapR = max(gapR, x - pR);
			pR = x;
		}
		if (c == 'B') {
			if (pB != -1) ans += x - pB, gapB = max(gapB, x - pB);
			pB = x;
		}
		if (c == 'G') {
			if (pR != -1) ans += x - pR, gapR = max(gapR, x - pR);
			if (pB != -1) ans += x - pB, gapB = max(gapB, x - pB);
			if (pG != -1 && gapR + gapB > x - pG) {
				ans += x - pG;
				ans -= gapR + gapB;
			}
			gapR = gapB = 0;
			pR = pB = pG = x;
		}
	}
	cout << ans << "\n";
	return 0;
}