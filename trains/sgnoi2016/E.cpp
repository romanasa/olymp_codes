#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

int cur[31];
ll dp[18][2][2];

bool good(ll x) {
	int ind = 0;
	
	while (x) cur[ind++] = x % 10, x /= 10;
	reverse(cur, cur + ind);
	
	int ok = 1;
  	for (int i = 0; i < ind; i++) {
  		if (cur[i] == 4) { ok = 0; break; }
  		if (i + 1 < ind && cur[i] == 1 && cur[i + 1] == 3) { ok = 0; break; }
   	}
	return ok;
}

int cnt1[10]; 
int cnt2[10]; 

ll calc(ll x) {
	ll old = x;
	int ind = 0;
	
	while (x) cur[ind++] = x % 10, x /= 10;
	reverse(cur, cur + ind);
	
	for (int i = 0; i < 18; i++) {
		for (int a = 0; a < 2; a++) for (int b = 0; b < 2; b++) dp[i][a][b] = 0;
	}
	
	dp[0][0][0] = 1;
	for (int i = 0; i < ind; i++) {
		/*for (int t = 0; t < 2; t++) {
   			for (int was1 = 0; was1 < 2; was1++) if (dp[i][t][was1]) {
   				for (int c = 0; c <= (t ? 9 : cur[i]); c++) if (c != 4 && (!was1 || c != 3)) {
   					dp[i + 1][t | (c < cur[i])][c == 1] += dp[i][t][was1];
   				}
   			}
		}*/

		dp[i + 1][1][1] += dp[i][1][0];
		dp[i + 1][1][0] += dp[i][1][0] * 8;
		
		dp[i + 1][1][1] += dp[i][1][1];
		dp[i + 1][1][0] += dp[i][1][1] * 7;
		
		
		if (1 <= cur[i]) dp[i + 1][1 < cur[i]][1] += dp[i][0][0]; // c = 1
		if (1 <= cur[i]) dp[i + 1][1 < cur[i]][1] += dp[i][0][1]; // c = 1
		
		int ok = 1;
		if (cur[i] == 4 || cur[i] == 1) ok = 0;
		
		dp[i + 1][1][0] += dp[i][0][0] * cnt1[cur[i]];
		dp[i + 1][0][0] += dp[i][0][0] * ok;
		
		if (cur[i] == 3) ok = 0;
		
		dp[i + 1][1][0] += dp[i][0][1] * cnt2[cur[i]];
		dp[i + 1][0][0] += dp[i][0][1] * ok;
	}
	/*
		(i, 1, 0) , c = 1  ---> (i, 1, 1)
		(i, 1, 0) , c = 0, 2, 3, 5, 6, 7, 8, 9   ---> (i, 1, 0)

	 	(i, 1, 1) , c = 1  ---> (i, 1, 1)
	 	(i, 1, 1) , c = 0, 2, 5, 6, 7, 8, 9 ---> (i, 1, 0)
	 	
	 	
	 	(i, 0, 0) , c = 1 ---> (i, (c < cur[i]), 1)
	 	(i, 0, 0) , c = 0, 2, 3, 5, 6, 7, 8, 9 ---> (i, c < cur[i], 0)
	 	
	 	(i, 0, 1) , c = 1 ---> (i, (c < cur[i]), 1)
	 	(i, 0, 1) , c = 0, 2, 5, 6, 7, 8, 9 ---> (i, c < cur[i], 0)
	*/
	
	ll sum = dp[ind][0][0] +
			 dp[ind][0][1] +
			 dp[ind][1][0] +
			 dp[ind][1][1];
			 
	return old - sum + 1;
}

// 0 2 3 5 6 7 8 9
// 0 2 5 6 7 8 9  

int main() {
	cnt1[0] = 0; cnt1[1] = 1; cnt1[2] = 1; cnt1[3] = 2; cnt1[4] = 3; cnt1[5] = 3; cnt1[6] = 4; cnt1[7] = 5; cnt1[8] = 6; cnt1[9] = 7;
	cnt2[0] = 0; cnt2[1] = 1; cnt2[2] = 1; cnt2[3] = 2; cnt2[4] = 2; cnt2[5] = 2; cnt2[6] = 3; cnt2[7] = 4; cnt2[8] = 5; cnt2[9] = 6;
	
	int n;
	cin >> n;
	
	for (int i = 0; i < n; i++) {
		int t;
		ll x;
		cin >> t >> x;
		if (t == 1) {	
			if (!good(x)) cout << "-1\n";
			else cout << x - calc(x) << "\n";
		} else {
			ll l = x - 1, r = (ll)1e18;
			while (r - l > 1) {
				ll m = (l + r) / 2;
				if (m - calc(m) < x) l = m;
				else r = m;
			}
			cout << r << "\n";
		}
	}
	
	return 0;
}