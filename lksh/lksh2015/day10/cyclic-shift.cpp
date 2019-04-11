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

#define TASK "cyclic-shift"

const double eps = 1e-7;
const double pi = acos(-1.0);

const int INF = (int)2e9 + 1;
const ll LINF = (ll)9e18 + 7;
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

const ll p = 31;

ll hh[200007], pp[200007];

ll get(int l, int r) {
    if (l > r)
        return -1;
    if (!l)
        return hh[r];
    return (hh[r] + MM - (hh[l - 1] * pp[r - l + 1]) % MM) % MM;
}

int solve() {
    pp[0] = 1;
    fornn(i, 1, 200007)
        pp[i] = (pp[i - 1] * p) % MM;
    
    string s;
    cin >> s;
    int n = s.size();
    s = s + s;
    
    ll curh = 0;
    forn(i, s.size())
        hh[i] = curh = ((curh * p) % MM + s[i] - 'a' + 1) % MM;
    
    int ml = 0, mr = n - 1;
    
    for (int beg = 1; beg < n; beg++) {
        int l = 0, r = n;
        while (r - l > 1) {
            int m = (l + r) / 2;
            if (get(ml, ml + m - 1) == get(beg, beg + m - 1))
                l = m;
            else
                r = m;
        }

        if (l < n - 1)
            if (s[ml + l] > s[beg + l])
                ml = beg, mr = beg + n - 1;
    }
    fornn(i, ml, mr + 1)
        cout << s[i];
    return 0;
}