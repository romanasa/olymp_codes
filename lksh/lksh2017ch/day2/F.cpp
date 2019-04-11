#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

vector<char> A, B;
string s;

const int C = 5000;
ll dp[20][20][2];

vector<ll> go(int len1, int len2, int q) {
    if (len1 == 0) return q == 1 ? vector<ll>(0) : vector<ll>(1);
    vector<ll> Q;
    ll p = 1;
    for (int i = 0; i < len1 - 1; i++) p *= 10;

    for (int w = 0; w < 2; w++) {
        for (char a : A) {
            for (char b : B) {
                int val1 = a, val2 = b;
                if (len2 < len1) val1 = 0;
                if ((val1 + val2 + w) % 10 == s[len1 - 1] - '0' && (val1 + val2 + w) / 10 == q) {
                    auto now = go(len1 - 1, (len1 == len2 ? 0 : len2), w);
                    for (ll &x : now) x += p * a;

                    for (ll x : now) {
                        if (Q.size() >= C) break;
                        Q.push_back(x);
                    }
                }
                if (Q.size() >= C) break;
            }
            if (Q.size() >= C) break;
        }
        if (Q.size() >= C) break;
    }
    return Q;
}

vector<ll> calc(int msk1, int msk2) {
    A.clear(), B.clear();
    for (int i = 0; i < 10; i++) if ((msk1 >> i) & 1) A.push_back(i);
    for (int i = 0; i < 10; i++) if ((msk2 >> i) & 1) B.push_back(i);

    //err("A = {");for (int x : A) err(" %d,", x); err(" }\n");
    //err("B = {");for (int x : B) err(" %d,", x); err(" }\n");

    for (int i = 0; i < 20; i++) for (int j = 0; j < 20; j++) dp[i][j][0] = dp[i][j][1] = 0;
    dp[0][0][0] = 1;
    reverse(s.begin(), s.end());
    for (int len = 0; len < (int)s.size(); len++) {
        for (int t = 0; t <= max(len, 0); t++) {
            for (int q = 0; q < 2; q++) {
                if (dp[len][t][q] == 0) continue;


                if (t == 0) {
                    for (char a : A) {
                        {
                            int b = s[len] - '0' - a - q;
                            if (0 <= b && ((msk2 >> b) & 1)) dp[len + 1][t][0] += dp[len][t][q];
                        }
                        {
                            int b = s[len] - '0' + 10 - a - q;
                            if (0 <= b && ((msk2 >> b) & 1)) {
                                //if (len == 0) err("%d + %d + %d\n", (int)a, b, q);
                                dp[len + 1][t][1] += dp[len][t][q];
                            }
                        }

                        if (a != 0) {
                            {
                                int b = s[len] - '0' - a - q;
                                if (0 <= b && ((msk2 >> b) & 1)) dp[len + 1][len + 1][0] += dp[len][t][q];
                            }
                            {
                                int b = s[len] - '0' + 10 - a - q;
                                if (0 <= b && ((msk2 >> b) & 1)) dp[len + 1][len + 1][1] += dp[len][t][q];
                            }
                        }
                    }
                } else {
                    for (char b : B) {
                        int cur = b + q;
                        if (cur == s[len] - '0') dp[len + 1][t][0] += dp[len][t][q];
                        if (cur == s[len] - '0' + 10) dp[len + 1][t][1] += dp[len][t][q];
                    }
                }
            }
        }
    }


    /*for (int len = 0; len <= (int)s.size(); len++) {
        for (int t = 0; t <= max(len, 0); t++) {
            for (int q = 0; q < 2; q++) {
                if (dp[len][t][q] == 0) continue;
                err("dp[%d][%d][%d] = %I64d\n", len, t, q, dp[len][t][q]);
            }
        }
    }*/

    vector<ll> Q, W;
/*
    int len = (int)s.size();
    for (int len2 = 1; len2 <= len; len2++) {
        auto c = go(len, len2, 0);
        for (ll x : c) {
            if (Q.size() >= C) break;
            Q.push_back(x);
        }
    }

    if (s.back() == '1') {
        for (int len2 = 1; len2 < len; len2++) {
            auto c = go(len - 1, len2, 1);
            for (ll x : c) {
                if (W.size() >= C) break;
                W.push_back(x);
            }
        }
    }

    for (ll x : W) Q.push_back(x);
    sort(Q.begin(), Q.end());
    if (Q.size() > C) Q.resize(C);*/


    reverse(s.begin(), s.end());
    return Q;
}

int main() {
#ifdef WIN
    freopen("01.in", "r", stdin);
#endif
    cin >> s;


    calc(384, 68);
    return 0;


    vector<ll> A;
    int ans = 0;
    for (int msk = 0; msk < (1 << 10); msk++) {

        int ok = 1;
        for (char c : s) if ((msk >> (c - '0')) & 1) ok = 0;
        if (!ok) continue;

        for (int msk1 = (msk - 1) & msk; msk1; msk1 = (msk1 - 1) & msk) {
            int msk2 = msk ^ msk1;

            //err("calc (%d, %d), msk = %d\n", msk1, msk2, msk);
            auto c = calc(msk1, msk2);

            for (int len2 = 0; len2 <= (int)s.size(); len2++) {
                int tmp = dp[(int)s.size()][len2][0];
                ans += dp[(int)s.size()][len2][0];
                if (!tmp) continue;
                err("msk1 = %d, msk2 = %d\n", msk1, msk2);
                err("+= dp[%d][%d][0] = %d\n", (int)s.size(), len2, tmp);
            }

            //TODO 1!!!

            //err("ok\n");
        }
    }
    cout << ans << "\n";
    return 0;
}

