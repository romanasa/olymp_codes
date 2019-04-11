#pragma GCC optimize("O3", "unroll-loops")
#include <bits/stdc++.h>
#include <unordered_set>
#include <unordered_map>
#define pb push_back
#define pf push_front
#define popb pop_back
#define popf pop_front
#define all(a) (a).begin(), (a).end()
#define rall(a) (a).rbegin(), (a).rend()
#define sz(a) (ll)((a).size())
#define heap priority_queue
#define hash_map unordered_map
#define hash_set unordered_set
#define ft first
#define sd second
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define endl "\n"
#define mineq(a, b) (a) = min((a), (b))
#define maxeq(a, b) (a) = max((a), (b))
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
typedef pair<ll, ll> pll;
typedef pair<ld, ld> pld;
typedef vector<ll> vll;
typedef set<ll> sll;
typedef map<ll, ll> mll;
const ll inf = numeric_limits<ll>::max() / 2;
const ld eps = 1e-9;
const ld pi = acos(-1);

const ll MAXS = 1024;

ll n, k;
string s;
vll sa, temp, head, color, ncolor, rev, lcp;
ll cs;

void sort1() {
        head.assign(MAXS, 0);
        color.assign(n, 0);
        for (ll i = 0; i < n; i++) {
                ++head[s[i]];
        }
        for (ll i = 1; i < MAXS; i++) {
                head[i] += head[i - 1];
        }
        for (ll i = n - 1; i >= 0; i--) {
                --head[s[i]];
                sa[head[s[i]]] = i;
        }
        cs = 1;
        color[sa[0]] = 0;
        for (ll i = 1; i < n; i++) {
                if (s[sa[i]] != s[sa[i - 1]]) {
                        ++cs;
                }
                color[sa[i]] = cs - 1;
        }
}

void build() {
        sa.resize(n, 0);
        sort1();
        for (ll p = 1; p < n; p *= 2) {
                temp.assign(n, 0);
                head.assign(cs, 0);
                ncolor.assign(n, 0);
                for (ll i = 0; i < n; i++) {
                        temp[i] = (sa[i] - p + n) % n;
                }
                for (ll i = 0; i < n; i++) {
                        ++head[color[temp[i]]];
                }
                for (ll i = 1; i < cs; i++) {
                        head[i] += head[i - 1];
                }
                for (ll i = n - 1; i >= 0; i--) {
                        --head[color[temp[i]]];
                        sa[head[color[temp[i]]]] = temp[i];
                }
                cs = 1;
                ncolor[sa[0]] = 0;
                for (ll i = 1; i < n; i++) {
                        pll p1 = { color[sa[i]], color[(sa[i] + p) % n] };
                        pll p2 = { color[sa[i - 1]], color[(sa[i - 1] + p) % n] };
                        if (p1 != p2) {
                                ++cs;
                        }
                        ncolor[sa[i]] = cs - 1;
                }
                color = ncolor;
        }
}

void kasai() {
        lcp.assign(n, 0);
        rev.assign(n, 0);
        for (ll i = 0; i < n; i++) {
                rev[sa[i]] = i;
        }
        ll p = 0;
        for (ll i = 0; i < n; i++) {
                if (p > 0) {
                        --p;
                }
                if (rev[i] == n - 1) {
                        lcp[rev[i]] = 0;
                        p = 0;
                } else {
                        ll j = sa[rev[i] + 1];
                        while (max(i, j) + p < n && s[i + p] == s[j + p]) {
                                ++p;
                        }
                        lcp[rev[i]] = p;
                }
        }
}

void solve() {
        build();
        kasai();
        sa.erase(sa.begin());
        lcp.erase(lcp.begin());
        s.erase(s.end());
        --n;
        string ans = "";
        for (ll i = 0; i < n - 1; i++) {
                ll cur = n - sa[i];
                if (i >= 1) {
                        cur -= lcp[i - 1];
                }
                if (k > cur) {
                        k -= cur;
                } else {
                        ll d = 0;
                        if (i >= 1) {
                                d = lcp[i - 1];
                        }
                        ans = s.substr(sa[i], d + k);
                        cout << ans << endl;
                        break;
                }
        }
        if (ans == "") {
                cout << s.substr(sa.back()) << endl;
        }
}

void read() {
        cin >> s;
        s.pb(0);
        cin >> k;
        n = sz(s);
}

int main() {
        fast;
        read();
        solve();
        return 0;
}