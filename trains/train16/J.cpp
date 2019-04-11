#include <bits/stdc++.h>
#define ll long long

using namespace std;

const ll LINF = (ll)1e18 + 7;

int a[100007];

struct st{
    ll aa, ab, ba, bb, sz;
};

void add(ll &a, ll b, ll c){
    if (b != -LINF && c != -LINF) a = max(a, b + c);
}

struct tree{
    st t[4 * 100007];

    st merge(st x, st y){
        st ans;
        ans.sz = x.sz + y.sz;
        ans.aa = -LINF;
        ans.ab = -LINF;
        ans.ba = -LINF;
        ans.bb = -LINF;

        add(ans.aa, x.aa, y.aa);
        add(ans.aa, x.ab, y.ba);

        add(ans.ab, x.aa, y.ab);
        add(ans.ab, x.ab, y.bb);

        add(ans.ba, x.ba, y.aa);
        add(ans.ba, x.bb, y.ba);

        add(ans.bb, x.ba, y.ab);
        add(ans.bb, x.bb, y.bb);

        if (x.sz % 2 == 0){
            add(ans.aa, 0, y.aa);
            add(ans.ab, 0, y.ab);
            add(ans.ba, 0, y.ba);
            add(ans.bb, 0, y.bb);
        } else {
            add(ans.ba, 0, y.aa);
            add(ans.bb, 0, y.ab);
            add(ans.aa, 0, y.ba);
            add(ans.ab, 0, y.bb);
        }

        if (y.sz % 2 == 0){
            add(ans.aa, x.aa, 0);
            add(ans.ab, x.ab, 0);
            add(ans.ba, x.ba, 0);
            add(ans.bb, x.bb, 0);
        } else {
            add(ans.ab, x.aa, 0);
            add(ans.aa, x.ab, 0);
            add(ans.bb, x.ba, 0);
            add(ans.ba, x.bb, 0);
        }

        return ans;
    }

    void build(int v, int vl, int vr){
        if (vl == vr){
            t[v].sz = 1;
            t[v].aa = a[vl];
            t[v].ab = -LINF;
            t[v].ba = -LINF;
            t[v].bb = -LINF;
        } else {
            int vm = (vl + vr) >> 1;
            build(v * 2 + 1, vl, vm);
            build(v * 2 + 2, vm + 1, vr);
            t[v] = merge(t[v * 2 + 1], t[v * 2 + 2]);
            //cout << "===" << v << ' ' << vl << ' ' << vr << endl;
            //cout << t[v].aa << ' ' << t[v].ab << ' ' << t[v].ba << ' ' << t[v].bb << endl;
        }
    }

    void up(int v, int vl, int vr, int pos, int val){
        if (vl == vr){
            t[v].sz = 1;
            t[v].aa = val;
            t[v].ab = -LINF;
            t[v].ba = -LINF;
            t[v].bb = -LINF;
        } else {
            int vm = (vl + vr) >> 1;
            if (pos <= vm){
                up(v * 2 + 1, vl, vm, pos, val);
            } else {
                up(v * 2 + 2, vm + 1, vr, pos, val);
            }
            t[v] = merge(t[v * 2 + 1], t[v * 2 + 2]);
        }
    }

    st get(int v, int vl, int vr, int l, int r){
        if (r < vl || l > vr){
            st ans;
            ans.sz = 0;
            ans.aa = -LINF;
            ans.ab = -LINF;
            ans.ba = -LINF;
            ans.bb = -LINF;
            return ans;
        }
        if (vl >= l && vr <= r){
            return t[v];
        } else {
            int vm = (vl + vr) >> 1;
            return merge(get(v * 2 + 1, vl, vm, l, r), get(v * 2 + 2, vm + 1, vr, l, r));
        }
    }
};

tree t;
int n, m;

int main(){
    //freopen("01", "r", stdin);
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++) scanf("%d", &a[i]);
    t.build(0, 0, n - 1);

    while(m--){
        int type, x, y;
        scanf("%d %d %d", &type, &x, &y);
        if (type== 1){
            t.up(0, 0, n - 1, x - 1, y);
        } else {
            auto now = t.get(0, 0, n - 1, x - 1, y - 1);
            printf("%lld\n", max(now.aa, max(now.ab, max(now.ba, now.bb))));
        }
    }
}
