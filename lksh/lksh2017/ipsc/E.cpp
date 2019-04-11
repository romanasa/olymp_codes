#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

int cnt = 0;

void checkR(int pos, vector<int> &cur) {
	if (cur[pos] > cur[pos + 1] + 1) {
		cur[pos + 1]++, cnt++;
		checkR(pos + 1, cur);
	}
	if (cur[pos] < cur[pos + 1] - 1) {
		cur[pos + 1]--, cnt++;
		checkR(pos + 1, cur);
	}
}

void checkL(int pos, vector<int> &cur) {
	if (cur[pos] > cur[pos - 1] + 1) {
		cur[pos - 1]++, cnt++;
		checkL(pos - 1, cur);
	}
	if (cur[pos] < cur[pos - 1] - 1) {
		cur[pos - 1]--, cnt++;
		checkL(pos - 1, cur);
	}
}

const int mod = (int)1e9 + 9;

int main() {
	int t;
	cin >> t;
	while (t--) {
		vector<int> cur(4007);
		int n;
		cin >> n;
		
		int ans = 0;
		
		for (int i = 0; i < n; i++) {
			int a, b;
			cin >> a >> b;
			
			int pos = a + 2000;	
			cnt = 1;
			
			cur[pos] += b;
			
			checkL(pos, cur);
			checkR(pos, cur);
			
			ans += 1ll * cnt * (i + 1) % mod;
			if (ans >= mod) ans -= mod;
		}			
		
		cout << ans << "\n";
	}
	return 0;
}