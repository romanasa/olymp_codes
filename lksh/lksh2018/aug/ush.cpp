#include <bits/stdc++.h>

using namespace std;

#define int long long

const int MAXN = 150001;
const int INF = 1e18 + 7;

int n, q;
int a[MAXN], v[MAXN];
int coord[MAXN];
int val[MAXN];
map <int, int> d;

void read() {
    for (int i = 0; i < MAXN; ++i) {
        val[i] = INF;
    }

    cin >> n >> q;
    for (int i = 0; i < n; ++i) cin >> a[i];

    for (int i = 0; i < n; ++i) {
        d[a[i]]++;
    }

    int it = 1;
    for (auto &el : d) {
        el.second = it;
        val[it] = el.first;
        ++it;
    }

    for (int i = 0; i < n; ++i) {
        coord[i] = d[a[i]];
    }
}

struct Node {
    int cnt, sum;
    Node *l, *r;
    Node() {
        cnt = sum = 0;
        l = r = NULL;
    }
};

Node *tree[MAXN];

Node *build(int tl, int tr) {
    Node *t = new Node();
    if (tl == tr) return t;
    int tm = (tl + tr) / 2;
    t->l = build(tl, tm);
    t->r = build(tm + 1, tr);
    return t;
}

void relax(Node *t) {
    t->cnt = t->l->cnt + t->r->cnt;
    t->sum = t->l->sum + t->r->sum;
}

Node *add(Node *t, int tl, int tr, int p) {
    Node *nt = new Node();

    if (tl == tr) {
        nt->cnt = t->cnt + 1;
        nt->sum = t->sum + val[p];
        return nt;
    }

    int tm = (tl + tr) / 2;
    if (p <= tm) {
        nt->l = add(t->l, tl, tm, p);
        nt->r = t->r;
    }
    else {
        nt->l = t->l;
        nt->r = add(t->r, tm + 1, tr, p);
    }

    relax(nt);
    return nt;
}

void build_do() {
    tree[0] = build(0, MAXN);
    for (int i = 0; i < n; ++i) {
        tree[i + 1] = add(tree[i], 0, MAXN, coord[i]);
    }
}

int descent(Node *t1, Node *t2, int tl, int tr, int mn) {
    int cnt = t2->cnt - t1->cnt;
    if (!cnt) return -1;
    if (tr < mn) return -1;
    if (tl == tr) return tl;
    int tm = (tl + tr) / 2;
    int lres = descent(t1->l, t2->l, tl, tm, mn);
    if (lres != -1) return lres;
    else return descent(t1->r, t2->r, tm + 1, tr, mn);
}

int getsum(Node *t, int tl, int tr, int l, int r) {
    if (tr < l || r < tl) return 0;
    if (l <= tl && tr <= r) return t->sum;
    int tm = (tl + tr) / 2;
    return getsum(t->l, tl, tm, l, r) + getsum(t->r, tm + 1, tr, l, r);
}

int getmin(int x) {
    return upper_bound(val + 1, val + n + 1, x) - val;
}

int getx(int l, int r, int x) {
    int mn = getmin(x);
    int c = descent(tree[l], tree[r + 1], 0, MAXN, mn);
    if (c == -1) return -1;
    else return val[c];
}

int getmax(int x) {
    return upper_bound(val + 1, val + n + 1, x) - val - 1;
}

int getsum(int l, int r, int x) {
    int mx = getmax(x);
    return getsum(tree[r + 1], 0, MAXN, 0, mx) - getsum(tree[l], 0, MAXN, 0, mx);
}

int segsum(int l, int r) {
    return tree[r + 1]->sum - tree[l]->sum;
}

int get(int l, int r) {
    int curr = 0;

    while (1) {
        int x = getx(l, r, curr + 1);

        cout << "curr = " << curr << ", " << "x = " << x << endl;
        
        if (x == -1) {
            return segsum(l, r) + 1;
        }

        int sum = getsum(l, r, x - 1);

        if (sum + 1 < x) {
            return sum + 1;
        }
        else {
            curr += x;
        }
    }
}

void solve() {
    build_do();

    for (int i = 0; i < q; ++i) {
        int l, r;
        cin >> l >> r;
        --l; --r;
        cout << get(l, r) << '\n';
    }
}

signed main() {
    //freopen("test.txt", "r", stdin);

    ios_base::sync_with_stdio(0);
    cin.tie(0);

    read();
    solve();
}