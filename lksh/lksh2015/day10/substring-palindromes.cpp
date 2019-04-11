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
#include <unordered_set>

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

#define TASK "substring-palindromes"

const double eps = 1e-7;
const double pi = acos(-1.0);

const int inf = (int)2e9 + 1;
const ll linf = (ll)9e18 + 7;
const ll MM = (ll)1e9 + 7;

int solve();

int main() {
#ifdef _DEBUG
    freopen("input.txt", "r", stdin), freopen("output.txt", "w", stdout);
#else
    freopen(TASK".in", "r", stdin), freopen(TASK".out", "w", stdout);
    //freopen("input.txt", "r", stdin), freopen("output.txt", "w", stdout), freopen("test.txt", "w", stderr);
#endif
    solve();
    return 0;
}

const int MAXN = 2e5 + 7;
const int p = 31;
ll T[4 * MAXN], P[MAXN];
ll TR[4 * MAXN];

void update(int v, int tl, int tr, int pos, int val) {
    if (tl == pos && tr == pos)
        T[v] = val;
    else {
        int tm = (tl + tr) / 2;
        if (pos <= tm)
            update(v * 2, tl, tm, pos, val);
        else if (pos <= tr)
            update(v * 2 + 1, tm + 1, tr, pos, val);

        int siz = tr - tm;
        
        T[v] = ((T[v * 2] * P[siz]) % MM + T[v * 2 + 1]) % MM;
    }
}

ll get(int v, int tl, int tr, int l, int r) {
    if (l == tl && r == tr)
        return T[v];
    int tm = (tl + tr) / 2;
    if (r <= tm)
        return get(v * 2, tl, tm, l, r);
    if (l > tm)
        return get(v * 2 + 1, tm + 1, tr, l, r);

    ll h1 = get(v * 2, tl, tm, l, tm);
    ll h2 = get(v * 2 + 1, tm + 1, tr, tm + 1, r);

    return ((h1 * P[r - tm]) % MM + h2) % MM;
}

void updateR(int v, int tl, int tr, int pos, int val) {
    if (tl == pos && tr == pos)
        TR[v] = val;
    else {
        int tm = (tl + tr) / 2;
        if (pos <= tm)
            updateR(v * 2, tl, tm, pos, val);
        else if (pos <= tr)
            updateR(v * 2 + 1, tm + 1, tr, pos, val);

        int siz = tr - tm;

        TR[v] = ((TR[v * 2] * P[siz]) % MM + TR[v * 2 + 1]) % MM;
    }
}

ll getR(int v, int tl, int tr, int l, int r) {
    if (l == tl && r == tr)
        return TR[v];
    int tm = (tl + tr) / 2;
    if (r <= tm)
        return getR(v * 2, tl, tm, l, r);
    if (l > tm)
        return getR(v * 2 + 1, tm + 1, tr, l, r);

    ll h1 = getR(v * 2, tl, tm, l, tm);
    ll h2 = getR(v * 2 + 1, tm + 1, tr, tm + 1, r);

    return ((h1 * P[r - tm]) % MM + h2) % MM;
}

int solve() {
    P[0] = 1;
    fornn(i, 1, MAXN)
        P[i] = (P[i - 1] * p) % MM;

    string s;
    cin >> s;
    int n = s.size();
    string sR = string(s.rbegin(), s.rend());

    forn(i, n)
        update(1, 0, n - 1, i, s[i] - 'a' + 1);
    
    forn(i, n)
        updateR(1, 0, n - 1, i, sR[i] - 'a' + 1);

    int k;
    cin >> k;
    forn(i, k) {
        string s;
        cin >> s;
        if (s[0] == 'p') {
            int l, r;
            cin >> l >> r;
            l--, r--;
            ll h1 = get(1, 0, n - 1, l, r);
            ll h2 = getR(1, 0, n - 1, n - r - 1, n - l - 1);
            if (h1 == h2)
                cout << "Yes\n";
            else
                cout << "No\n";
        }
        else {
            int pos;
            char c;
            cin >> pos >> c;
            pos--;
            update(1, 0, n - 1, pos, c - 'a' + 1);
            updateR(1, 0, n - 1, n - pos - 1, c - 'a' + 1);
        }
    }
    return 0;
}