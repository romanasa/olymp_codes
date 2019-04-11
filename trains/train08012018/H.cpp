#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

int a[51];
int dp[51][51][51][51];

inline void uax(int &a, int b) { if (a < b) a = b; }

int main() {
	int n;
	cin >> n;
	for (int i = 0; i < n; i++) cin >> a[i];
	
	int ans = 0;
	
	
    for (int len = 0; len < n; len++) {
		for (int L = 1; L <= 50; L++) {
			for (int R = L; R <= 50; R++) {
		
            	for (int i = 0; i + len < n; i++) {
            		int j = i + len;
            		
            		if (i == j) dp[i][j][L][R] = (L <= a[i] && a[i] <= R);
            		else {
                    	int cur = 0;
                    	
                    	uax(cur, dp[i + 1][j][L][R]);
                    	if (L <= a[i] && a[i] <= R) uax(cur, dp[i + 1][j][a[i]][R] + 1);
                    	
                    	uax(cur, dp[i][j - 1][L][R]);
                    	if (L <= a[j] && a[j] <= R) uax(cur, dp[i][j - 1][L][a[j]] + 1);
                    	
                    	uax(cur, dp[i + 1][j - 1][L][R]);
                    	if (L <= a[j] && a[j] <= R) uax(cur, dp[i + 1][j - 1][a[j]][R] + 1);
                    	if (L <= a[i] && a[i] <= R) uax(cur, dp[i + 1][j - 1][L][a[i]] + 1);
                    	if (L <= a[j] && a[j] <= a[i] && a[i] <= R) uax(cur, dp[i + 1][j - 1][a[j]][a[i]] + 2);
                    	
                    	dp[i][j][L][R] = cur;
                 	}
                    uax(ans, dp[i][j][L][R]);
            	}
            }
       	}
	}
	cout << ans << "\n";
	return 0;
}