#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__)
 
using namespace std;
 
typedef long long ll;
 
const int dd = (int)2e6 + 1;
 
struct req {
    int tp, r, ind;
    bool operator < (req b) const {
        return (tp == b.tp ? r < b.r : tp < b.tp);
    }
};
 
vector<req> P[dd];
vector<int> H, W[dd];
int L[dd], R[dd];
 
struct st {
    int T[4 * dd + 7];
 
    void upd(int v, int tl, int tr, int pos, int val) {
        if (tl == tr) {
            T[v] = max(T[v], val);
        } else {
            int tm = (tl + tr) / 2;
            if (pos <= tm)
                upd(v * 2, tl, tm, pos, val);
            else
                upd(v * 2 + 1, tm + 1, tr, pos, val);
 
            T[v] = max(T[v * 2], T[v * 2 + 1]);
        }
    }
 
    int get(int v, int tl, int tr, int l, int r) {
        if (l == tl && tr == r)
            return T[v];
        int tm = (tl + tr) / 2;
        if (r <= tm)
            return get(v * 2, tl, tm, l, r);
        if (l > tm)
            return get(v * 2 + 1, tm + 1, tr, l, r);
        return max(get(v * 2, tl, tm, l, tm), get(v * 2 + 1, tm + 1, tr, tm + 1, r));
    }
} F;
 
inline int get(int x) {
    return lower_bound(H.begin(), H.end(), x) - H.begin();
}
 
int main() {
    int n;
    scanf("%d", &n);
 
    vector<pair<int, int> > G(n);
 
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &G[i].first, &G[i].second);
        H.push_back(G[i].first);
        H.push_back(G[i].second);
    }
 
    int m;
    scanf("%d", &m);
 
    vector<pair<int, int> > Q(m);
    vector<int> J(m);
 
    for (int i = 0; i < m; i++) {
        int A, B;
        scanf("%d %d", &A, &B);
        Q[i] = { A, B };
        H.push_back(A);
        H.push_back(B);
    }
 
    sort(H.begin(), H.end());
    H.resize(unique(H.begin(), H.end()) - H.begin());
 
    for (int i = 0; i < n; i++) {
        int l = get(G[i].first), r = get(G[i].second);
        P[l].push_back({ 0, r });
        W[r].push_back(l);
    }
 
    for (int i = 0; i < m; i++) {
        int l = get(Q[i].first), r = get(Q[i].second);
        P[l].push_back({ 1, r, i });
    }
 
    for (int i = dd - 1; i >= 0; i--) {
        if (P[i].empty()) continue;
        sort(P[i].begin(), P[i].end());
 
        for (auto c : P[i]) {
            if (c.tp == 0) {
                F.upd(1, 0, dd, c.r, H[c.r] - H[i]);
                //err("upd %d, %d\n", c.r, H[c.r] - H[i]);
            } else {
                int t = F.get(1, 0, dd, 0, c.r);
                //err("get(%d, %d) = %d\n", 0, c.r, t);
                J[c.ind] = t;
            }
        }
    }
 
    set<int> S;
    for (int i = 0; i < dd; i++) {
        for (auto c : P[i]) {
            if (c.tp == 0) {
                S.insert(c.r);
            } else {
                break;
            }
        }
 
        if (S.size())
            R[i] = *S.rbegin();
        else
            R[i] = -1;
    }
 
    S.clear();
    for (int i = dd - 1; i >= 0; i--) {
         for (auto c : W[i]) {
            S.insert(c);
        }
 
        if (S.size())
            L[i] = *S.begin();
        else
            L[i] = (int)1e9 + 1;
    }
 
    for (int i = 0; i < m; i++) {
        int ans = 0;
 
        int A = get(Q[i].first), B = get(Q[i].second);
 
        int mxd = (R[A] == -1) ? R[A] : H[R[A]];
        int mnc = (L[B] == (int)1e9 + 1) ? L[B] : H[L[B]];
        int len = J[i];
 
 
        //err("J[%d] = %d, ", i, J[i]);
 
        ans = max(ans, len);
        ans = max(ans, mxd - Q[i].first);
        ans = max(ans, Q[i].second - mnc);
        ans = min(ans, Q[i].second - Q[i].first);
 
        printf("%d\n", ans);
    }
 
    return 0;
}