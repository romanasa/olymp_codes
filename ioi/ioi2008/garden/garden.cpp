#include <bits/stdc++.h>
#define ll long long
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

int main() {
	int n, mod;
	string s;
	cin >> n >> mod >> s;
	
	int minb = 0, maxb = 0;
	int b = 0, ans = 1;

	vector<int> P(n + 1);
	P[0] = 1;
	for (int i = 0; i < n; i++)
		P[i + 1] = P[i] * 2 % mod;
		
	for (int i = 0; i < n; i++) {
		
		if (s[i] == 'L' || b + 1 > minb + 2) {
			
			b += (s[i] == 'L' ? 1 : -1);
		
			minb = min(minb, b);
			maxb = max(maxb, b);
			
			continue;
		}
		//cout << "count for " << string(s.begin(), s.begin() + i) + "L" << "\n";		
		int cur = n - i - 1;
		
		if (max(maxb, b + 1) - minb == 2) {
			if (minb == b) {
				ans += P[(cur + 1) / 2];
				//cout << "add1 " << P[(cur + 1) / 2] << "\n";
			} else {
				ans += P[cur / 2];
				//cout << "add2 " << P[(cur) / 2] << "\n";
			}
		} else {
			ans += P[(cur + 1) / 2] + P[cur / 2] - 1;
			//cout << "add3 " << P[(cur + 1) / 2] + P[cur / 2] - 1 << "\n";
		}
		ans %= mod;
		
		
		b += (s[i] == 'L' ? 1 : -1);
		
		minb = min(minb, b);
		maxb = max(maxb, b);
	}
	cout << ans;
	return 0;
}