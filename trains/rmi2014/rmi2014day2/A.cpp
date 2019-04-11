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
 
#define TASK "minxor"
 
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
 
const int dd = 1e4 + 7;
 
 
int solve() {
    int q;
    scanf("%d", &q);
 
    multiset<ll> S, T;
 
    while (q--) {
        int tp;
        scanf("%d", &tp);
 
        if (tp == 1) {
            int x;
            scanf("%d", &x);
 
            int prev = -1, nxt = -1;
 
            auto it = S.lower_bound(x);
 
            if (it != S.begin()) {
                it--;
                prev = *it;
            }
 
            it = S.upper_bound(x);
            if (it != S.end())
                nxt = *it;
 
            if (prev != -1)
                T.insert(prev ^ x);
            if (nxt != -1)
                T.insert(x ^ nxt);
 
            if (prev != -1 && nxt != -1)
                T.erase(T.find(prev ^ nxt));
 
            S.insert(x);
        }
 
        if (tp == 2) {
            int x;
            scanf("%d", &x);
 
            S.erase(x);
 
            int prev = -1, nxt = -1;
 
            auto it = S.lower_bound(x);
 
            if (it != S.begin()) {
                it--;
                prev = *it;
            }
 
            it = S.upper_bound(x);
            if (it != S.end())
                nxt = *it;
 
            if (prev != -1)
                T.erase(T.find(prev ^ x));
            if (nxt != -1)
                T.erase(T.find(x ^ nxt));
 
            if (prev != -1 && nxt != -1)
                T.insert(prev ^ nxt);
        }
 
        if (tp == 3) {
            printf("%lld\n", *T.begin());
        }
    }
 
 
    return 0;
}