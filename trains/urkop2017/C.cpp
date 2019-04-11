#include <bits/stdc++.h>

#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

#define x first
#define y second
#define mp make_pair
#define pub push_back
#define all(v) (v).begin(), (v).end()

using namespace std;

typedef long long ll;
typedef double db;

struct ev {
    int tp, col, a, b, c, d;
};

const int maxC = 507;
vector<ev> E[maxC];

int dx[] = {  0, 0, -1, 1 };
int dy[] = {  1, -1, 0, 0 };
int n, m;

bool ok(int i, int j) { return i >= 1 && i <= n && j >= 1 && j <= m; }

ll dist(int x1, int y1, int x2, int y2) {
    return 1ll * (x2 - x1) * (x2 - x1) + 1ll * (y2 - y1) * (y2 - y1);
}


const int dd = 507;
struct SegmentTree {
    int P[8 * dd];
    int val[8 * dd];

    void clear(int n) {
        fill(P, P + 8 * (n + 1) + 7, -1);
        fill(val, val + 8 * (n + 1) + 7, 0);
    }

    void push(int v) {
        if (P[v] != -1) {
            val[v] = P[v];
            P[v * 2] = P[v];
            P[v * 2 + 1] = P[v];
            P[v] = -1;
        }
    }

    void upd(int v, int tl, int tr, int l, int r, int val) {
        push(v);
        if (tl == l && tr == r) {
            P[v] = val;
        } else {
            int tm = (tl + tr) / 2;
            if (r <= tm) upd(v * 2, tl, tm, l, r, val);
            else if (l > tm) upd(v * 2 + 1, tm + 1, tr, l, r, val);
            else upd(v * 2, tl, tm, l, tm, val), upd(v * 2 + 1, tm + 1, tr, tm + 1, r, val);
        }
    }

    void out(int v, int tl, int tr) {
        push(v);
        if (tl == tr) printf("%d ", val[v]);
        else {
            int tm = (tl + tr) / 2;
            out(v * 2, tl, tm);
            out(v * 2 + 1, tm + 1, tr);
        }
    }
} T;

int main() {
#ifdef WIN
    freopen("01", "r", stdin);
#endif // WIN
    scanf("%d %d", &n, &m);

    int q;
    scanf("%d", &q);

    vector<ev> st;
    int pos = 0;

    while (q--) {
        int tp;
        scanf("%d", &tp);

        if (tp == 1) {
            int col, x1, y1, x2, y2;
            scanf("%d %d %d %d %d", &col, &x1, &y1, &x2, &y2);

            while ((int)st.size() > pos) st.pop_back();

            st.push_back({ 1, col, x1, y1, x2, y2 });
            pos = (int)st.size();
        }
        if (tp == 2) {
            int col, x, y;
            scanf("%d %d %d", &col, &x, &y);

            while ((int)st.size() > pos) st.pop_back();

            st.push_back({ 2, col, x, y, -1, -1 });
            pos = (int)st.size();
        }
        if (tp == 3) {
            int col, x1, y1, x2, y2;
            scanf("%d %d %d %d %d", &col, &x1, &y1, &x2, &y2);

            while ((int)st.size() > pos) st.pop_back();

            st.push_back({ 3, col, x1, y1, x2, y2 });
            pos = (int)st.size();
        }
        if (tp == 4) {
            pos--;
            if (pos < 0) pos = 0;
        }
        if (tp == 5) {
            pos++;
            if (pos > (int)st.size()) pos = (int)st.size();
        }
    }

    while ((int)st.size() > pos) st.pop_back();

    //2 - seg, 1 - pt
    for (auto c : st) {
        if (c.tp == 1) {
            for (int i = c.a; i <= c.c; i++) E[i].push_back({ 2, c.col, c.b, c.d });
        } else if (c.tp == 2) {
            E[c.a].push_back({ 1, c.col, c.b });
        } else if (c.tp == 3) {

            int x1 = c.a, y1 = c.b;
            int x2 = c.c, y2 = c.d;

            //err("x1 = %d, y1 = %d, x1 = %d, y2 = %d\n", x1, y1, x2, y2);

            E[x1].push_back({ 1, c.col, y1 });
            while (x1 != x2 || y1 != y2) {

                int gx = -1, gy = -1;
                for (int gg = 0; gg < 4; gg++) {
                    int ni = x1 + dx[gg], nj = y1 + dy[gg];
                    if (ok(ni, nj)) {
                        if (gx == -1) gx = ni, gy = nj;
                        else if (dist(gx, gy, x2, y2) > dist(ni, nj, x2, y2)) gx = ni, gy = nj;
                    }
                }
                //err("%d, %d -> %d, %d\n", x1, y1, gx, gy);
                x1 = gx;
                y1 = gy;
                E[x1].push_back({ 1, c.col, y1 });
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        vector<int> cur(m + 1);

        T.clear(m + 1);
        for (auto c : E[i]) {
            if (c.tp == 1) T.upd(1, 1, m, c.a, c.a, c.col);
            else T.upd(1, 1, m, c.a, c.b, c.col);
        }
        T.out(1, 1, m); printf("\n");
    }

    return 0;
}
