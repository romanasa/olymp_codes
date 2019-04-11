#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

int A[654][654];
int G[17][17];
int h, w, k, s;

int dp[(1 << 16) + 7][17];
int p[(1 << 16) + 7][17];

int sum(int x, int y) {
    int sum = 0;
    for (int i = x - 4; i <= x; i++) {
        for (int j = y - 4; j <= y; j++) {
            sum += A[i][j];
        }
    }
    return sum;
}

int check(int i, int j) {
    int res = 0;

    int i1 = i * s + s - 1;
    int i2 = j * s;

    for (int t = 5; t < w; t++) {
        res += abs(sum(i1, t) - sum(i2 + 4, t));
    }
    return res;
}

int main() {
#ifdef WIN
    freopen("input.txt", "r", stdin);
#endif
    int q;
    scanf("%d", &q);
    while (q--) {
        scanf("%d %d %d", &h, &w, &k);

        s = h / k;

        for (int i = 0; i < h; i++) {
            for (int j = 0; j < w; j++) {
                scanf("%d", &A[i][j]);
            }
        }

        for (int i = 0; i < k; i++) {
            for (int j = 0; j < k; j++) {
                G[i][j] = check(i, j);
            }
        }

        for (int i = 0; i < (1 << k); i++) fill(dp[i], dp[i] + k, (int)1e9);

        for (int i = 0; i < k; i++) {
            dp[1 << i][i] = 0;
        }

        for (int msk = 0; msk < (1 << k); msk++) {
            for (int i = 0; i < k; i++) if ((msk >> i) & 1) {
                for (int j = 0; j < k; j++) if (((msk >> j) & 1) == 0) {
                    if (dp[msk ^ (1 << j)][j] > dp[msk][i] + G[i][j]) {
                        dp[msk ^ (1 << j)][j] = dp[msk][i] + G[i][j];
                        p[msk ^ (1 << j)][j] = i;
                    }
                }
            }
        }

        vector<int> ans, res(k);
        int i = (1 << k) - 1;
        int j = min_element(dp[i], dp[i] + k) - dp[i];

        while (i) {
            ans.push_back(j);

            int ni = i ^ (1 << j);
            int nj = p[i][j];
            i = ni, j = nj;
        }
        reverse(ans.begin(), ans.end());

        for (int i = 0; i < k; i++) res[ans[i]] = i;
        for (int i = 0; i < k; i++) printf("%d ", res[i] + 1);
        printf("\n");
    }
	return 0;
}

