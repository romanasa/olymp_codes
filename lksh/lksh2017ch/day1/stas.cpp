#include <bits/stdc++.h>
 
using std::istream; using std::ostream; using std::fixed; using std::greater;
using std::tuple; using std::tie; using std::make_pair; using std::multiset;
using std::nth_element; using std::min_element; using std::max_element;
using std::vector; using std::set; using std::map; using std::string;
using std::fill; using std::copy; using std::sort; using std::unique;
using std::unordered_set; using std::unordered_map; using std::pair;
using std::next_permutation; using std::reverse; using std::rotate;
using std::cin; using std::cout; using std::cerr; using std::endl;
using std::lower_bound; using std::upper_bound; using std::deque;
using std::min; using std::max; using std::swap; using std::abs;
using std::priority_queue; using std::queue; using std::bitset;
using std::make_tuple; using std::iota; using std::shuffle;
 
typedef long long ll;
typedef long double ld;
typedef unsigned int uint;
typedef unsigned long long ull;
 
int const INF = 100 + (int) 1e9;
ll const INFL = 100 + (ll) 1e18;
ld const PI = 3.1415926535897932384626433832795028L;
std::mt19937 mt19937(960172);
 
ll rnd(ll x, ll y) { static auto gen = std::bind(std::uniform_int_distribution<ll>(), mt19937); return gen() % (y - x + 1) + x; }
ll gcd(ll a, ll b) { while (b > 0) { ll t = a % b; a = b; b = t; } return a; }
ll sqr(int a) { return (ll) a * a; } ld sqr(ld a) { return a * a; } ll sqr(ll a) { return a * a; }
 
int const N = 10100;
 
struct node {
    ll sum, pref, suf;
    int ppos, spos;
};
 
node const NONE = {0, -INFL, -INFL, INF, INF};
 
node operator+(node const& a, node const& b) {
    if (a.ppos == NONE.ppos) {
        return b;
    }
    if (b.ppos == NONE.ppos) {
        return a;
    }
    node ret;
    ret.sum = a.sum + b.sum;
    if (a.pref > a.sum + b.pref) {
        ret.pref = a.pref;
        ret.ppos = a.ppos;
    } else {
        ret.pref = a.sum + b.pref;
        ret.ppos = b.ppos;
    }
    if (b.suf > b.sum + a.suf) {
        ret.suf = b.suf;
        ret.spos = b.spos;
    } else {
        ret.suf = b.sum + a.suf;
        ret.spos = a.spos;
    }
    return ret;
}
 
node tree[N];
 
void build(int v, int l, int r) {
    tree[v] = {0, 0, 0, l, r - 1};
    if (r - l > 1) {
        int m = (l + r) / 2;
        build(2 * v + 1, l, m);
        build(2 * v + 2, m, r);
    }
}
 
void modify(int v, int l, int r, int pos, int val) {
    if (r - l == 1) {
        tree[v].sum += val;
        if (tree[v].sum > 0) {
            tree[v].pref = tree[v].suf = tree[v].sum;
            tree[v].ppos = l;
            tree[v].spos = l;
        } else {
            tree[v].pref = tree[v].suf = 0;
            tree[v].ppos = l - 1;
            tree[v].spos = l + 1;
        }
    } else {
        int m = (l + r) / 2;
        if (pos < m) {
            modify(2 * v + 1, l, m, pos, val);
        } else {
            modify(2 * v + 2, m, r, pos, val);
        }
        tree[v] = tree[2 * v + 1] + tree[2 * v + 2];
    }
}
 
node get_node(int v, int l, int r, int from, int to) {
    if (r <= from || to <= l) {
        return NONE;
    }
    if (from <= l && r <= to) {
        return tree[v];
    }
    int m = (l + r) / 2;
    return get_node(2 * v + 1, l, m, from, to) +
            get_node(2 * v + 2, m, r, from, to);
}
 
void solve() {
     
    int n;
    scanf("%d", &n);
     
    static int a[N], b[N], s[N];
    static int alla[N], allb[N];
     
    for (int i = 0; i < n; ++i) {
        scanf("%d%d%d", a + i, b + i, s + i);
        alla[i] = a[i];
        allb[i] = b[i];
    }
     
    sort(alla, alla + n);
    sort(allb, allb + n);
    int sza = unique(alla, alla + n) - alla;
    int szb = unique(allb, allb + n) - allb;
     
    static vector<int> wa[N], wb[N];
     
    for (int i = 0; i < n; ++i) {
        a[i] = lower_bound(alla, alla + sza, a[i]) - alla;
        b[i] = lower_bound(allb, allb + szb, b[i]) - allb;
        wa[a[i]].push_back(i);
        wb[b[i]].push_back(i);
        //cerr << "i = " << i << ", a[i] = " << a[i] << ", b[i] = " << b[i] << endl;
    }
     
    int LA = -1, RA = -1;
    int LB = -1, RB = -1;
    ll ans = -INFL;
         
    for (int la = 0; la < sza; ++la) {
        build(0, 0, szb);
        for (int ra = la; ra < sza; ++ra) {
            for (int i : wa[ra]) {
                modify(0, 0, szb, b[i], s[i]);
            }
            for (int i : wa[la]) {
                for (int j : wa[ra]) {
                    if (i == j) continue;
                     
                    int L = min(b[i], b[j]);
                    int R = max(b[i], b[j]) + 1;
                     
                    ll now = get_node(0, 0, szb, L, R).sum;
                    int l = L;
                    int r = R - 1;
                     
                    if (L > 0) {
                        auto x = get_node(0, 0, szb, 0, L);
                        now += x.suf;
                        l = x.spos;
                    }
                     
                    if (R < szb) {
                        auto x = get_node(0, 0, szb, R, szb);
                        now += x.pref;
                        r = x.ppos;
                    }
                     
                    if (now > ans) {
                        ans = now;
                        LA = la;
                        RA = ra;
                        LB = l;
                        RB = r;
                     
                        //cerr << la << ' ' << ra << endl;
                        //cerr << l << ' ' << r << endl;
                        //cerr << "L R: " << L << ' ' << R << endl;
                        //cerr << "ind: " << i << ' ' << j << endl;
                    }
                }
            }
        }
    }
     
    cout << alla[LA] << ' ' << alla[RA] << endl;
    cout << allb[LB] << ' ' << allb[RB] << endl;
     
    cerr << "ans = " << ans << endl;
}
 
 
 
int main() {
 
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
 
    cout.precision(15);
    cout << fixed;
    cerr.precision(6);
    cerr << fixed;
     
    solve();
     
#ifdef LOCAL
    cerr << "time: " << (ll) clock() * 1000 / CLOCKS_PER_SEC << " ms" << endl;
#endif
}