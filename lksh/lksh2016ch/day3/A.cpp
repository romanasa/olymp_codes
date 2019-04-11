#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int dd = (int)2e5 + 7;

const int inf = (int)1e9 + 7;

struct dsu {
    int P[dd], R[dd];
    int cnt;

    dsu() {
        for (int i = 0; i < dd; i++)
            P[i] = i, R[i] = 1;
    }

    int get(int v) {
        return v == P[v] ? v : P[v] = get(P[v]);
    }

    void un(int a, int b) {
        a = get(a), b = get(b);
        if (a != b) {
            if (R[b] > R[a])
                swap(a, b);

            P[b] = a;
            R[a] += R[b];
            cnt--;
        }
    }
} J;

struct edge { int v, to, c, ind; };
vector<edge> F[dd];
vector<vector<pair<int, int> > > E;

long long ans[dd];
int cnt[dd], used[dd];
int N;

int dfs0(int v, int p) {
    int sz = J.R[J.get(v)];
    for (auto c : E[v]) {
        int to = c.first;
        if (to != p)
            sz += dfs0(to, v);
    }
    return sz;
}

int dfs(int v, int p) {
    used[v] = true;
    cnt[v] = J.R[J.get(v)];

    for (auto c : E[v]) {
        int to = c.first;
        if (to != p) {
            cnt[v] += dfs(to, v);

            ans[c.second] += 1ll * cnt[to] * (N - cnt[to]);
        }
    }
    return cnt[v];
}


int main() {
    int n;
    scanf("%d", &n);

    E.resize(n);
    J.cnt = n;

    vector<edge> T;
    vector<int> G;
    for (int i = 0; i < n - 1; i++) {
        int a, b, c;
        scanf("%d %d %d", &a, &b, &c);
        a--, b--;

        T.push_back({ a, b, c, i });
        G.push_back(c);
    }

    sort(G.begin(), G.end());
    G.resize(unique(G.begin(), G.end()) - G.begin());

    for (int i = 0; i < n - 1; i++) {
        T[i].c = lower_bound(G.begin(), G.end(), T[i].c) - G.begin();
        F[T[i].c].push_back( T[i] );
    }

    for (int i = 0; i < n; i++) {
        for (auto e : F[i]) {
            E[J.get(e.v)].push_back({ J.get(e.to), e.ind });
            E[J.get(e.to)].push_back({ J.get(e.v), e.ind });
        }

        for (auto e : F[i]) {
            if (!used[J.get(e.v)]) {
                N = dfs0(J.get(e.v), -1);
                dfs(J.get(e.v), -1);
            }
            if (!used[J.get(e.to)]) {
                N = dfs0(J.get(e.to), -1);
                dfs(J.get(e.to), -1);
            }
        }


        for (auto e : F[i]) {
            cnt[J.get(e.v)] = 0;
            cnt[J.get(e.to)] = 0;
            used[J.get(e.v)] = 0;
            used[J.get(e.to)] = 0;
        }

        for (auto e : F[i]) {
            E[J.get(e.v)].pop_back();
            E[J.get(e.to)].pop_back();
        }

        for (auto e : F[i]) {
            J.un(J.get(e.v), J.get(e.to));
        }

    }
    int k = 0;
    
    ll t = *max_element(ans, ans + n - 1);
    
    for (int i = 0; i < n - 1; i++)
        if (ans[i] == t)
            k++;

    printf("%lld %d\n", t * 2, k);


    for (int i = 0; i < n - 1; i++)
        if (ans[i] == t)
            printf("%d ", i + 1);
    return 0;
}