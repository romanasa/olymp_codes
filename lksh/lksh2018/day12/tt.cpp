#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <queue>
#include <set>

#define endl '\n'

using namespace std;

typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
//    freopen("owls.in", "r", stdin);
//    freopen("owls.out", "w", stdout);
    int n, m;
    cin >> n >> m;
    vector<vector<int>> g(n);
    vector<pair<int, int>> e(m);
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        e[i] = {a - 1, b - 1};
        g[a - 1].push_back(b - 1);
        g[b - 1].push_back(a - 1);
    }
    for (int i = 0; i < n; ++i) {
        sort(g[i].begin(), g[i].end());
    }
    vector<int> big;
    vector<bool> is_big(n);
    for (int i = 0; i < n; ++i) {
        if (1ll * g[i].size() * g[i].size() >= m) {
            big.push_back(i);
            is_big[i] = 1;
        }
    }
    vector<vector<bool>> big_edges(big.size(), vector<bool>(big.size()));
    for (int i = 0; i < big.size(); ++i) {
        for (int j = i + 1; j < big.size(); ++j) {
            if (binary_search(g[big[i]].begin(), g[big[i]].end(), big[j])) {
                big_edges[i][j] = 1;
                big_edges[j][i] = 1;
            }
        }
    }
    ll ans = 0;
    for (int i = 0; i < big.size(); ++i) {
        for (int j = i + 1; j < big.size(); ++j) {
            for (int k = j + 1; k < big.size(); ++k) {
                if (big_edges[i][j] && big_edges[i][k] && big_edges[j][k]) {
                    ans += 3;
                }
            }
        }
    }
    set<pair<pair<int, int>, int>> s;
    for (int i = 0; i < m; ++i) {
        if (is_big[e[i].first] && is_big[e[i].second]) {
            continue;
        }
        if (g[e[i].first].size() < g[e[i].second].size()) {
            swap(e[i].first, e[i].second);
        }
        for (int nv : g[e[i].second]) {
            if (binary_search(g[nv].begin(), g[nv].end(), e[i].first)) {
                ans++;
                if (is_big[e[i].first] && is_big[nv] && !s.count({{e[i].second, nv}, e[i].first})) {
                    s.insert({{e[i].second, e[i].first}, nv});
                    ans++;
                }
            }
        }
    }
    cout << ans / 3 << endl;
//    fclose(stdin);
//    fclose(stdout);
}