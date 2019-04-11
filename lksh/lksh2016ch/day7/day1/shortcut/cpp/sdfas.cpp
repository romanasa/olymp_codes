#include <bits/stdc++.h>
#define ll long long
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stdout)
 
using namespace std;
 
const ll linf = (ll)1e18 + 7;
 
const int dd = (int)1e6 + 7;
ll P[dd], D[dd], C;
 
inline ll dist(int i, int j) {
    return abs(P[i] - P[j]);
}
 
inline ll dist(int a, int b, int i, int j) {
    if (a == b)
        return 0;
    ll q = min(dist(a, b), dist(a, i) + C + dist(j, b));
    q = min(q, dist(a, j) + C + dist(i, b));
    return q + D[a] + D[b];
}
 
ll find_shortcut(int n, vector <int> l, vector <int> d, int c) {
    C = c;
    copy(d.begin(), d.end(), D);
     
    for (int i = 0; i < n - 1; i++) {
        P[i + 1] = P[i] + l[i];
    }
     
    ll ans = linf;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {            
         
            ll cur = 0;
             
            int indS = (j + 1 < n ? j + 1 : j);
            int indP = (i > 0 ? i - 1 : i);
             
            for (int t = j + 1; t < n; t++) {
                if (dist(j, t) + d[t] > dist(j, indS) + d[indS])
                    indS = t;
            }
             
            for (int t = i - 1; t >= 0; t--) {
                if (dist(t, i) + d[t] > dist(indP, i) + d[indP])
                    indP = t;
            }
 
            ll val = -P[0] + d[0];
             
            for (int t = 1; t <= i; t++) {
                cur = max(cur, val + P[t] + d[t]);
                val = max(val, -P[t] + d[t]);
            }
             
            val = P[n - 1] + d[n - 1];
            for (int t = n - 2; t >= j; t--) {
                cur = max(cur, val - P[t] + d[t]);
                val = max(val, P[t] + d[t]);
            }
             
            cur = max(cur, dist(indP, indS, i, j));
             
            for (int t = i; t <= j; t++) {
                cur = max(cur, dist(indP, t, i, j));
                cur = max(cur, dist(t, indS, i, j));
            }           
             
            for (int t = i; t <= j; t++) {
                for (int k = i; k < t; k++)
                	cur = max(cur, dist(k, t, i, j));
            }
             
            //err("(%d--->%d) : %lld\n", i, j, cur);
            ans = min(ans, cur);
        }
    }
    return ans;
}