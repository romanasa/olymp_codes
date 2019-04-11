#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

typedef long long ll;

using namespace std;

string A[2007];
char used[2007][2007];

int main() {
#ifdef WIN
    freopen("01", "r", stdin);
#endif
    int n, m;
    cin >> n >> m;

    for (int i = 0; i < n; i++) cin >> A[i];

    deque<pair<int, int> > Q;
    Q.push_back({ 0, 0 });

    cout << A[0][0];
    for (int s = 0; s < n - 1 + m - 1; s++) {

        char let = 'z' + 1;

        for (auto c : Q) {
            if (c.first + 1 < n) {
                let = min(let, A[c.first + 1][c.second]);
            }
            if (c.second + 1 < m) {
                let = min(let, A[c.first][c.second + 1]);
            }
        }
        cout << let;

        deque<pair<int, int> > D;
        for (auto c : Q) {
            if (c.first + 1 < n && A[c.first + 1][c.second] == let && !used[c.first + 1][c.second]) {
                D.push_back({ c.first + 1, c.second });
                used[c.first + 1][c.second ] = 1;
            }
            if (c.second + 1 < m && A[c.first][c.second + 1] == let && !used[c.first][c.second + 1]) {
                D.push_back({ c.first, c.second + 1 });
                used[c.first][c.second + 1] = 1;
            }
        }
        Q = D;
    }
    cout << "\n";
    return 0;
}
