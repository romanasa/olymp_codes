#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)
 
using namespace std;
 
typedef unsigned long long ull;
 
vector<vector<ull> > T;
 
int dp[(1 << 26) + 1];
 
int main() {
    int n, m;
    scanf("%d %d", &n, &m);
     
    if (n <= 26) {
        vector<int> Q(m);
        for (int i = 0; i < m; i++) {
            int t;
            scanf("%d", &t);
            for (int j = 0; j < t; j++) {
                int x;
                scanf("%d", &x);
                x--;
                Q[i] ^= 1 << x;
            }   
            dp[Q[i]]++;
        }       
        for (int j = 0; j < n; j++) {
            for (int msk = 0; msk < (1 << n); msk++) if ((msk >> j) & 1) {
                dp[msk ^ (1 << j)] += dp[msk];
            }
        }
         
        long long ans = 0;
        for (int i = 0; i < m; i++) {
            int rev = 0;
            for (int j = 0; j < n; j++) if (((Q[i] >> j) & 1) == 0)
                rev ^= (1 << j);
            ans += dp[rev];
            if (Q[i] == (1 << n) - 1) ans--;
        }
        printf("%lld\n", ans / 2);
        return 0;
    }
     
    vector<int> sz(m);
     
    if (n <= 32) {
        vector<unsigned int> Q(m);
         
        long long ans = 0;
        int cnt = 0;
         
        for (int i = 0; i < m; i++) {
            int t;
            scanf("%d", &t);
             
            sz[i] = t;
            for (int j = 0; j < t; j++) {
                int x;
                scanf("%d", &x);
                x--;
                Q[i] ^= (unsigned int)1 << x;
            }
             
            if (sz[i] == n) {
                ++cnt;
                ans += m - cnt, sz[i] = 0, Q[i] = 0;
            }
        }
         
        vector<pair<int, int> > P(m);
        for (int i = 0; i < m; i++) P[i] = { sz[i], i };
         
        unsigned int msk1 = 0;
        for (int i = 0; i < n; i++) msk1 ^= (unsigned int)1 << i;
         
        sort(P.rbegin(), P.rend());
         
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < i; j++) {
                if (P[i].first + P[j].first < n) break;
                ans += (Q[P[i].second] | Q[P[j].second]) == msk1;
            }
        }   
        printf("%lld\n", ans);
        return 0;
    }
     
    if (n <= 64) {
        vector<ull> Q(m);
 
        for (int i = 0; i < m; i++) {
            int t;
            scanf("%d", &t);
            sz[i] = t;
            for (int j = 0; j < t; j++) {
                int x;
                scanf("%d", &x);
                x--;
                Q[i] ^= (ull)1 << x;
            }
        }
         
        vector<pair<int, int> > P(m);
        for (int i = 0; i < m; i++) P[i] = { sz[i], i };
         
        ull msk1 = 0;
        for (int i = 0; i < n; i++) msk1 ^= (ull)1 << i;
         
        sort(P.rbegin(), P.rend());
         
        int ans = 0;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < i; j++) {
                if (P[i].first + P[j].first < n) break;
                ans += (Q[P[i].second] | Q[P[j].second]) == msk1;
            }
        }   
        printf("%d\n", ans);
        return 0;
    }
     
    int len = (n + 63) / 64;
     
    T.resize(m);
     
    for (int i = 0; i < m; i++) {
        int t;
        scanf("%d", &t);
         
        T[i].resize(len);
        sz[i] = t;
         
        for (int j = 0; j < t; j++) {
            int x;
            scanf("%d", &x);
            x--;        
            T[i][x >> 6] ^= (ull)1 << (x & 63);
        }
    }
     
     
    ull msk1 = 0, msk2 = 0;
    for (int i = 0; i < 64; i++) msk1 ^= (ull)1 << i;
    for (int i = 0; i <= ((n - 1) & 63); i++) msk2 ^= (ull)1 << i;
     
    vector<pair<int, int> > P(m);
    for (int i = 0; i < m; i++) P[i] = { sz[i], i };
     
    sort(P.rbegin(), P.rend());
     
    int ans = 0;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < i; j++) {
         
            if (P[i].first + P[j].first < n) break;
            if ((T[P[i].second][len - 1] | T[P[j].second][len - 1]) ^ msk2) continue;
         
            int ok = 1;
            for (int t = 0; t + 1 < len; t++) {
                if ((T[P[i].second][t] | T[P[j].second][t]) ^ msk1) {
                    ok = 0;
                    break;
                }
            }
            ans += ok;
        }   
    }
    printf("%d\n", ans);
    return 0;
}