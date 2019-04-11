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
 
#define TASK "rooks"
 
const ld eps = 1e-9;
const double pi = acos(-1.0);
 
const int INF = (int)2e9 + 1;
const ll LINF = (ll)8e18;
const ll MM = (ll)1e9 + 7;
const int inf = (int)2e9 + 1;
const ll linf = (ll)8e18;
 
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
#ifdef HOME
    cout << "\n\n\nTime : " << times;
#endif
    return 0;
}
 
const int dd = 1500 + 7;
bool T[dd][dd];
 
int L[dd][dd], R[dd][dd];
pair<int, int> num[2 * dd][2 * dd];
 
vector<vector<int> > e;
 
int tmm = 1;
int used[5 * dd], pr[5 * dd], pr2[5 * dd];
 
int dfs(int v) {
    used[v] = tmm;
    for (int to : e[v]) {
        if (pr[to] == -1) {
            pr[to] = v;
            pr2[v] = to;
            return 1;
        }
    }
    for (int to : e[v]) {
        if (used[pr[to]] != tmm && dfs(pr[to])) {
            pr[to] = v;
            pr2[v] = to;
            return 1;
        }
    }
 
    return 0;
}
 
int solve() {
    int n, k;
    scanf("%d %d", &n, &k);
 
    forn(i, k) {
        int x, y;
        scanf("%d %d", &x, &y);
        x--, y--;
        T[x][y] = 1;
    }
 
    int curL = 0;
    forn(i, n) {
        forn(j, n) {
            if (T[i][j])
                curL++;
            else
                L[i][j] = curL;
        }
        curL++;
    }
 
 
    int curR = 0;
    forn(j, n) {
        forn(i, n) {
            if (T[i][j])
                curR++;
            else
                R[i][j] = curR;
        }
        curR++;
    }
 
    e.resize(curL);
 
    forn(i, n) {
        forn(j, n) {
            if (!T[i][j]) {
                e[L[i][j]].push_back(R[i][j] + curL);
                num[L[i][j]][R[i][j] + curL] = mp(i, j);
            }
        }
    }
 
    forn(i, curR + curL) {
        pr[i] = -1;
        pr2[i] = -1;
    }
 
    for (int run = 1; run;) {
        run = 0;
        tmm++;
 
        forn(i, curL) {
            if (pr2[i] == -1 && dfs(i))
                run = 1;
        }
    }
 
    int ans = 0;
    forn(i, curR) {
        if (pr[i + curL] != -1)
            ans++;
    }
 
    printf("%d\n", ans);
    forn(i, curR + curL) {
        if (pr[i] != -1) {
            printf("%d %d\n", num[pr[i]][i].first + 1, num[pr[i]][i].second + 1);
        }
    }
 
    return 0;
}