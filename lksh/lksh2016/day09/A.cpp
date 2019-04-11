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

#define TASK "rollback"

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
    //freopen(TASK".in", "r", stdin), freopen(TASK".out", "w", stdout);
    //freopen("input.txt", "r", stdin), freopen("output.txt", "w", stdout), freopen("test.txt", "w", stderr);
#endif
    solve();
    return 0;
}

const int dd = 1e5 + 7;

int T[1 << 13];
int x[1 << 13];

vector<int> G;

int solve() {
    int n, m;
    cin >> n >> m;

    G.resize(m);

    bool ok = true;

    forn(i, m) {
        int cmsk = 0;
        cin >> x[i];

        forn(j, x[i]) {
            int t;
            cin >> t;
            cmsk += 1 << (t - 1);
        }
        G[i] = cmsk;
        T[cmsk]++;
    }

    if (!T[0])
        ok = false;

    forn(i, m) {
        for (int msk = G[i]; msk; msk = (msk - 1) & G[i])
            if (!T[msk])
                ok = false;
    }

    forn(i, m) {
        forn(j, m) {
            if (x[i] < x[j]) {
                bool t = false;

                forn(k, n) {
                    if (!(G[i] & (1 << k)) && (G[j] & (1 << k)) && T[G[i] + (1 << k)])
                        t = true;
                }

                if (!t)
                    ok = false;
            }
        }
    }
    if (ok)
        puts("YES");
    else
        puts("NO");

    return 0;
}