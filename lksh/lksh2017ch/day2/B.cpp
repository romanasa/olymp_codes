#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

const int dd = (int)2e3 + 7;
int cost[dd], go[dd][5], row[dd], sum[dd];

double p[dd][5];
double dp1[dd], dp2[dd];

int main() {
#ifdef WIN
    freopen("01.in", "r", stdin);
#endif
    int h;
    scanf("%d", &h);

    int n = h * (h + 1) / 2;

    for (int i = 0; i < n; i++) scanf("%d", &cost[i]);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < 5; j++) cin >> p[i][j];

    int cur = 0;
    for (int r = 1; r <= h; r++) {
        for (int j = cur; j < cur + r; j++) row[j] = r;
        cur += r;
    }

    for (int r = 1; r <= h; r++) sum[r] = sum[r - 1] + r;

    for (int i = 0; i < n; i++) {
        fill(go[i], go[i] + 4, -1);

        int okL = 1;
        for (int r = 0; r <= h; r++) if (sum[r] == i) okL = 0;
        if (okL) go[i][0] = i - row[i];

        int okR = 1;
        for (int r = 0; r <= h; r++) if (sum[r] == i + 1) okR = 0;
        if (okR) go[i][1] = i - row[i] + 1;

        if (row[i] < h) {
            go[i][2] = i + row[i];
            go[i][3] = i + row[i] + 1;
        }
    }

    double ans = 0;
    dp1[0] = 1;

    while (clock() < 1.9 * CLOCKS_PER_SEC) {
        for (int v = 0; v < n; v++) {
            for (int i = 0; i < 4; i++) if (go[v][i] != -1) {
                dp2[go[v][i]] += dp1[v] * p[v][i];
            }
            ans += dp1[v] * p[v][4] * cost[v];
        }
        for (int v = 0; v < n; v++) dp1[v] = dp2[v], dp2[v] = 0;
        //err("len = %d, ans = %.3f\n", len, ans);
    }

    printf("%.10f\n", ans);
    return 0;
}


