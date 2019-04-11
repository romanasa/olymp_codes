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
#include <cstring>
#include <sstream>
#include <numeric>

using namespace std;

typedef unsigned long long ull;
typedef long long ll;
typedef long double ld;

#define forn(i, n) for (int i = 0; i < (int)n; i++)
#define fornn(i, q, n) for (ll i = q; i < (ll)n; i++)
#define mp make_pair
#define pk push_back
#define all(v) v.begin(), v.end()
#define times clock() * 1.0 / CLOCKS_PER_SEC

#define TASK "substrcmp"

const double eps = 1e-7;
const double pi = acos(-1.0);

const ll INF = (ll)2e9 + 1;
const ll LINF = (ll)8e18;
const ll inf = (ll)2e9 + 1;
const ll linf = (ll)8e18;
const ll MM = (ll)1e9 + 7;

int solve();
void gen();

int main()
{
#ifdef HOME
    freopen("input.txt", "r", stdin), freopen("output.txt", "w", stdout);
#else
    freopen(TASK".in", "r", stdin), freopen(TASK".out", "w", stdout);
    //freopen("input.txt", "r", stdin), freopen("output.txt", "w", stdout), freopen("test.txt", "w", stderr);
#endif
    solve();
    return 0;
}

const int dd = 1e6 + 7;


struct myHash {
    vector<int> H, P;
    const int p = 31;
    ll mod = 1e9 + 11;

    myHash() {}
    myHash(string s, int x) {
        mod = x;

        H.resize(s.size() + 1);
        P.resize(s.size() + 1);

        ll h = 0;
        forn(i, s.size()) {
            H[i + 1] = h = (1ll * h * p + s[i] - 'a' + 1) % mod;
        }

        P[0] = 1;
        forn(i, s.size())
            P[i + 1] = 1ll * P[i] * p % mod;
    }

    int get(int l, int r) {
        return (H[r + 1] + mod - 1ll * H[l] * P[r - l + 1] % mod) % mod;
    }
};

int solve() {
    string s;
    cin >> s;

    myHash h1(s, 1e9 + 11);
    myHash h2(s, 1e9 + 7);

    int q;
    scanf("%d", &q);

    while (q--) {
        int a, b, c, d;
        scanf("%d %d %d %d", &a, &b, &c, &d);
        a--, b--, c--, d--;

        if (h1.get(a, b) == h1.get(c, d) && h2.get(a, b) == h2.get(c, d))
            puts("Yes");
        else
            puts("No");
    }

    return 0;
}