#include <bits/stdc++.h>
#define ll long long
 
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stdout)
 
using namespace std;
 
const int dd = 17;
 
ll dp[1 << dd][dd];
 
const ll linf = (ll)1e18 + 7;
 
void upd(ll &a, ll b) {
    if (a > b)
        a = b;
}
 
ll plan_roller_coaster(vector<int> s, vector<int> t) {
    int n = (int)s.size();
 
    for (int i = 0; i < (1 << n); i++)
        fill(dp[i], dp[i] + dd, linf);
 
    for (int i = 0; i < n; i++) 
        dp[1 << i][i] = 0;
         
    for (int msk = 0; msk < (1 << n); msk++) {
        for (int i = 0; i < n; i++) if (msk & (1 << i))
            for (int j = 0; j < n; j++) if (!(msk & (1 << j))) {
                upd(dp[msk | (1 << j)][j], dp[msk][i] + max(0, t[i] - s[j]));
            }
    }
    return *min_element(dp[(1 << n) - 1], dp[(1 << n) - 1] + n);
}