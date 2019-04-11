#include <bits/stdc++.h>
 
#define ll long long
#define err(...) //fprintf(stderr, __VA_ARGS__), fflush(stderr)
 
using namespace std;
 
const int dd = (int)2e5 + 1;
 
struct SegmentTree {
    int mn[4 * dd];
    void clear() { fill(mn, mn + 4 * dd, (int)1e9); }
    void upd(int v, int tl, int tr, int pos, int val) {
        if (tl == tr) mn[v] = val;
        else {
            int tm = (tl + tr) / 2;
            if (pos <= tm) upd(v * 2, tl, tm, pos, val);
            else upd(v * 2 + 1, tm + 1, tr, pos, val);
            mn[v] = min(mn[v * 2], mn[v * 2 + 1]);
        }
    }
    int getmin(int v, int tl, int tr, int l, int r) {
        if (tl == l && tr == r) return mn[v];
        int tm = (tl + tr) / 2;
        if (r <= tm) return getmin(v * 2, tl, tm, l, r);
        if (l > tm) return getmin(v * 2 + 1, tm + 1, tr, l, r);
        return min(getmin(v * 2, tl, tm, l, tm), getmin(v * 2 + 1, tm + 1, tr, tm + 1, r));
    }
} T;
 
char s[dd];
int n, L[dd], R[dd];
int A[dd], lcp[dd];
 
#define TASK "carpet"
 
inline int check(int x) {
    return x >= n ? x - n : x;
}
 
void build() {
     
    vector<int> col(n);
    vector<pair<int, int> > S;
    vector<pair<pair<int, int>, int> > J;
     
    for (int i = 0; i < n; i++) S.push_back({ s[i], i });
    sort(S.begin(), S.end());
     
    int c = 0;
    for (int i = 0; i < n; i++) {
        if (i && S[i - 1].first != S[i].first) c++;
        col[S[i].second] = c;
    }
     
    for (int L = 1; L <= n; L *= 2) {
        J.clear();
        for (int i = 0; i < n; i++) {
            J.push_back({ { col[i], col[check(i + L)] }, i });
        }   
        sort(J.begin(), J.end());
        int c = 0;
        for (int i = 0; i < n; i++) {
            if (i && (J[i - 1].first.first != J[i].first.first || J[i - 1].first.second != J[i].first.second)) c++;
            col[J[i].second] = c;
        }
    }
    for (int i = 0; i < n; i++) {
        A[col[i]] = i;
    }
     
    int z = 0;
     
    for (int i = 0; i < n; i++) {
        int j = col[i];
        if (j + 1 == n) continue;
        int t = A[j + 1];
        while (t + z < n && i + z < n && s[t + z] == s[i + z]) z++;
        lcp[j] = z;
        if (z > 0) z--;
    }
     
    //err("A = {"); for (int i = 0; i < n; i++) err(" %d,", A[i]); err(" }\n");
    //err("lcp = {"); for (int i = 0; i < n; i++) err(" %d,", lcp[i]); err(" }\n");
}
 
int st[dd];
int sz, tmp;
 
void add(int lcp, int pos) {
    err("add lcp = %d, pos = %d\n", lcp, pos);
     
    while (sz && st[sz - 1] >= lcp) {
        pos = min(pos, T.getmin(1, 0, n, sz - 1, sz - 1));
        sz--;
    }
    st[sz++] = lcp;
    T.upd(1, 0, n, sz - 1, pos);
     
    err("st = {"); for (int i = 0; i < sz; i++) err(" (lcp = %d, pos = %d),", st[i], T.getmin(1, 0, n, i, i)); err(" }\n");
}
 
int get(int pos) {
    if (sz == 1) return 0;
     
    if (st[0] + (tmp = T.getmin(1, 0, n, 0, sz - 1)) > pos) {
        return pos - tmp;
    }
    int l = 0, r = sz;
    while (r - l > 1) {
        int m = (l + r) / 2;
        if (st[m] + (tmp = T.getmin(1, 0, n, m, sz - 1)) <= pos)
            l = m;
        else
            r = m;
    }
    int mx = st[l];
    if (l + 1 <= sz - 1)
        mx = max(mx, pos - T.getmin(1, 0, n, l + 1, sz - 1));
    err("l = %d\n", l);
    return mx;
}
 
void calc(int *cur) {
    s[n++] = '0';
    build();
 
    T.clear();  
    sz = 0;
    for (int i = n - 1; i > 0; i--) {
        //err("i = %d\n", i);
        add((int)1e9, A[i]);
        err("get(%d) = %d\n", A[i], get(A[i]));
        cur[A[i]] = max(cur[A[i]], get(A[i]));
        sz--;
        add(lcp[i - 1], A[i]);
    }
     
    T.clear();
    sz = 0;
    err("\n\nreverse\n\n");
    for (int i = 1; i < n; i++) {
        add((int)1e9, A[i]);
        err("get(%d) = %d\n", A[i], get(A[i]));
        cur[A[i]] = max(cur[A[i]], get(A[i]));
        sz--;
        add(lcp[i], A[i]);
    }
    n--;
}
 
struct FenTree {
    int T[dd];
    void upd(int pos, int val) {
        for (int i = pos + 5; i < dd; i += (i&-i)) T[i] += val;
    }
    int get(int pos) {
        int res = 0;
        for (int i = pos + 5; i; i -= (i&-i)) res += T[i];
        return res;
    }
} F;
 
int main() {
#ifndef HOME
    freopen(TASK".in", "r", stdin), freopen(TASK".out", "w", stdout);
#endif
    scanf("%s", s);
    n = strlen(s);
     
    calc(L);
    reverse(s, s + n);
    calc(R);
    reverse(R, R + n);
     
    for (int i = 0; i < n; i++) {
        err("L[%d] = %d, R[%d] = %d\n", i, L[i], i, R[i]);
    }
     
    ll ans = 0;
    for (int l = n - 1; l >= 0; l--) {
        if (L[l] && l + 1 < n) ans += F.get(L[l] + l);
        if (R[l]) F.upd(max(l - R[l] + 1, -2), 1);
    }
     
    printf("%I64d\n", ans);
    return 0;
}