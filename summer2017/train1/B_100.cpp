#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)
  
using namespace std;
  
const int maxN = 115;
const int maxC = 215;
 
int T[2][21][maxN][maxN][maxC];
  
const int mod = (int)1e9 + 7;
  
void add(int &a, int b) {
    a += b;
    if (a >= mod) a -= mod;
}
  
const int maxT = 1000;
  
int C[maxT + 5][maxT + 5];
  
void updL(int a, int b, int c, int d, int e, int val) {
    //err("oL");
    for (int i = b + 2; i < maxN; i += (i&-i)) add(T[a][e][i][c][d], val);
    //err("k\n");
}
 
void updR(int a, int b, int c, int d, int e, int val) { 
    //err("oR, i = %d", c + 2);
    for (int i = c + 2; i < maxN; i += (i&-i)) add(T[a][e][b][i][d], val);
    //err("k\n");
}
 
int getL(int a, int b, int c, int d, int e) {
    int res = 0;
    for (int i = b + 2; i; i -= (i&-i)) add(res, T[a][e][i][c][d]);
    return res;
}
 
int getR(int a, int b, int c, int d, int e) {
    int res = 0;
    for (int i = c + 2; i; i -= (i&-i)) add(res, T[a][e][b][i][d]);
    return res;
}
 
int getL(int a, int b1, int b2, int c, int d, int e) {  
    int cur = getL(a, b2 - 1, c, d, e) - getL(a, b1 - 1, c, d, e);
    return cur < 0 ? cur + mod : cur;
}
 
int getR(int a, int b, int c1, int c2, int d, int e) {
    int cur = getR(a, b, c2 - 1, d, e) - getR(a, b, c1 - 1, d, e);
    return cur < 0 ? cur + mod : cur;
}
 
int main() {
    for (int i = 0; i < maxT + 5; i++) C[i][0] = 1;
    for (int i = 1; i < maxT + 5; i++) C[0][i] = 0;
  
    for (int i = 1; i < maxT + 5; i++) {
        for (int k = 1; k <= i; k++) {
            add(C[i][k], C[i - 1][k - 1]);
            add(C[i][k], C[i - 1][k]);
        }
    }
  
  
    int T, n, K;
    cin >> T >> n >> K;
  
    int ans = 0;
  
    updR(1, 0, 0, 0, 0, 1);
  
    for (int L = 0; L <= n + 1; L++) {
        for (int R = 0; R <= n + 1; R++) {
            for (int t = L + R; t <= T; t++) {
                for (int k = 0; k <= min(K, 20); k++) {
 
                    int cur0 = 0;
                    int cur1 = 0;
                    
                    if (k - (R < n + 1) >= 0) {
                        int nrl = 0, nrr = R + (R == n + 1);
                        int cur = getR(1, L, nrl, nrr, t - L - R, k - (R < n + 1));
                        add(cur0, cur);
                    }
  
                    if (k - (L < n + 1) >= 0) {
                        int nll = 0, nlr = L + (L == n + 1);
                        int cur = getL(0, nll, nlr, R, t - L - R, k - (L < n + 1));
                        add(cur1, cur);
                    }
                     
                    updL(0, L, R, t, k, cur0);
                    updR(1, L, R, t, k, cur1);
                     
                    if (t + R == T) {
                        int cur = cur0;
                        int q = K - k;
                        int w = max(n - L, 0) + max(n - R, 0);
                        add(ans, 1ll * cur * C[w][q] % mod);
                    }
  
                    if (t + L == T) {
                        int cur = cur1;
                        
                        if (L == 0 && R == 0 && t == 0 && k == 0) cur = 1;
                        
                        int q = K - k;
                        int w = max(n - L, 0) + max(n - R, 0);
                        add(ans, 1ll * cur * C[w][q] % mod);
                    }
                }
            }
        }
    }
    cout << ans << "\n";
    return 0;
}