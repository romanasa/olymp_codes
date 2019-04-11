#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

struct pt { ll x, y; };

struct vt {
    ll x, y;
    vt() {}
    vt(pt A, pt B) { x = B.x - A.x, y = B.y - A.y; }
    ll operator % (vt b) {
        return x * b.y - y * b.x;
    }
};

ll dist(pt A, pt B) {
    return (B.x - A.x) * (B.x - A.x) + (B.y - A.y) * (B.y - A.y);
}

vector<pt> Convex(vector<pt> P) {
    if (P.empty()) return P;

    sort(P.begin(), P.end(), [](pt A, pt B){ return A.x == B.x ? A.y < B.y : A.x < B.x; });

    pt O = P[0];

    sort(P.begin() + 1, P.end(), [O](pt A, pt B) {
        ll t = vt(O, A) % vt(O, B);
        if (t == 0) return dist(O, A) < dist(O, B);
        return t > 0;
    });

    vector<pt> st;
    for (auto p : P) {
        while (st.size() > 1 && (vt(st[st.size() - 2], st.back()) % vt(st.back(), p)) <= 0)
            st.pop_back();
        st.push_back(p);
    }
    return st;
}

const int dd = (int)2e5 + 1;

struct Fen {
    int T[dd];

    void upd(int pos, int val) {
        for (int i = pos + 1; i < dd; i += (i&-i)) T[i] += val;
    }

    int get(int pos) {
        int res = 0;
        for (int i = pos + 1; i; i -= (i&-i)) res += T[i];
        return res;
    }

    int get(int l, int r) {
        return get(r) - get(l - 1);
    }
} T;

unordered_set<int> M[dd];

struct ev {
    int l, r, tp, ind;
};

vector<ev> E[dd];
set<int> S;

int main() {
#ifdef WIN
    freopen("input.txt", "r", stdin);
#endif
    int n, m;
    while (scanf("%d %d", &n, &m) == 2) {
        if (n == 0) break;

        S.clear();

        vector<pt> P(m);
        for (int i = 0; i < m; i++) {
            scanf("%I64d %I64d", &P[i].x, &P[i].y);
            S.insert(P[i].x);
            S.insert(P[i].x + 1);
            S.insert(P[i].x - 1);
        }

        S.insert(0), S.insert(n + 1);

        for (int i : S) M[i].clear();
        for (int i : S) E[i].clear();

        for (int i = 0; i < m; i++) {
            M[P[i].x].insert(P[i].y);
        }


        for (int i = 0; i < m; i++) {
            int x = P[i].x, y = P[i].y;
            {
                //if (x != 6 || y != 6) continue;
                if (M[x + 1].count(y) && M[x].count(y + 1)) {
                    //x + 1, y + 1
                    E[x + 1].push_back({ y + 1, n + 1, 1, 4 * i });
                    E[n + 1].push_back({ y + 1, n + 1, -1, 4 * i });
                }

                if (M[x - 1].count(y) && M[x].count(y + 1)) {
                    E[0].push_back({ y + 1, n + 1, 1, 4 * i + 1 });
                    E[x - 1].push_back({ y + 1, n + 1, -1, 4 * i + 1 });
                }

                if (M[x - 1].count(y) && M[x].count(y - 1)) {
                    E[0].push_back({ 0, y - 1, 1, 4 * i + 2 });
                    E[x - 1].push_back({ 0, y - 1, -1, 4 * i + 2 });
                }
                if (M[x + 1].count(y) && M[x].count(y - 1)) {
                    E[x + 1].push_back({ 0, y - 1, 1, 4 * i + 3 });
                    E[n + 1].push_back({ 0, y - 1, -1, 4 * i + 3 });
                }
            }
        }


        vector<pt> Q;
        vector<int> res(4 * m + 7);


        for (int i : S) {
            for (auto c : E[i]) if (c.tp == 1) {
                res[c.ind] -= T.get(c.l, c.r);
            }
            for (auto c : M[i]) {
                T.upd(c, 1);
            }
            for (auto c : E[i]) if (c.tp == -1) {
                res[c.ind] += T.get(c.l, c.r);
            }
        }

        for (int i = 0; i < 4 * m; i++) {
            if (res[i] > 0) {
                int ind = i / 4, t = i % 4;
                if (t == 0) Q.push_back(P[ind]);
                if (t == 1) Q.push_back({ P[ind].x - 1, P[ind].y });
                if (t == 2) Q.push_back({ P[ind].x - 1, P[ind].y - 1 });
                if (t == 3) Q.push_back({ P[ind].x, P[ind].y - 1 });
            }
        }

        Q = Convex(Q);
        reverse(Q.begin(), Q.end());

        int ind = 0;
        for (int i = 0; i < (int)Q.size(); i++)
            if (make_pair(Q[i].x, Q[i].y) < make_pair(Q[ind].x, Q[ind].y)) ind = i;

        printf("%d\n", (int)Q.size());
        for (int i = ind; i < (int)Q.size(); i++) printf("%I64d %I64d\n", Q[i].x, Q[i].y);
        for (int i = 0; i < ind; i++) printf("%I64d %I64d\n", Q[i].x, Q[i].y);

        for (int i : S) {
            for (auto c : M[i]) {
                T.upd(c, -1);
            }
        }

    }
	return 0;
}

