#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)
 
typedef long long ll;
 
using namespace std;
 
const int dd = (int)1e5 + 1;
 
int a[dd], b[dd], Q[dd];
int suf1[dd], suf2[dd];
int pref[dd];
 
vector<vector<int> > E;
int n, l, q;
 
const int mod = (int)1e9 + 7;
 
void add(int &a, int b) {
    a += b;
    if (a >= mod) a -= mod;
}
 
void sub(int &a, int b) {
    a -= b;
    if (a < 0) a += mod;
}
 
int mul(int a, int b) {
    return 1ll * a * b % mod;
}
 
int ans = 0;
int O;
int num = 1;
 
vector<int> dfs(int v) {
    vector<int> cur;
 
    for (int to : E[v]) {
        auto t = dfs(to);
 
        if (t.size() > cur.size()) swap(t, cur);
 
        for (int i = 0; i < (int)t.size(); i++)
            add(cur[i], t[i]);
    }
    //err("v = %d, cur = {", v); for (int x : cur) err(" %d,", x); err(" }\n");
 
    suf1[v] = (l == a[v] ? 1 : (l - a[v] - 1 >= 0 && l - a[v] - 1 < (int)cur.size() ? cur[l - a[v] - 1] : 0));
    suf2[v] = (l == b[v] ? 1 : (l - b[v] - 1 >= 0 && l - b[v] - 1 < (int)cur.size() ? cur[l - b[v] - 1] : 0));
 
    //err("suf2 = %d\n", suf2[v]);
 
    if ((int)cur.size() >= l - a[v]) {
 
        if ((int)cur.size() == l - a[v]) cur.push_back(0);
 
        int q = (l == a[v] ? 1 : cur[l - a[v] - 1]);
 
        add(cur[l - a[v]], q);
 
    }
 
 
 
    return cur;
}
 
void upd(int v) {
 
    //err("change v = %d, a[v] = %d, b[v] = %d\n", v, a[v], b[v]);
 
    //err("sub %d * %d = %d\n",pref[a[v] - 1], suf1[v],  mul(pref[a[v] - 1], suf1[v]));
    //err("add %d * %d = %d\n",pref[b[v] - 1], suf2[v],  mul(pref[b[v] - 1], suf2[v]));
 
    int ch = 0;
 
    sub(ch, mul(pref[a[v] - 1], suf1[v]));
    add(ch, mul(pref[b[v] - 1], suf2[v]));
 
    Q[v] = ch;
 
    for (int to : E[v]) {
 
        add(pref[b[v]], pref[b[v] - 1]);
 
        upd(to);
 
        sub(pref[b[v]], pref[b[v] - 1]);
    }
}
 
 
void precalc(int v) {
 
    add(pref[a[v]], pref[a[v] - 1]);
 
    //err("v = %d, pref = {", v); for (int i = 0; i <= l; i++) err(" %d,", pref[i]); err(" }\n");
 
    if (a[v] == l)
        add(ans, pref[a[v] - 1]);
 
    for (int to : E[v]) {
        precalc(to);
    }
 
    sub(pref[a[v]], pref[a[v] - 1]);
}
 
void calc() {
    fill(Q, Q + n, 0);
    //err("one\n");
    dfs(0);
    //err("two\n");
    upd(0);
    //err("three\n");
}
 
int main() {
    pref[0] = 1;
 
    scanf("%d %d %d", &n, &l, &q);
 
    E.resize(n);
 
    for (int i = 1; i < n; i++) {
        int p;
        scanf("%d", &p);
        E[p].push_back(i);
    }
 
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
        b[i] = a[i];
    }
 
    precalc(0);
 
    //err("ans = %d\n", ans);
 
    for (int i = 0; i < q; i++) {
        scanf("%d", &b[i % n]);
        if (i % n == n - 1 || i == q - 1) {
            calc();
 
            int c = i / n * n + 1;
 
            for (int j = 0; j < n; j++) {
 
                if (c + j > q) break;
 
                add(ans, Q[j]);
 
                //err("ans = %d\n", ans);
                add(O, mul(ans, c + j));
            }
 
            for (int j = 0; j < n; j++)
                a[j] = b[j];
        }
    }
    printf("%d\n", O);
    return 0;
}