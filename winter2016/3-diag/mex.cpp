#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__)
 
using namespace std;
 
typedef long long ll;
 
const int dd = (int)1e6 + 7;
int A[dd], B[dd];
vector<int> E[dd];
 
struct SegmentTree {
    ll T[4 * dd];
    int P[4 * dd];
 
    SegmentTree() {
        fill(P, P + 4 * dd, -1);
        fill(T, T + 4 * dd, 0);
    }
 
    void build(int v, int tl, int tr) {
        if (tl == tr) {
            T[v] = (int)1e9;
        } else {
            int tm = (tl + tr) / 2;
            build(v * 2, tl, tm);
            build(v * 2 + 1, tm + 1, tr);
            T[v] = T[v * 2] + T[v * 2 + 1];
        }
    }
 
    void push(int v, int tl, int tr) {
        if (P[v] != -1) {
            T[v] = 1ll * (tr - tl + 1) * P[v];
 
            P[v * 2] = P[v];
            P[v * 2 + 1] = P[v];
 
            P[v] = -1;
        }
    }
 
    void upd(int v, int tl, int tr, int l, int r, int val) {
        push(v, tl, tr);
        if (l == tl && r == tr) {
            P[v] = val;
        } else {
            int tm = (tl + tr) / 2;
            if (r <= tm)
                upd(v * 2, tl, tm, l, r, val);
            else if (l > tm)
                upd(v * 2 + 1, tm + 1, tr, l, r, val);
            else {
                upd(v * 2, tl, tm, l, tm, val);
                upd(v * 2 + 1, tm + 1, tr, tm + 1, r, val);
            }
 
            push(v * 2, tl, tm);
            push(v * 2 + 1, tm + 1, tr);
 
            T[v] = T[v * 2] + T[v * 2 + 1];
        }
    }
 
    int get(int v, int tl, int tr, int pos) {
        push(v, tl, tr);
        if (tl == tr)
            return T[v];
        int tm = (tl + tr) / 2;
        if (pos <= tm)
            return get(v * 2, tl, tm, pos);
        else
            return get(v * 2 + 1, tm + 1, tr, pos);
    }
} T;
 
int n;
 
void upd(int a, int b, int val) {
 
    if (a > b)
        return;
 
    if (T.get(1, 0, n - 1, b) < val)
        return;
 
 
    int l = a - 1, r = b;
 
    while (r - l > 1) {
        int m = (l + r) / 2;
        if (T.get(1, 0, n - 1, m) < val)
            l = m;
        else
            r = m;
    }
    T.upd(1, 0, n - 1, r, b, val);
}
 
ll get() {
    T.push(1, 0, n - 1);
    return T.T[1];
}
 
int main() {
    scanf("%d", &n);
 
    for (int i = 0; i < n; i++) {
        scanf("%d", &A[i]);
        if (A[i] < n)
            E[A[i]].push_back(i);
    }
 
    T.build(1, 0, n - 1);
 
    for (int i = 0; i <= n; i++) {
        int nxt;
        if (E[i].empty())
            nxt = n;
        else
            nxt = E[i][0];
        upd(0, nxt - 1, i);
    }
 
    ll ans = 0;
    for (int i = 0; i < n; i++) {
        ans += get();
 
        /*err("B: ");
        for (int j = 0; j < n; j++) {
            err("%d, ", B[j]);
        }
        err("\n\n");
*/
        if (A[i] < n) {
            int nxt = -1;
            int ind = lower_bound(E[A[i]].begin(), E[A[i]].end(), i) - E[A[i]].begin();
            if (ind + 1 == (int)E[A[i]].size())
                nxt = n;
            else
                nxt = E[A[i]][ind + 1];
 
            upd(i + 1, nxt - 1, A[i]);
        }
        upd(i, i, 0);
    }
    printf("%lld\n", ans);
    return 0;
}