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

const int dd = (int)1e5 + 7;
const int LOG = 18;
int C[dd];

vector<vector<int> > E, G;

struct SegmentTree {
    pair<ll, int> T[4 * dd];

    void build(int v, int tl, int tr) {
        if (tl == tr) T[v] = { -1, tl };
        else {
            int tm = (tl + tr) / 2;
            build(v * 2, tl, tm);
            build(v * 2 + 1, tm + 1, tr);
            T[v] = max(T[v * 2], T[v * 2 + 1]);
        }
    }

    void upd(int v, int tl, int tr, int pos, ll val) {
        if (tl == tr) (val > 0 ? T[v].first += val : T[v].first = -1);
        else {
            int tm = (tl + tr) / 2;
            if (pos <= tm) upd(v * 2, tl, tm, pos, val);
            else upd(v * 2 + 1, tm + 1, tr, pos, val);
            T[v] = max(T[v * 2], T[v * 2 + 1]);
        }
    }
    pair<int, int> get(int v, int tl, int tr, int l, int r) {
        if (tl == l && tr == r) return T[v];
        int tm = (tl + tr) / 2;
        if (r <= tm) return get(v * 2, tl, tm, l, r);
        if (l > tm) return get(v * 2 + 1, tm + 1, tr, l, r);
        return max(get(v * 2, tl, tm, l, tm), get(v * 2 + 1, tm + 1, tr, tm + 1, r));
    }
} T;

int used[dd];
int tin[dd], tout[dd];
int pr[dd];
int tmm = 1;

void dfs(int v, int pr = -1) {
    tin[v] = tmm++;
    for (int to : E[v]) {
        dfs(to);
        G[v].push_back(tin[to]);
    }
    tout[v] = tmm++;
}

int main() {
#ifdef WIN
    freopen("01", "r", stdin);
#endif // WIN
    int n;
    scanf("%d", &n);

    E.resize(n);
    G.resize(n);

    pr[0] = -1;
    for (int i = 1; i < n; i++) {
        int p;
        scanf("%d", &p);
        E[p - 1].push_back(i);
        pr[i] = p - 1;
    }


    for (int i = 0; i < n; i++) scanf("%d", &C[i]);

    dfs(0);

    T.build(1, 0, tmm);
    for (int i = 0; i < n; i++) {
        T.upd(1, 0, tmm, tin[i], C[i]);
    }

    int q;
    scanf("%d", &q);

    int v = 0;
    //printf("%d\n", v + 1);

    while (q--) {
        int tp;
        scanf("%d", &tp);

        if (tp == 1) {
            /*if (ok) {
                ok = 0;
                used[v] = 1;
                printf("%d\n", v + 1);
                T.upd(1, 0, tmm, tin[v], -1);
                continue;
            }*/

            used[v] = 1;
            printf("%d\n", v + 1);
            T.upd(1, 0, tmm, tin[v], -1);


            int pos = -1;

            while (1) {
                auto c = T.get(1, 0, tmm, tin[v], tout[v]);
                pos = c.second;
                if (c.first >= 0) break;

                if (v == 0) return 0;
                v = pr[v];
            }


            int ind = upper_bound(G[v].begin(), G[v].end(), pos) - G[v].begin() - 1;

            v = E[v][ind];
        } else {
            int a, b;
            scanf("%d %d", &a, &b);
            a--;

            if (used[a]) continue;
            T.upd(1, 0, tmm, tin[a], b);
        }
    }

    return 0;
}

