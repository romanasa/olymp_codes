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

int dx[] = { -1, 0, 1, 0 };
int dy[] = { 0, 1, 0, -1 };

vector<vector<int> > used;
vector<string> A;

int n, m;

bool ok(int i, int j) { return i >= 0 && i < n && j >= 0 && j < m; }

void dfs(int i, int j, int c) {
    used[i][j] = c;
    for (int gg = 0; gg < 4; gg++) {
        int ni = i + dx[gg];
        int nj = j + dy[gg];
        if (ok(ni, nj) && A[ni][nj] == '0' && !used[ni][nj]) dfs(ni, nj, c);
    }
}


const int dd = (int)1e6 + 7;
struct dsu {
    int P[dd], R[dd];
    dsu() { for (int i = 0; i < dd; i++) P[i] = i, R[i] = 1; }
    int get(int v) { return v == P[v] ? v : P[v] = get(P[v]); }
    void un(int a, int b) {
        a = get(a), b = get(b);
        if (a != b) {
            if (R[b] > R[a]) swap(a, b);
            P[b] = a, R[a] += R[b];
        }
    }
} J;

int main() {
#ifdef WIN
    freopen("01", "r", stdin);
#endif // WIN
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> m;

    used.resize(n);
    for (int i = 0; i < n; i++) used[i].resize(m);


    A.resize(n);
    for (int i = 0; i < n; i++) cin >> A[i];

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (A[i][j] == '0') A[i][j] = '1';
            else A[i][j] = '0';
        }
    }

    int comp = 0;
    int tr = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (A[i][j] == '0' && !used[i][j]) dfs(i, j, ++comp);
            if (A[i][j] == '1') tr++;
        }
    }


    vector<int> ans(n, vector<int>(m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            ans[i * m + j] = (A[i][j] == '1' ? ++comp : used[i][j]);
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) if (A[i][j] == '1') {

            map<int, int> S;
            for (int gg = 0; gg < 4; gg++) {
                int ni = i + dx[gg], nj = j + dy[gg];
                if (ok(ni, nj) && A[ni][nj] == '0') {
                    S[ans[J.get(ni * m + nj)]] = ni * m + nj;
                }
            }

            if (S.size() == 4) {
                for (auto it = S.begin(); it != S.end(); ++it) {
                    if (it == S.begin()) continue;
                    auto pr = prev(it);
                    J.un(pr->second, it->second);
                }
                tr--;
                comp -= 3;

            }
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) if (A[i][j] == '1') {

            map<int, int> S;
            for (int gg = 0; gg < 4; gg++) {
                int ni = i + dx[gg], nj = j + dy[gg];
                if (ok(ni, nj) && A[ni][nj] == '0') {
                    S[ans[J.get(ni * m + nj)]] = ni * m + nj;
                }
            }

            if (S.size() == 3) {
                for (auto it = S.begin(); it != S.end(); ++it) {
                    if (it == S.begin()) continue;
                    auto pr = prev(it);
                    J.un(pr->second, it->second);
                }
                tr--;
                comp -= 2;
            }
        }
    }

    if (tr > 0 && tr > comp) {
        cout << "YES\n";
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                cout << ans[J.get(i * m + j)] << " ";
            }
            cout << "\n";
        }
    } else {
        cout << "NO\n";
    }

    return 0;
}

