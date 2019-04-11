#include <bits/stdc++.h>
#define err(...) //fprintf(stderr, __VA_ARGS__), fflush(stderr)
using namespace std;

typedef long long ll;

const int dd = (int)5000 + 1;
double dp1[dd][3], dp2[dd][3];
double p[3];

double get(int N, int K) {
    return K * 1.0 / (N * (N - K + 1));
}

int main() {
#ifdef WIN
    freopen("01.in", "r", stdin);
#else
    freopen("input.txt", "r", stdin);// freopen("output.txt", "w", stdout);
#endif
    int n, s;
    scanf("%d %d", &n, &s);

    int cnt = -1;
    for (int i = 0; i <= n; i++) {
        if (3 * i + 2 * (n - i) == s) cnt = i;
    }
    assert(cnt != -1);

    //dp1[1][0] = cnt * 1.0 / n;

    double pa = cnt * 1.0 / n;
    //p[0] = pa;
    //p[1] = 1 - pa;

    for (int i = 1; i < n; i++) {
        for (int a = 0; a <= min(i, cnt); a++) {
            int b = i - a;

            p[0] = min((cnt - a) * 1.0 / (n - i), 1.0);
            p[1] = 1 - p[0];

            dp2[a + 1][0] += (dp1[a][0] + 1) * p[0];
            dp2[a + 1][0] += (dp1[a][1]) * p[0];

            dp2[a][1] += (dp1[a][0]) * p[1];
            dp2[a][1] += (dp1[a][1] + 1) * p[1];
        }

        for (int a = 0; a <= n; a++) {
            err("dp[%d][%d] = (%.3f, %.3f)\n", i, a, dp1[a][0], dp1[a][1]);
            dp1[a][0] = dp2[a][0], dp1[a][1] = dp2[a][1];
            dp2[a][0] = dp2[a][1] = 0;
        }
    }

    for (int a = 0; a <= n; a++) {
        err("dp[%d][%d] = (%.3f, %.3f)\n", n, a, dp1[a][0], dp1[a][1]);
    }

    double pb = 1 - pa;
    printf("%.10f\n", n - (dp1[cnt][0] * pa + dp1[cnt][0] * (1 - pb)));
    return 0;
}
