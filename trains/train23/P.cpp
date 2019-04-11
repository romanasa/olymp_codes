#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

vector<vector<int> > E = {
    { },
    { 2, 3, 4, 5, 6 },
    { 1, 3, 6, 7, 11 },
    { 1, 2, 4, 7, 8 },
    { 1, 3, 5, 8, 9 },
    { 1, 4, 6, 9, 10 },
    { 1, 2, 5, 10, 11 },
    { 2, 3, 8, 11, 12 },
    { 3, 4, 7, 9, 12 },
    { 4, 5, 8, 10, 12 },
    { 5, 6, 9, 11, 12 },
    { 2, 6, 7, 10, 12 },
    { 7, 8, 9, 10, 11 },
};

int dp[15][15][15];
int u[15][15][15];

int calc(int a, int b, int c) {
    if (a == c || b == c) return 1;
    if (dp[a][b][c] != -1) return dp[a][b][c];
    if (u[a][b][c]) return (int)1e9;


    u[a][b][c] = 1;
    int t = (int)1e9;

    for (int toa : E[a]) {
        int cur = -1;
        if (toa == c) t = 1;
        for (int toc : E[c]) {
            cur = max(cur, calc(toa, b, toc) + 2);
        }
        t = min(t, cur);
    }

    for (int tob : E[b]) {
        int cur = -1;
        if (tob == c) t = 1;
        for (int toc : E[c]) {
            cur = max(cur, calc(a, tob, toc) + 2);
        }
        t = min(t, cur);
    }
    return dp[a][b][c] = t;
}

int main() {
    freopen("dodeca.in", "r", stdin);
    freopen("dodeca.out", "w", stdout);

    for (int i = 0; i < 15; i++)
        for (int j = 0; j < 15; j++)
            for (int k = 0; k < 15; k++)
                dp[i][j][k] = -1;


    int d;
    cin >> d;

    int a = 1;
    int b = -1;

    if (d == 0) b = 1;
    if (d == 1) b = 2;
    if (d == 2) b = 7;
    if (d == 3) b = 12;

    int ans = -1;

    for (int c = 0; c < 12; c++) {
        ans = max(ans, calc(a, b, c));
    }

    cout << ans << "\n";


    return 0;
}

