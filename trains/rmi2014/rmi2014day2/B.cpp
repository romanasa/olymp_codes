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
 
using namespace std;
 
typedef unsigned long long ull;
typedef long long ll;
typedef double ld;
 
#define forn(i, n) for (int i = 0; i < (int)n; i++)
#define fornn(i, q, n) for (int i = q; i < (ll)n; i++)
#define mp make_pair
#define pk push_back
#define all(v) v.begin(), v.end()
#define times clock() * 1.0 / CLOCKS_PER_SEC
 
#define TASK "parking"
 
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
int dp1[dd], dp2[dd];
 
int solve() {
    int m, n;
 
    cin >> m >> n;
 
    vector<int> T(n);
 
    forn(i, n) {
        cin >> T[i];
    }
 
    sort(all(T));
 
    forn(i, m)
        dp1[i] = dp2[i] = inf;
 
    dp1[0] = 0;
 
 
    forn(i, n) {
        int cur = inf;
        forn(j, m + 1) {
            dp2[j] = min(dp2[j], cur + abs(T[i] - j));
            cur = min(cur, dp1[j]);
        }
        forn(j, m + 1)
            dp1[j] = dp2[j], dp2[j] = inf;
    }
 
    cout << *min_element(dp1, dp1 + m + 1);
 
    return 0;
}