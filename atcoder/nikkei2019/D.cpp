#include <bits/stdc++.h>
#ifdef SIR
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)
#else
#define err(...) 42
#endif

typedef long long ll;

using namespace std;

vector<vector<int>> E;

void solve() {
    int n, m;
    cin >> n >> m;

    vector<int> in(n);
    E.resize(n);

    for (int i = 0; i < n - 1 + m; i++) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        E[a].push_back(b);
        in[b]++;
    }

    vector<int> pr(n, -1), ans(n, -1);
    set<pair<int, int>> S;
    for (int i = 0; i < n; i++) S.insert({ in[i], i });


    while (S.size()) {
        vector<int> cur;
        while (S.size() && S.begin()->first == 0) {
            cur.push_back(S.begin()->second);
            S.erase(S.begin());
        }

        for (int v : cur) {
            ans[v] = pr[v];
            for (int to : E[v]) {
                pr[to] = v;
                S.erase({ in[to], to });
                in[to]--;
                S.insert({ in[to], to });
            }
        }
    }
    for (int i = 0; i < n; i++) cout << ans[i] + 1 << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
#ifdef SIR
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    solve();
}