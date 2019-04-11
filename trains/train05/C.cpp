#include <bits/stdc++.h>
#define ll long long
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)
using namespace std;
 
int n, k, d;
 
vector<vector<int> > E;
 
const int maxN = 107;
const int maxK = 107;
 
const int mod = (int)1e4 + 7;
 
short dp[maxN][maxN][maxK][2];
 
short cnt1[maxN][maxK][2];
short cnt2[maxN][maxK][2];
int sz[maxN];
 
void add(short &a, short b) {
    a += b;
    if (a >= mod) a -= mod;
}
 
void calc(int v, int pr, int L) {
	sz[v] = 1;
    for (int to : E[v]) if (to != pr) {
        calc(to, v, L);
        sz[v] += sz[to];
    }
         
    for (int cntV = 0; cntV <= min(sz[v], L + d); cntV++)
        for (int cntC = 0; cntC <= k; cntC++) 
            for (int was = 0; was < 2; was++)
                cnt1[cntV][cntC][was] = cnt2[cntV][cntC][was] = 0;
                 
    cnt1[1][0][0] = 1;
         
    for (int i = 0; i < (int)E[v].size(); i++) {
        if (E[v][i] == pr) continue;
        for (int cntV = 0; cntV <= min(sz[v], L + d); cntV++) {
            for (int cntC = 0; cntC <= k; cntC++) {
                for (int was = 0; was < 2; was++) {
                    if (cnt1[cntV][cntC][was] == 0) continue;
                    for (int t = 0; cntV + t <= min(sz[v], L + d); t++) {
                        for (int q = 0; q + cntC <= k; q++) {
                            for (int w = 0; w < 2; w++) {
                                add(cnt2[cntV + t][cntC + q][was | w], (int)cnt1[cntV][cntC][was] * dp[E[v][i]][t][q][w] % mod);
                            }
                        }
                    }
                }
            }
        }
         
        for (int cntV = 0; cntV <= min(sz[v], L + d); cntV++) {
            for (int cntC = 0; cntC <= k; cntC++) {
                for (int was = 0; was < 2; was++) {
                    cnt1[cntV][cntC][was] = cnt2[cntV][cntC][was];
                    cnt2[cntV][cntC][was] = 0;
                }
            }
        }
    }
     
    for (int cntV = 0; cntV <= min(sz[v], L + d); cntV++) {
        for (int cntC = 0; cntC <= k; cntC++) {
            for (int was = 0; was < 2; was++) {
                dp[v][cntV][cntC][was] = cnt1[cntV][cntC][was];
            }
        }
    }
     
    for (int cntC = 1; cntC <= k; cntC++) {
        dp[v][0][cntC][0] = dp[v][0][cntC][1] = 0;
        for (int was = 0; was < 2; was++) {
            for (int cntV = L; cntV <= min(L + d, sz[v]); cntV++) {
                add(dp[v][0][cntC][was | (cntV == L)], dp[v][cntV][cntC - 1][was]);
            }
        }
    }
    /*
    err("v = %d\n", v);
    for (int cntV = 0; cntV <= n; cntV++) {
        for (int cntC = 0; cntC <= k; cntC++) {
            for (int was = 0; was < 2; was++) {
                err("dp[cntV = %d][cntC = %d][was = %d] = %d\n", cntV, cntC, was, dp[v][cntV][cntC][was]);
            }
        }
    }
    */
}
 
int main() {
    scanf("%d %d %d", &n, &k, &d);
     
    E.resize(n);
     
    for (int i = 0; i + 1 < n; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        E[a - 1].push_back(b - 1);
        E[b - 1].push_back(a - 1);
    }
     
    int ans = 0;
    for (int mn = 1; mn <= n; mn++) {
        calc(0, -1, mn);
        ans += dp[0][0][k][1];
        ans %= mod;
    }   
    printf("%d\n", ans);
    return 0;
}   