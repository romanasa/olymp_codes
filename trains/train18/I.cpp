#include <bits/stdc++.h>

#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

#define x first
#define y second
#define mp make_pair
#define pub push_back
#define all(v) (v).begin(), (v).end()
//236695ZVSVG

using namespace std;

typedef long long ll;
typedef double db;

int n;

ll A, B, C, D;
ll d[35][35];
int dp[35][11][11][11][4];
int x[35], y[35];

int go(int h, int f, int t, int v, int q) {
    if (v == n - 1) return 0;
    if (dp[v][h][f][t][q] != -1) return dp[v][h][f][t][q];

    int dist = (int)1e9;
    if (h > 0) {
        if (q == 1) {
            ll cur = 2 * A;
            for (int j = 0; j < n; j++) if (d[j][v] <= cur * cur) {
                dist = min(dist, go(h - 1, f, t, j, 1)  + 1);
            }
        }
        if (q == 2) {
            ll cur = C + B + A;
            for (int j = 0; j < n; j++) if (d[j][v] <= cur * cur) {
                dist = min(dist, go(h - 1, f, t, j, 1)  + 1);
            }
        }
        if (q == 3) {
            ll cur = D + B + A;
            for (int j = 0; j < n; j++) if (d[j][v] <= cur * cur) {
                dist = min(dist, go(h - 1, f, t, j, 1)  + 1);
            }
        }
    }
    if (f > 0) {
        if (q == 1) {
            ll cur = A + B + C;
            for (int j = 0; j < n; j++) if (d[j][v] <= cur * cur) {
                dist = min(dist, go(h, f - 1, t, j, 2)  + 1);
            }
        }
        if (q == 2) {
            ll cur = 2 * C;
            for (int j = 0; j < n; j++) if (d[j][v] <= cur * cur) {
                dist = min(dist, go(h, f - 1, t, j, 2)  + 1);
            }
        }
        if (q == 3) {
            ll cur = C + D;
            for (int j = 0; j < n; j++) if (d[j][v] <= cur * cur) {
                dist = min(dist, go(h, f - 1, t, j, 2)  + 1);
            }
        }
    }
    if (t > 0) {
        if (q == 1) {
            ll cur = A + B + D;
            for (int j = 0; j < n; j++) if (d[j][v] <= cur * cur) {
                dist = min(dist, go(h, f, t - 1, j, 3) + 1);
            }
        }
        if (q == 2) {
            ll cur = C + D;
            for (int j = 0; j < n; j++) if (d[j][v] <= cur * cur) {
                dist = min(dist, go(h, f, t - 1, j, 3) + 1);
            }
        }
    }

    return dp[v][h][f][t][q] = dist;
}

int main() {
#ifdef WIN
    freopen("01", "r", stdin);
#else
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif // WIN
    for (int i = 0; i < 31; i++)
        for (int a = 0; a < 11; a++)
            for (int b = 0; b < 11; b++)
                for (int c = 0; c < 11; c++)
                    for (int d = 0; d < 4; d++)
                        dp[i][a][b][c][d] = -1;

    cin >> A >> B >> C >> D;
    int kh, kf, kt;
    cin >> kh >> kf >> kt;

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> x[i] >> y[i];
    }

    /*if (n == 1) {
        return 0 * puts("0");
    }*/

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            d[i][j] = 1ll * (x[i] - x[j]) * (x[i] - x[j]) + 1ll * (y[i] - y[j]) * (y[i] - y[j]);
        }
    }

    int t = (int)1e9;

    if (kh > 0) t = min(t, go(kh - 1, kf, kt, 0, 1) + 1);
    if (kf > 0) t = min(t, go(kh, kf - 1, kt, 0, 2) + 1);
    if (kt > 0) t = min(t, go(kh, kf, kt - 1, 0, 3) + 1);

    if (t == (int)1e9) cout << -1;
    else cout << t;
    return 0;
}

