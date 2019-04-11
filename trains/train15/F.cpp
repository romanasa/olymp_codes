#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

bool check(int n, int m, int cur) {
	int cnt = 0;
	int l = 1, r = cur;
	int pr = -(int)1e9;
	while (l <= r) {
		if (r + pr + 1 <= n) {
			cnt += r;
			pr = r;
			r--;
		} else if (l + pr + 1 <= n) {
			cnt += l;
			pr = l;
			l++;
		} else {
			cnt++;
			pr = -(int)1e9;
		}
	}
	return n >= cur && m >= cnt;
}

int get(int n, int m) {
	int cur = min(n, m);
	if (cur > 1300) cur = 1300;
	for (; cur > 0; cur-- ) {
		if (check(n, m, cur)) return cur;
	}
	return 0;
}

int main() {
	int s;
	cin >> s;
	
	int ans = 0;
	for (int i = 1; i * i <= s; i++) if (s % i == 0) {
		ans = max(ans, get(i, s / i));
		ans = max(ans, get(s / i, i));
	}
	cout << ans << "\n";
	return 0;
}