#include <bits/stdc++.h>
#define err(...) //fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

int n, m;

string A[57];

int used[57][57];
int dx[] = { -1, 0, 1, 0 };
int dy[] = { 0, 1, 0, -1 };
int cnt;

bool ok(int i, int j) { return i >= 0 && i < n && j >= 0 && j < m; }

void down() {
    for (int j = 0; j < m; j++) {
        for (int i = 1; i < n; i++) {
            if (A[i][j] == '.') {
                for (int k = i; k > 0; k--) A[k][j] = A[k - 1][j];
                A[0][j] = '.';
            }
        }
    }

    for (int j = m - 1; j >= 0; j--) {
        int ok = 0;
        for (int i = 0; i < n; i++) ok |= (A[i][j] != '.');
        if (!ok) {
            for (int t = j; t + 1 < m; t++) {
                for (int i = 0; i < n; i++) A[i][t] = A[i][t + 1];
            }
            for (int i = 0; i < n; i++) A[i][m - 1] = '.';
        }
    }
}

bool checkall() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) if (A[i][j] != '.') {
            for (int gg = 0; gg < 4; gg++) {
                int ni = i + dx[gg], nj = j + dy[gg];
                if (ok(ni, nj) && A[i][j] == A[ni][nj]) return true;
            }
        }
    }
    return false;
}

bool checknot(char c) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) if (A[i][j] != '.' && A[i][j] != c) {
            for (int gg = 0; gg < 4; gg++) {
                int ni = i + dx[gg], nj = j + dy[gg];
                if (ok(ni, nj) && A[i][j] == A[ni][nj]) return true;
            }
        }
    }
    return false;
}

bool checkcol(char c) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) if (A[i][j] != '.' && A[i][j] == c) {
            for (int gg = 0; gg < 4; gg++) {
                int ni = i + dx[gg], nj = j + dy[gg];
                if (ok(ni, nj) && A[i][j] == A[ni][nj]) return true;
            }
        }
    }
    return false;
}

pair<int, int> cur;

void dfs(int i, int j, char c) {

    if (i > cur.first || (i == cur.first && j < cur.second)) cur = { i, j };

    used[i][j] = 1;
    cnt++;
    for (int gg = 0; gg < 4; gg++) {
        int ni = i + dx[gg], nj = j + dy[gg];
        if (ok(ni, nj) && A[ni][nj] == c && !used[ni][nj])
            dfs(ni, nj, c);
    }
}

void mark(int i, int j, char c) {
    A[i][j] = '.';
    for (int gg = 0; gg < 4; gg++) {
        int ni = i + dx[gg], nj = j + dy[gg];
        if (ok(ni, nj) && A[ni][nj] == c) mark(ni, nj, c);
    }
}

string B[57];

int game(char c) {

    err("st %c\n", c);

    int score = 0;
    for (int i = 0; i < n; i++) A[i] = B[i];

    while (checkall()) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) err("%c", A[i][j]);
            err("\n");
        }
        while (checknot(c)) {
            err("ok1\n");
            vector<pair<int, pair<int, int>>> G;

            for (int i = 0; i < n; i++) fill(used[i], used[i] + m, 0);

            for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) {
                    if (!used[i][j] && A[i][j] != '.' && A[i][j] != c) {
                        cnt = 0;
                        cur = { i, j };

                        dfs(i, j, A[i][j]);

                        err("i = %d, j = %d, cnt = %d\n", i, j, cnt);
                        if (cnt > 1) G.push_back({ -cnt, { -cur.first, cur.second } });
                    }
                }
            }
            err("ok2\n");

            sort(G.begin(), G.end());
            G[0].first *= -1;
            G[0].second.first *= -1;
            err("G[0] = { %d, {%d, %d} }\n", G[0].first, G[0].second.first, G[0].second.second);
            mark(G[0].second.first, G[0].second.second, A[G[0].second.first][G[0].second.second]);
            down();
            score += (G[0].first - 1) * G[0].first;


            for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) err("%c", A[i][j]);
                err("\n");
            }
        }
        err("ok3\n");

        if (checkcol(c)) {
            vector<pair<int, pair<int, int>>> G;
            for (int i = 0; i < n; i++) fill(used[i], used[i] + m, 0);
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) {
                    if (!used[i][j] && A[i][j] != '.' && A[i][j] == c) {
                        cnt = 0;
                        cur = { i, j };
                        dfs(i, j, A[i][j]);
                        if (cnt > 1) G.push_back({ -cnt, { -cur.first, cur.second } });
                    }
                }
            }

            sort(G.begin(), G.end());
            G[0].first *= -1;
            G[0].second.first *= -1;
            err("G[0] = { %d, {%d, %d} }\n", G[0].first, G[0].second.first, G[0].second.second);

            mark(G[0].second.first, G[0].second.second, A[G[0].second.first][G[0].second.second]);
            down();

            score += (G[0].first - 1) * G[0].first;
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) err("%c", A[i][j]);
            err("\n");
        }
    }
    err("sc = %d\n", score);
    return score;
}

char let[] = { 'B', 'G', 'R', 'W', 'Y' };

int main() {
#ifdef WIN
    freopen("01.in", "r", stdin);
#else
    freopen("input.txt", "r", stdin), freopen("output.txt", "w", stdout);
#endif
    cin >> n >> m;

    for (int i = 0; i < n; i++) cin >> A[i];
    for (int i = 0; i < n; i++) B[i] = A[i];

    for (int it = 0; it < 5; it++) {
        int ok = 0;
        for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) ok |= (A[i][j] == let[it]);
        if (ok) cout << let[it] << ": " << game(let[it]) << "\n";
        for (int i = 0; i < n; i++) A[i] = B[i];
    }

    return 0;
}


