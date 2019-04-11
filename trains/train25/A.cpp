#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define TASK "binary"

void no() {
    cout << "0\n";
    exit(0);
}

vector<vector<pair<int, int> > > E;

const int dd = (int)1e3 + 7;
const int mod = (int)1e9 + 7;

int used[dd];
int col[dd];

void dfs(int v, int cc) {
    col[v] = cc;
    used[v] = 1;

    for (auto c : E[v]) {
        int to = c.first;
        if (used[to]) continue;
        dfs(to, cc ^ c.second);
    }
}

int main() {
#ifdef WIN
    freopen("01", "r", stdin);
#else
    freopen(TASK".in", "r", stdin);
    freopen(TASK".out", "w", stdout);
#endif // WIN

    int n;
    cin >> n;

    E.resize(n);

    vector<int> z(n);
    for (int i = 0; i < n; i++) cin >> z[i];


    if (z[0] == -1) z[0] = 0;
    if (z[0] != 0) no();

    for (int i = 0; i < n; i++) if (i + z[i] > n) no();

    for (int i = 1; i < n; i++) {
        if (z[i] == -1) continue;
        if (z[i] == 0) {
            E[0].push_back({ i, 1 });
            E[i].push_back({ 0, 1 });
        } else {
            for (int j = 0; j < z[i]; j++) {
                E[j].push_back({ i + j, 0 });
                E[i + j].push_back({ j, 0 });
            }
            if (i + z[i] < n) E[i + z[i]].push_back({ z[i], 1 });
            if (i + z[i] < n) E[z[i]].push_back({ i + z[i], 1 });
        }
    }


    int cnt = 0;
    for (int i = 0; i < n; i++) if (!used[i]) {
        dfs(i, 0);
        cnt++;
    }

    for (int v = 0; v < n; v++) {
        for (auto c : E[v]) {
            int to = c.first;
            if (c.second == 0 && col[v] != col[to]) no();
            if (c.second == 1 && col[v] == col[to]) no();
        }
    }

    int ans = 1;
    for (int i = 0; i < cnt; i++) ans = (ans + ans) % mod;
    cout << ans;


    return 0;
}


