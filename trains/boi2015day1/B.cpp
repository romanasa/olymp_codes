#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

typedef long long ll;

using namespace std;

struct node {
    node *L, *R;
    int val;
    node() { L = R = NULL; val = 0; }
    node(int x) { L = R = NULL; val = x; }
    node(node *_L, node *_R) {
        L = _L, R = _R;
        val = max(L->val, R->val);
    }
};

node* build(int tl, int tr) {
    if (tl == tr) {
        return new node();
    } else {
        int tm = (tl + tr) / 2;
        return new node(build(tl, tm), build(tm + 1, tr));
    }
}

int get(node *v, int tl, int tr, int l, int r) {
    if (tl == l && tr == r) return v->val;
    int tm = (tl + tr) / 2;
    if (r <= tm) return get(v->L, tl, tm, l, r);
    if (l > tm) return get(v->R, tm + 1, tr, l, r);
    return max(get(v->L, tl, tm, l, tm), get(v->R, tm + 1, tr, tm + 1, r));
}

node* upd(node *v, int tl, int tr, int pos, int val) {
    if (tl == tr) return new node(val);
    int tm = (tl + tr) / 2;
    if (pos <= tm) return new node(upd(v->L, tl, tm, pos, val), v->R);
    return new node(v->L, upd(v->R, tm + 1, tr, pos, val));
}

int main() {
#ifdef WIN
    freopen("01", "r", stdin);
#endif
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;

    vector<int> val(n + 1);
    vector<node*> T;
    T.push_back(build(0, n));

    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        val[i] = x;

        if (x > 0) {
            T.push_back(T.back());
            T.back() = upd(T.back(), 0, n, 0, i);
        } else {
            int level = -x;
            //for (int j = 0; j < level; j++) ind = max(ind, T.back()[j]);
            int ind = get(T.back(), 0, n, 0, level - 1);
            T.push_back(T[ind - 1]);
            T.back() = upd(T.back(), 0, n, level, i);
        }
        cout << val[get(T.back(), 0, n, 0, 0)] << "\n";
    }
    return 0;
}
