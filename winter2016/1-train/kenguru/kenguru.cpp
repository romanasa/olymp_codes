#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__)

using namespace std;

typedef long long ll;

const ll mod = (int)1e9 + 7;

ll dp[2007][2007][3];

void add(ll &a, ll b) {
    a += b;
    a %= mod;
}

int main() {
    int n, S, T;
    scanf("%d %d %d", &n, &S, &T);
    S--, T--;

    dp[0][0][0] = 1;

    for (int i = 0; i < n; i++) {
        for (int q = 0; q <= i; q++) {
            for (int c = 0; c <= 2; c++) {
                if (q == 0 && c == 0 && i > 0) dp[i][q][c] = 0;

                if (i != S && i != T) {
                    if (q > 1) {
                        ll cur = 1ll * q * (q - 1) * dp[i][q][c] % mod;
                        add(dp[i + 1][q - 1][c], cur);
                    }
                    if (q > 0 && c > 0) {
                        ll cur = 1ll * q * c * dp[i][q][c] % mod;
                        add(dp[i + 1][q - 1][c], cur);
                    }
                    if (c > 1) {
                        ll cur = 1ll * dp[i][q][c] % mod;
                        add(dp[i + 1][q][c - 2], cur);
                    }
                    add(dp[i + 1][q + 1][c], dp[i][q][c]);
                } else {
                    if (q > 0) add(dp[i + 1][q - 1][c + 1], dp[i][q][c] * q % mod);
                    if (c > 0) add(dp[i + 1][q][c - 1], dp[i][q][c] * c % mod);
                    add(dp[i + 1][q][c + 1], dp[i][q][c]);
                }
            }
        }
    }
    printf("%lld\n", dp[n][0][0]);
    return 0;
}
