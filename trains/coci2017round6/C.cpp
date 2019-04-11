#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

const int mod = (int)1e9 + 7;

void add(int &a, int b) {
	a += b;
	if (a >= mod) a -= mod;
}

int dp[2007][26][26];
int S[2007][26];

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	string s;
	cin >> s;
	
	int n = (int)s.size();
	
	S[0][0] = 1;
	
	for (int i = 0; i < n; i++) {
		char c = s[i];
		for (int len = n - 1; len >= 0; len--) {
			for (int y = 0; y < 26; y++) {
				add(dp[len + 1][y][c - 'a'], S[len][y]);
				add(S[len + 1][c - 'a'], S[len][y]);
			}
		}
	}
	
	int q;
	cin >> q;
	while (q--) {
		int d;
		string s;
		cin >> d >> s;
		cout << dp[d][s[0] - 'a'][s[1] - 'a'] << "\n";
	}
	return 0;
}