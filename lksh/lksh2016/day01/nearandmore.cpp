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

#define TASK "nearandmore"

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

const int dd = 2e5 + 7;

int T[4 * dd];

int get(int v, int tl, int tr, int pos, int x) {

    if (tl == tr) {
        return (T[v] >= x ? tl : -1);
    }

    int tm = (tl + tr) / 2;

    int t1 = -1;
    if (pos <= tm && T[v * 2] >= x)
        t1 = get(v * 2, tl, tm, pos, x);

    if (t1 != -1)
        return t1;

    int t2 = -1;
    if (T[v * 2 + 1] >= x)
        t2 = get(v * 2 + 1, tm + 1, tr, pos, x);

    return t2;
}

void upd(int v, int tl, int tr, int pos, int x) {
    if (tl == tr) {
        T[v] = x;
    } else {
        int tm = (tl + tr) / 2;
        if (pos <= tm)
            upd(v * 2, tl, tm, pos, x);
        else
            upd(v * 2 + 1, tm + 1, tr, pos, x);

        T[v] = max(T[v * 2], T[v * 2 + 1]);
    }
}

int solve() {
    int n, m;
    scanf("%d %d", &n, &m);

    forn(i, n) {
        int t;
        scanf("%d", &t);

        upd(1, 0, n - 1, i, t);
    }

    while (m--) {
        int tp, i, x;
        scanf("%d %d %d", &tp, &i, &x);

        i--;

        if (tp == 0) {
            upd(1, 0, n - 1, i, x);
        } else {
            int r = get(1, 0, n - 1, i, x);

            if (r != -1)
                printf("%d\n", r + 1);
            else {
                printf("%d\n", -1);
            }
        }
    }

	return 0;
}