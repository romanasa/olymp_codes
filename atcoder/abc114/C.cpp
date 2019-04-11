#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

int ans = 0;
int n;

void go(int len, ll cur, int msk) {
	if (len == 10) return;
	
	if (msk == 7 && cur <= n) {
		ans++;
	}
	go(len + 1, cur * 10 + 3, msk | 1);
	go(len + 1, cur * 10 + 5, msk | 2);
	go(len + 1, cur * 10 + 7, msk | 4);
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> n;
	go(0, 0, 0);
	cout << ans << "\n";
	return 0;
}