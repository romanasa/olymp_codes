#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

#define all(x) (x).begin(), (x).end()
//#define int ll

void FAST_IO() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    //cout.setf(ios::fixed);
    //cout.precision(20);
    #ifdef _offline
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif // _offline
}

const int MAXN = 1100;
vector<int> edges[MAXN];
vector<int> g[MAXN * 5], gt[MAXN * 5];
vector<int> order;
int used[MAXN * 5];
int comp[MAXN * 5];

pair<char, char> need(char c) {
    if (c == 'R') {
        return {'G', 'B'};
    }
    if (c == 'G') {
        return {'R', 'B'};
    }
    if (c == 'B') {
        return {'R', 'G'};
    }
}

void dfs1(int v) {
    used[v] = 1;
    for (int to : g[v]) {
        if (used[to] != 1) {
            dfs1(to);
        }
    }
    order.push_back(v);
}

void dfs2(int v, int id) {
    used[v] = 2;
    comp[v] = id;
    for (int to : gt[v]) {
        if (used[to] != 2) {
            dfs2(to, id);
        }
    }
}

signed main() {
    FAST_IO();
    int n, m;
    string s;
    cin >> n >> m;
    cin >> s;
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        edges[u].push_back(v);
        edges[v].push_back(u);
    }
    for (int i = 0; i < n; ++i) {
        pair<char, char> cur = need(s[i]);
        for (int to : edges[i]) {
            pair<char, char> nxt = need(s[to]);
            if (s[to] != cur.first) {
                if (nxt.first == cur.first) {
                    g[i].push_back(to + MAXN);
                    gt[to + MAXN].push_back(i);
                }
                else {
                    g[i].push_back(to);
                    gt[to].push_back(i);
                }
            }
            if (s[to] != cur.second) {
                if (nxt.first == cur.second) {
                    g[i + MAXN].push_back(to + MAXN);
                    gt[to + MAXN].push_back(i + MAXN);
                }
                else {
                    g[i + MAXN].push_back(to);
                    gt[to].push_back(i + MAXN);
                }
            }
        }
    }
    for (int i = 0; i < n; ++i) {
        if (used[i] != 1) {
            dfs1(i);
        }
    }
    for (int i = 0; i < n; ++i) {
        if (used[i + MAXN] != 1) {
            dfs1(i + MAXN);
        }
    }
    reverse(all(order));
    int id = 0;
    for (int i : order) {
        if (used[i] != 2) {
            dfs2(i, id++);
        }
    }
    string ans(n, 'a');
    for (int i = 0; i < n; ++i) {
        if (comp[i] == comp[i + MAXN]) {
            cout << "Impossible";
            return 0;
        }
        pair<char, char> cur = need(s[i]);
        if (comp[i] > comp[i + MAXN]) {
            ans[i] = cur.first;
        }
        else {
            ans[i] = cur.second;
        }
    }
    cout << "Possible"; return 0;
    cout << ans;
}