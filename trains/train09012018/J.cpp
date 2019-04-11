#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

#define TASK "tickets"

int C, D, P;
ll dp[15][15][2];

ll calc(string cur) {
	int ind = (int)cur.size();
	
	for (int i = 0; i < 15; i++)
		for (int j = 0; j < 15; j++) dp[i][j][0] = dp[i][j][1] = 0;
	
	for (char &c : cur) c -= '0';
		
	dp[0][0][0] = 1;
		
	for (int i = 0; i < ind; i++) {
		for (int j = 0; j <= i; j++) {
			for (int t = 0; t < 2; t++) if (dp[i][j][t]) {
				for (int c = 0; c <= (t ? 9 : cur[i]); c++) {
					dp[i + 1][j + (c == D)][t | (c < cur[i])] += dp[i][j][t];
				}
			}
		}
	}
	
	ll ans = 0;
	for (int cnt = 0; cnt <= ind; cnt++) {
		//err("cnt = %d, val = %I64d + %I64d\n", cnt, dp[ind][cnt][0], dp[ind][cnt][1]);
		long double cost = C;
		for (int j = 0; j < cnt; j++) cost *= (100 - P) / 100.0;
		ans += (ll)cost * (dp[ind][cnt][0] + dp[ind][cnt][1]);
	}
	//err("__\n");
	return ans;
}

int main() {
#ifndef HOME
	freopen(TASK".in", "r", stdin), freopen(TASK".out", "w", stdout);
#endif
	int n;
	cin >> n;
	cin >> C >> D >> P;
	
	while (n--) {
		string l, r;
		cin >> l >> r;
		
		ll cur = calc(r) - calc(l);

		//err("L = %I64d\n", calc(l));
		//err("R = %I64d\n", calc(r));
		
		long double cost = C;
		int cnt = 0;
		for (char c : l) if (c - '0' == D) cnt++;
		for (int j = 0; j < cnt; j++) cost *= (100 - P) / 100.0;
		cur += (ll)cost;
		
		cout << cur << "\n";
	}
	
	return 0;
}