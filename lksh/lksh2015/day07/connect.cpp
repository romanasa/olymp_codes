#define _CRT_SECURE_NO_WARNINGS
#pragma comment(linker, "/STACK:66777216")
#include <iostream>
#include <cstdio>
#include <cmath>
#include <vector>
#include <ctime>
#include <map>
#include <set>
#include <string>
#include <queue>
#include <deque>
#include <cassert>
#include <cstdlib>
#include <bitset>
#include <algorithm>
#include <string>
#include <list>
#include <fstream>

using namespace std;

typedef unsigned long long ull;
typedef long long ll;
typedef long double ld;

#define forn(i, n) for (ll i = 0; i < (ll)n; i++)
#define fornn(i, q, n) for (ll i = q; i < (ll)n; i++)
#define mp make_pair
#define pk push_back
#define all(v) v.begin(), v.end()
#define times clock() * 1.0 / CLOCKS_PER_SEC

#define TASK "connect"

const double eps = 1e-7;
const double pi = acos(-1.0);

const int INF = (int)2e9 + 1;
const ll LINF = (ll)9e18 + 7;
const ll MM = (ll)1e9 + 7;

int solve();

int main()
{
#ifdef _DEBUG
    freopen("input.txt", "r", stdin), freopen("output.txt", "w", stdout);
#else
    freopen(TASK".in", "r", stdin), freopen(TASK".out", "w", stdout);
    //freopen("input.txt", "r", stdin), freopen("output.txt", "w", stdout), freopen("test.txt", "w", stderr);
#endif
    solve();
    return 0;
}

struct cond {
    int a, b, cnt;
    cond() {}
    cond(int _a, int _b, int _cnt) : a(_a), b(_b), cnt(_cnt) {}
};

const int MAXN = 3e5 + 7;
int back[MAXN], forw[MAXN], tmm = 1, p[MAXN], cnt[MAXN], ans[MAXN];
string req[MAXN];
pair<int, int> num[MAXN];
map<pair<int, int>, int> m;

int get(int v) {
    return v == p[v] ? v : get(p[v]);
}

vector<cond> st;

void un(int a, int b) {
    a = get(a), b = get(b);
    if (a != b) {
        if (cnt[a] < cnt[b])
            swap(a, b);

        st.pk(cond(a, b, cnt[a]));
        p[b] = a, cnt[a] += cnt[b];
    }
}

void del() {
    cond cur = st.back();
    st.pop_back();
    int a = cur.a, b = cur.b, c = cur.cnt;
    p[b] = b, cnt[a] = c;
}

int n, k, comp;

void go(int l, int r) {
    if (l >= r)
        return;
    if (r - l == 1) {
        if (req[l] == "?")
            ans[l] = n - comp;
        return;
    }
    int m = (l + r) / 2, c = 0;

    for (int i = m; i < r; i++)
        if (req[i] == "-" && back[i] < l) {
            if (get(num[i].first) != get(num[i].second))
                un(num[i].first, num[i].second), comp++, c++;
        }

    go(l, m);

    forn(i, c)
        del(), comp--;
    
    c = 0;

    for (int i = l; i < m; i++)
        if (req[i] == "+" && forw[i] >= r) {
            if (get(num[i].first) != get(num[i].second))
                un(num[i].first, num[i].second), comp++, c++;
        }

    go(m, r);

    forn(i, c)
        del(), comp--;
}

int solve() {
    cin >> n >> k;
    forn(i, k)
        forw[i] = INF, back[i] = -1;
    forn(i, k) {
        cin >> req[i];
        if (req[i] == "+" || req[i] == "-") {
            cin >> num[i].first >> num[i].second;
            if (num[i].first > num[i].second)
                swap(num[i].first, num[i].second);
        }

        if (req[i] == "+")
            m[num[i]] = i;
        if (req[i] == "-") {
            int f = m[num[i]];
            back[i] = f;
            forw[f] = i;
        }
    }

    forn(i, n + 1)
        p[i] = i, cnt[i] = 1;
    
    go(0, k);
    
    forn(i, k)
        if (req[i] == "?")
            cout << ans[i] << "\n";
    return 0;
}