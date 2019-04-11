#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

const int dd = 1e5 + 7;

struct edge {
    int v, to, c, f, w, back, ind;
};

vector<vector<edge> > E;

void add(int a, int b, int c, int w, int ind) {
    int ia = E[b].size(), ib = E[a].size();

    edge cur{ a, b, c, 0,  w, ia, ind };
    edge rev{ b, a, 0, 0, -w, ib, -1 };

    E[a].push_back(cur);
    E[b].push_back(rev);
}

int n, m;

ll findflow(int s, int t, int k) {

    ll cost = 0;
    ll flow = 0;

    while (1) {

        vector<int> d(n, (int)1e9);
        vector<int> used(n, false);
        vector<pair<int, int> > p(n, { -1, -1 });

        queue<int> q;

        q.push(s);
        used[s] = true;
        d[s] = 0;

        while (q.size()) {
            int v = q.front();

            used[v] = false;
            q.pop();

            for (int i = 0; i < (int)E[v].size(); i++) {

                auto &e = E[v][i];

                if (e.f < e.c && d[e.to] > d[v] + e.w) {

                    p[e.to] = { v, i };
                    d[e.to] = d[v] + e.w;

                    if (!used[e.to]) {
                        q.push(e.to);
                        used[e.to] = true;
                    }
                }
            }
        }

        if (p[t].first == -1) {
            break;
        }

        int add = k - flow;

        for (int i = t; p[i].first != -1; i = p[i].first) {
            add = min(add, E[p[i].first][p[i].second].c - E[p[i].first][p[i].second].f);
        }

        for (int i = t; p[i].first != -1; i = p[i].first) {
            auto &e = E[p[i].first][p[i].second];

            cost += 1ll * add * e.w;

            e.f += add;
            E[e.to][e.back].f -= add;
        }

        flow += add;

        if (add == 0)
            break;
    }

    if (flow < k)
        return -1;

    return cost;
}

vector<int> cur;
int used[dd];

bool find(int v, int t) {
    used[v] = true;
    
    if (v == t) {
        return true;
    }

    for (auto &e : E[v]) {
        if (e.f > 0 && e.ind > 0 && !used[e.to]) {
            if (find(e.to, t)) {

                e.f--;

                cur.push_back(e.ind);
                return true;
            }
        }
    }
    return false;
}


int main() {
    int k;
    cin >> n >> m >> k;

    E.resize(n);

    for (int i = 0; i < m; i++) {
        int a, b, w;
        cin >> a >> b >> w;

        a--, b--;
        add(a, b, 1, w, i + 1);
        add(b, a, 1, w, i + 1);
    }

    ll ans = findflow(0, n - 1, k);

    if (ans == -1) {
        printf("%I64d", ans);
        return 0;
    }

    printf("%.10f\n", ans * 1.0 / k);
	
    for (int i = 0; i < k; i++) {
        cur.clear();
        fill(used, used + n, 0);

        find(0, n - 1);

        auto path = cur;
        reverse(path.begin(), path.end());

        printf("%d ", (int)path.size());
        for (int x : path) printf("%d ", x);
        printf("\n");
    }

    return 0;
}