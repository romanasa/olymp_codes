#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int dp[65][65][5];
int used[65][65][5];
int deg[65][65][5];

int dx[] = { -1, 0, 1, 0 };
int dy[] = { 0, 1, 0, -1 };
const int n = 8;

bool ok(int i, int j) { return i >= 0 && i < 8 && j >= 0 && j < 8; }

void dfs(int pos1, int pos2, int c) {
    used[pos1][pos2][c] = 1;

    int i = -1, j = -1;
    if (c == 2) i = pos1 / n, j = pos1 % n;
    else i = pos2 / n, j = pos2 % n;

    //cout << pos1 << " " << pos2 <<  " " << c << endl;

    for (int gg = 0; gg < 4; gg++) {
        int ni = i + dx[gg], nj = j + dy[gg];
        if (!ok(ni, nj)) continue;


        int npos1 = pos1;
        int npos2 = pos2;

        if (c == 2) npos1 = ni * n + nj;
        else npos2 = ni * n + nj;

        if (dp[pos1][pos2][c] == 0) {
            dp[npos1][npos2][3 - c] = 1;
            //cerr << npos1 << " " << npos2 << " " << 3 - c << "=" << 1 << endl;

            if (!used[npos1][npos2][3 - c]) dfs(npos1, npos2, 3 - c);
        } else {

            if (--deg[npos1][npos2][3 - c] == 0) {
                dp[npos1][npos2][3 - c] = 0;
                //cerr << npos1 << " " << npos2 << " " << 3 - c << "=" << 0 << endl;
                if (!used[npos1][npos2][3 - c]) dfs(npos1, npos2, 3 - c);
            }
        }
    }
}


void init() {
    for (int pos1 = 0; pos1 < n * n; pos1++) {
        for (int pos2 = 0; pos2 < n * n; pos2++) {

            for (int c = 1; c <= 2; c++) {

                dp[pos1][pos2][c] = -1;

                int i = -1, j = -1;
                if (c == 1) i = pos1 / n, j = pos1 % n;
                else i = pos2 / n, j = pos2 % n;

                for (int gg = 0; gg < 4; gg++) {
                    int ni = i + dx[gg], nj = j + dy[gg];
                    if (ok(ni, nj)) deg[pos1][pos2][c]++;
                }
            }
        }
    }


    for (int pos = 0; pos < n * n; pos++) {
        for (int c = 1; c <= 2; c++) {
            dp[pos][pos][c] = 0;
        }
    }
    //dfs(48, 48, 1);

    for (int pos = 0; pos < n * n; pos++) {
        for (int c = 1; c <= 2; c++) {
            if (!used[pos][pos][c]) dfs(pos, pos, c);
        }
    }
}

int get(string s) {  return (s[0] - 'a') + (7 - (s[1] - '1')) * 8; }

int main() {
    freopen("endspiel.in", "r", stdin);
    freopen("endspiel.out", "w", stdout);
    init();

    string a, b, c;
    cin >> a >> b >> c;

    int pos1 = get(a), pos2 = get(b);
    int q = (c == "B" ? 2 : 1);

    if (dp[pos1][pos2][q] == 1) {
        if (q == 1) cout << "White wins\n";
        else cout << "Black wins\n";
    } else if (dp[pos1][pos2][q] == 0) {
        if (q == 1) cout << "Black wins\n";
        else cout << "White wins\n";
    } else cout << "Draw\n";

    return 0;
}

