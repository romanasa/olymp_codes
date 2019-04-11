#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

const LL INF = 1LL << 62;

const bool debug = false;

int main() {
    int n, m, p;
    cin >> n >> m >> p;
    vector<LL> x(n);
    for (int i = 1; i < n; i++) {
        int d;
        cin >> d;
        x[i] = x[i - 1] + d;
    }
    for (int i = 0; i < n; i++) {
        if (debug) cerr << x[i] << " ";
    }
    if (debug) cerr << endl;
    vector<LL> a(m);
    for (int i = 0; i < m; i++) {
        int h, t;
        cin >> h >> t;
        h--;
        a[i] = t - x[h];
    }
    sort(a.begin(), a.end());
    for (int i = 0; i < m; i++) {
        if (debug) cerr << a[i] << " ";
    }
    if (debug) cerr << endl;
    vector<LL> s(m + 1);
    for (int i = 0; i < m; i++) {
        s[i + 1] = s[i] + a[i];
    }

    vector<vector<LL>> dp(p, vector<LL>(m + 1));
    for (int i = 1; i <= m; i++) {
        dp[0][i] = a[i - 1] * i - s[i];
    }

    for (int k = 1; k < p; k++) {
        vector<LL> K(m + 1);
        vector<LL> B(m + 1);
        
        K[0] = -0;
        B[0] = dp[k - 1][0] + s[0];
        dp[k][0] = 0;

        vector<int> good;
        good.push_back(0);
        vector<LL> pts;
        pts.push_back(-INF);


        for (int j = 1; j <= m; j++) {
            int L = 0;
            int R = good.size();
            LL x = a[j - 1];
/*            if (x < 0) {
                x = 0;
            }*/
            while (L < R - 1) {
                int M = (L + R) / 2;
                if (x > pts[M]) {
                    L = M;
                } else {
                    R = M;
                }
            }
            dp[k][j] = K[good[L]] * x + B[good[L]] + x * j - s[j];
            if (debug) cerr << k << " " << j << "   " << L << " " << good[L] << "   " << K[good[L]] << " " << B[good[L]] << " " << dp[k][j] << endl;
            if (j < m) {
                K[j] = -j;
                B[j] = dp[k - 1][j] + s[j];

                LL x;
                while (good.size() > 0) {
                    int lst = good[good.size() - 1];
                    x = (B[j] - B[lst]) / (K[lst] - K[j]);
                    if (B[j] < B[lst]) {
                        x--;
                    }
                    if (good.size() == 0 || x > pts[pts.size() - 1]) {
                        break;
                    }
                    good.pop_back();
                    pts.pop_back();
                }
                if (K[good[good.size() - 1]] != K[j]) {
                    good.push_back(j);
                    pts.push_back(x);
                }

                for (int i = 0; i < good.size(); i++) {
                    if (debug) cerr << K[good[i]] << " * x + " << B[good[i]] << "    " << good[i] << " " << pts[i] << endl;
                }
                if (debug) cerr << "---" << endl;
            }
        }
    }

    if (debug) {
        for (int i = 0; i < p; i++) {
            for (int j = 0; j <= m; j++) {
                cerr << dp[i][j] << " ";
            }
            cerr << endl;
        }
    }

    cout << dp[p - 1][m] << endl;

    return 0;
}
