#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

int cnt[31];

int main() {
	int n, k;
	cin >> n >> k;
	
	string s;
	cin >> s;
	
	int j = 0;
	int ans = -1, pos = -1;
	for (int i = 0; i < n; i++) {
		while (j < n && cnt[s[j] - 'a'] < k) {
			cnt[s[j] - 'a']++;
			j++;
		}
		if (j - i > ans) {
			ans = j - i;
			pos = i;
		}
		cnt[s[i] - 'a']--;
	}
	cout << ans << " " << pos + 1 << "\n";
	
	return 0;
}