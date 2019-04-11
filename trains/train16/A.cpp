#include <bits/stdc++.h>

using namespace std;

string A[57][57];
int d[57][57][57];

int dx[] = { -1, 0, 1, 0 };
int dy[] = { 0, 1, 0, -1 };

struct cond {
    int i, j, k;
};

int main() {
#ifdef WIN
    freopen("01", "r", stdin);
#endif // WIN
    int n, m, t;
    cin >> n >> m >> t;

    int si = -1, sj = -1, sk = -1;
    int fi = -1, fj = -1, fk = -1;

    for (int it = 0; it < t; it++) {
        for (int i = 0; i < n; i++) {
            cin >> A[it][i];
            for (int j = 0; j < m; j++) {
                if (A[it][i][j] == 'A') si = i, sj = j, sk = it;
                if (A[it][i][j] == 'E') fi = i, fj = j, fk = it;
            }
        }
    }

    A[sk][si][sj] = '.';
    A[fk][fi][fj] = '.';

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            for (int k = 0; k < t; k++) {
                d[k][i][j] = (int)1e9;
            }
        }
    }

    deque<cond> Q;
    Q.push_back({ si, sj, sk });
    d[sk][si][sj] = 0;

    while (Q.size()) {
        int i = Q.front().i, j = Q.front().j, k = Q.front().k;
        Q.pop_front();

        //cerr << i << ", " << j << ", " << k << endl;

        if (i == fi && j == fj && k == fk) return 0 * puts("Yes");

        if (A[k][i][j] == 's') {
            if (k > 0 && A[k - 1][i][j] == 's' && d[k - 1][i][j] > d[k][i][j] + 1) {
                d[k - 1][i][j] = d[k][i][j] + 1;
                Q.push_back({ i, j, k - 1 });
            }
            if (k + 1 < t && A[k + 1][i][j] == 's' && d[k + 1][i][j] > d[k][i][j] + 1) {
                d[k + 1][i][j] = d[k][i][j] + 1;
                Q.push_back({ i, j, k + 1 });
            }
        }

        for (int gg = 0; gg < 4; gg++) {
            int ni = i + dx[gg], nj = j + dy[gg];


            if (ni < 0 || nj < 0 || ni >= n || nj >= m) continue;

            if (A[k][ni][nj] == 'w') {
                int nk = k;
                while (nk + 1 < t && A[nk + 1][ni][nj] == 'w') nk++;

                if (d[nk][ni][nj] > d[k][i][j] + 1) {
                    d[nk][ni][nj] = d[k][i][j] + 1;
                    Q.push_back({ ni, nj, nk });
                }
            } else {
                if (d[k][ni][nj] > d[k][i][j] + 1) {
                    d[k][ni][nj] = d[k][i][j] + 1;
                    Q.push_back({ ni, nj, k });
                }
            }
        }
    }
    puts("No");
    return 0;
}
