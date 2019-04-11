#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)
  
typedef long long ll;
  
using namespace std;
  
int iL, iR;
 
const int dd = (int)(1 << 17);
ll dp1[dd], dp2[dd];
ll T[dd];
 
ll C = 0;
      
inline void push(ll x) {
    x -= C;
    while (iL < iR && T[iR - 1] < x) iR--;
    T[iR++] = x;
}
  
inline void pop(ll x) {
    x -= C;
    if (iL < iR && T[iL] == x) iL++;
}
  
inline void add(ll x) {
    C += x;
}
 
inline ll get() {
    return (iL < iR ? T[iL] + C : -(ll)1e18);
}
  
 
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, s;
    cin >> n >> s;
      
    fill(dp1, dp1 + s + 1, -(ll)1e18);
    fill(dp2, dp2 + s + 1, -(ll)1e18);
    dp1[0] = 0;
      
    ll tmp;
    int sum = 0;
    
    for (int it = 0; it < n; it++) {
        int w, c, k;
        cin >> w >> c >> k;
        
        sum = min((ll)s, sum + 1ll * w * k);
        //sum = s;
        
        ll t1 = 1ll * w * (k + 1);
        ll t2 = 1ll * c * (k + 1);
        
        for (int i = 0; i <= min(w - 1, sum); i++) {
            iL = iR = 0;
            C = 0;
            for (int curw = i; curw <= sum; curw += w) {
                if (dp1[curw] >= 0) push(dp1[curw]);
                if (curw >= t1) pop(dp1[curw - t1] + t2);
                dp2[curw] = get();
                add(c);
            }
        }
        memcpy(dp1, dp2, sizeof(ll) * (sum + 1));
    }
    cout << *max_element(dp1, dp1 + s + 1) << "\n";
    err("time = %.3f\n", clock() * 1.0 / CLOCKS_PER_SEC);
    return 0;
}