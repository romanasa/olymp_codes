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

vector<string> a;

int dx[] = { -1, 0, 1, 0 };
int dy[] = { 0, 1, 0, -1 };

int n, m;
bool ok(int i, int j) { return i >= 0 && i < n && j >= 0 && j < m; }

int cur[123][123];
int used[123][123];

int cT = 0, cH = 0;
void dfs(int i, int j, int c) {
    if (a[i][j] == '1') cT++;
    if (a[i][j] == '0') cH++;
    used[i][j] = 1;
    for (int gg = 0; gg < 4; gg++) {
        int ni = i + dx[gg];
        int nj = j + dy[gg];
        if (ok(ni, nj) && cur[ni][nj] == c && !used[ni][nj]) dfs(ni, nj, c);
    }
}

void go(int num, int c) {
    if (num == n * m) {

        for (int i = 0; i < n; i++) fill(used[i], used[i] + m, 0);

        int qT = 0, qH = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (!used[i][j]) {
                    cT = 0, cH = 0;
                    dfs(i, j, cur[i][j]);
                    if (cT > cH) qT++;
                    if (cH > cT) qH++;
                }
            }
        }
        if (qT > qH) {
            puts("YES");
            exit(0);
        }

    } else {
        for (int x = 0; x < c; x++) {
            cur[num / m][num % m] = x;
            go(num + 1, c);
        }
    }

}

int main() {
#ifdef WIN
    freopen("01", "r", stdin);
#endif // WIN
    cin >> n >> m;

    a.resize(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    for (int c = 0; c < n * m; c++) {
        go(0, c);
    }
    puts("NO");
    return 0;
}

