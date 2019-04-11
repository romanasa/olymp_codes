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

const int dd = 2e6 + 7;

pair<int, int> w[dd];
int T[dd];

int solve() {
    int n, m;

    cin >> n >> m;

    forn(i, n) {
        cin >> w[i].first;
        w[i].second = i;
    }

    forn(i, m) {
        int t;
        cin >> t;   

        int cmsk = 0;
        vector<int> G(t);
        forn(i, t) {
            cin >> G[i];
            cmsk += 1 << (G[i] - 1);
        }
        T[cmsk]++;
    }

    sort(w, w + n);
    reverse(w, w + n);

    int cmsk = 0;
    int ans = 0;
    forn(i, n) {
        bool ok = true;

        for (int pmsk = cmsk; pmsk; pmsk = (pmsk - 1) & cmsk)
            if (T[pmsk + (1 << w[i].second)])
                ok = false;

        if (ok) {
            cmsk += 1 << w[i].second;
            ans += w[i].first;
        }
    }
    cout << ans;
    return 0;
}