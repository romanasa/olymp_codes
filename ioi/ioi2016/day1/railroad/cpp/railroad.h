#include <bits/stdc++.h>
#define ll long long
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stdout)

using namespace std;

const int dd = (int)2e5 + 7;
const int inf = (int)1e9 + 7;

struct dsu {
    int P[dd], R[dd];

    dsu() { for (int i = 0; i < dd; i++) P[i] = i, R[i] = 1; }

    int get(int v) { return v == P[v] ? v : P[v] = get(P[v]); }

    bool un(int a, int b) {
        a = get(a), b = get(b);
        if (a != b) {
            if (R[b] > R[a]) swap(a, b);
            P[b] = a, R[a] += R[b];
        }
        return a != b;
    }
} J;

ll plan_roller_coaster(vector<int> s, vector<int> t) {
    int n = (int)s.size();

    vector<pair<int, pair<int, int> > > G, E;
    for (int i = 0; i < n; i++) {
        G.push_back({ s[i], { 1, i } });
        G.push_back({ t[i], { -1, i } });
    }

    G.push_back({ inf, { 1, n } });
    G.push_back({ 1, {-1, n } });

    n++;

    sort(G.begin(), G.end());

    int cur = 0;
    ll ans = 0;

    for (int i = 0; i + 1 < (int)G.size(); i++) {
        cur += G[i].second.first;
        if (cur > 0)
            ans += cur * (G[i + 1].first - G[i].first);
        E.push_back({ G[i + 1].first - G[i].first, { G[i].second.second, G[i + 1].second.second } });
        if (G[i + 1].first == G[i].first || cur) {
            J.un(G[i].second.second, G[i + 1].second.second);
        }
    }
    sort(E.begin(), E.end());

    for (int i = 0; i < (int)E.size(); i++)
        if (J.un(E[i].second.first, E[i].second.second))
            ans += E[i].first;

	return ans;
}
