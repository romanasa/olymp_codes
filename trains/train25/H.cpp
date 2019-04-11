#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define TASK "secure"

vector<vector<pair<int, int> > > E;

int main() {
#ifdef WIN
    freopen("01", "r", stdin);
#else
    freopen(TASK".in", "r", stdin);
    freopen(TASK".out", "w", stdout);
#endif // WIN

    int n, m;
    cin >> n >> m;

    vector<int> tp(n);
    for (int i = 0; i < n; i++) cin >> tp[i];

    E.resize(n + 2);

    for  (int i = 0; i < m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        E[a - 1].push_back({ b - 1, c });
        E[b - 1].push_back({ a - 1, c });
    }

    int s = n;
    int t = n + 1;

    for (int i = 0; i < n; i++) if (tp[i] == 1) E[s].push_back({ i, 0 });
    for (int i = 0; i < n; i++) if (tp[i] == 2) E[i].push_back({ t, 0 });

    set<pair<ll, int> > S;
    vector<ll> d(n + 2, (ll)1e18);
    vector<int> p(n + 2, -1);

    d[s] = 0;
    S.insert({ d[s], s });

    while (S.size()) {
        int v = S.begin()->second;
        S.erase(S.begin());

        for (auto c : E[v]) {
            int to = c.first;
            if (d[to] > d[v] + c.second) {
                S.erase({ d[to], to });
                d[to] = d[v] + c.second, p[to] = v;
                S.insert({ d[to], to });
            }
        }
    }

    if (d[t] == (ll)1e18) cout << -1, exit(0);

    vector<int> path;
    for (int i = p[t]; i != s; i = p[i]) path.push_back(i);
    reverse(path.begin(), path.end());
    cout << path[0] + 1 << " " << path.back() + 1 << " " << d[t] << "\n";

    return 0;
}


