#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

typedef long long ll;

using namespace std;

ll dp[13][307][13][13];

bool eqi(int a, int b) {
    if (a == 11) return true;
    return a == b;
}
bool eqi2(int a, int b) {
    if (a == -1) return true;
    return a == b;
}

bool eq(char a, char b) {
    if (a == '?') return true;
    return a == b;
}

bool dig(char a) {
    if (a == '?') return true;
    return '0' <= a && a <= '9';
}

int solve() {
    int n; cin >> n;
    string s; cin >> s;

    vector<int> S(n);
    for (int i = 0; i < n; i++) cin >> S[i];

    if (*max_element(S.begin(), S.end()) > 300) {
        cout << "0\n";
        return 0;
    }

    for (int i = 0; i < 13; i++) {
        for (int sc = 0; sc < 307; sc++) {
            for (int a = 0; a < 13; a++) {
                for (int b = 0; b < 13; b++) {
                    dp[i][sc][a][b] = 0;
                }
            }
        }
    }

    dp[0][0][11][11] = 1;
    for (int i = 0; i + 1 < n; i++) {
        for (int sc = 0; sc <= 300; sc++) {
            for (int c1 = 0; c1 <= 11; c1++) {
                for (int c2 = 0; c2 <= 11; c2++) if (dp[i][sc][c1][c2]) {

                    ll cnt = dp[i][sc][c1][c2];

                    //strike
                    if  (eqi(c1, 10) && eq(s[2 * i], 'x') && eq(s[2 * i + 1], '-')) {
                        for (int A = 0; A <= 10; A++) if (eqi(c2, A)) {
                            for (int B = 0; B <= 10; B++) {
                                int cur = sc + 10 + A + B;
                                if (eqi2(S[i], cur)) dp[i + 1][cur][A][B] += cnt;
                            }
                        }
                    }
                    //spare
                    if (c1 != 10 && c2 != 0 && (c1 == 11 || c2 == 11 || c1 + c2 == 10) && dig(s[2 * i]) && eq(s[2 * i + 1], '/')) {
                        for (int x = 0; x < 10; x++) if (eqi(c1, x) && eq(s[2 * i], '0' + x)) {
                            for (int A = 0; A <= 10; A++) {
                                int cur = sc + 10 + A;
                                if (eqi2(S[i], cur)) dp[i + 1][cur][A][11] += cnt;
                            }
                        }
                    }
                    //nothing
                    if (c1 != 10 && c2 != 10 && (c1 == 11 || c2 == 11 || c1 + c2 < 10) && dig(s[2 * i]) && dig(s[2 * i + 1])) {
                        for (int x = 0; x < 10; x++) if (eq(s[2 * i], '0' + x) && eqi(c1, x)) {
                            for (int y = 0; x + y < 10; y++) if (eq(s[2 * i + 1], '0' + y) && eqi(c2, y)) {
                                int cur = sc + x + y;
                                if (eqi2(S[i], cur)) dp[i + 1][cur][11][11] += cnt;
                            }
                        }
                    }
                }
            }
        }
    }

    ll ans = 0;
    int i = n - 1;
    for (int sc = 0; sc <= 300; sc++) {
        for (int c1 = 0; c1 <= 11; c1++) {
            for (int c2 = 0; c2 <= 11; c2++) if (dp[i][sc][c1][c2]) {

                ll cnt = dp[i][sc][c1][c2];
                //err("dp[%d][%d][%d][%d] = %d\n", i, sc, c1, c2, cnt);


                for (int A = 0; A <= 10; A++) if (eqi(c1, A)) {

                    if (A < 10 && !eq(s[2 * i], '0' + A)) continue;;
                    if (A == 10 && !eq(s[2 * i], 'x')) continue;

                    for (int B = 0; B <= 10 - (A == 10 ? 0 : A); B++) if (eqi(c2, B)) {

                        if (A == 10) {
                            if (B < 10 && !eq(s[2 * i + 1], '0' + B)) continue;
                            if (B == 10 && !eq(s[2 * i + 1], 'x')) continue;
                        } else if (A + B == 10) {
                            if (!eq(s[2 * i + 1], '/')) continue;
                        } else {
                            if (!eq(s[2 * i + 1], '0' + B)) continue;
                        }

                        if (A == 10 || A + B == 10) {
                            for (int C = 0; C <= 10; C++) {

                                if (A == 10 && B < 10) {
                                    if (B + C == 10 && !eq(s[2 * i + 2], '/')) continue;
                                    if (B + C < 10 && !eq(s[2 * i + 2], '0' + C)) continue;
                                    if (B + C > 10) continue;
                                } else {
                                    if (C < 10 && !eq(s[2 * i + 2], '0' + C)) continue;
                                    if (C == 10 && !eq(s[2 * i + 2], 'x')) continue;
                                }


                                int cur = sc + A + B + C;
                                if (eqi2(S[i], cur)) ans += cnt;
                            }
                        } else {
                            int cur = sc + A + B;
                            if (eq(s[2 * i + 2], '-') && eqi2(S[i], cur)) ans += cnt;
                        }
                    }
                }

            }
        }
    }
    cout << ans << "\n";
    return 0;
}

int main() {
#ifdef WIN
    freopen("01", "r", stdin);
#endif
    int q;
    cin >> q;
    while (q--) solve();

    return 0;
}
