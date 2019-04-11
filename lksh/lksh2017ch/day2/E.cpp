#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

struct edge {
    int to, f, c, b;
};

const int maxN = 80 * 80 + 7;
int used[maxN];
const int dd = 87;

vector<vector<edge> > E;

void add(int a, int b, int c) {
    //err("%d--%d--->%d\n", a, c, b);
    int ia = (int)E[b].size();
    int ib = (int)E[a].size();
    E[a].push_back({ b, 0, c, ia });
    E[b].push_back({ a, 0, 0, ib });
}

int dfs(int v, int t, int cmin) {
    if (v == t) return cmin;
    used[v] = 1;
    for (auto &e : E[v]) {
        if (!used[e.to] && e.f < e.c) {
            int df = dfs(e.to, t, min(cmin, e.c - e.f));
            if (df) {
                e.f += df;
                E[e.to][e.b].f -= df;
                return df;
            }
        }
    }
    return 0;
}

int N;

int findflow(int s, int t) {
    int fl = 0;
    while (1) {
        fill(used, used + N, 0);
        int df = dfs(s, t, (int)1e9);
        if (!df) break;
        fl += df;
    }
    return fl;
}

char A[200][200];

int dx[] = { -1, 0, 1, 0 };
int dy[] = { 0, 1, 0, -1 };
int n;

bool ok(int i, int j) {
    return i >= 0 && i < n && j >= 0 && j < n;
}

int cap[dd][dd];

int main() {
#ifdef WIN
    freopen("01.in", "r", stdin);
#endif

    scanf("%d", &n);

    for (int i = 0; i < 2 * n - 1; i++) {
        scanf("%s", A[i]);
    }

    for (int i = 0; i < n; i++) fill(cap[i], cap[i] + n, 3);

    N = n * n + 7;
    E.resize(N);
    n--;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if ((i + j) % 2) continue;

            int x = 2 * i + 1;
            int y = 2 * j + 1;

            for (int gg = 0; gg < 4; gg++) {
                int ni = i + dx[gg], nj = j + dy[gg];
                int nx = x + dx[gg], ny = y + dy[gg];

                if (ok(ni, nj) && A[nx][ny] != '.') cap[i][j]--, cap[ni][nj]--;
                if (ok(ni, nj) && A[nx][ny] == '.') {
                    add(i * n + j, ni * n + nj, 1);
                    //err("(%d, %d)-->(%d, %d)\n", i, j, ni, nj);
                }
            }
        }
    }

    int s = n * n + 1;
    int t = n * n + 2;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int x = 2 * i + 1;
            int y = 2 * j + 1;
            if ((i + j) % 2 == 0) {
                for (int gg = 0; gg < 4; gg++) {
                    int ni = i + dx[gg], nj = j + dy[gg];
                    int nx = x + dx[gg], ny = y + dy[gg];
                    if (!ok(ni, nj) && A[nx][ny] == '.') add(i * n + j, t, 1);
                    if (!ok(ni, nj) && A[nx][ny] != '.') cap[i][j]--;
                }
            } else {
                for (int gg = 0; gg < 4; gg++) {
                    int ni = i + dx[gg], nj = j + dy[gg];
                    int nx = x + dx[gg], ny = y + dy[gg];
                    if (!ok(ni, nj) && A[nx][ny] == '.') add(s, i * n + j, 1);
                    if (!ok(ni, nj) && A[nx][ny] != '.') cap[i][j]--;
                }
            }
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if ((i + j) % 2) add(i * n + j, t, min(cap[i][j], 3));
            else add(s, i * n + j, min(cap[i][j], 3));
        }
    }
    printf("%d\n", findflow(s, t) + 1);
    return 0;
}
