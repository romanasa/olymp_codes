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
typedef long double ld;
 
#define forn(i, n) for (ll i = 0; i < (ll)n; i++)
#define fornn(i, q, n) for (ll i = q; i < (ll)n; i++)
#define mp make_pair
#define pk push_back
#define all(v) v.begin(), v.end()
#define times clock() * 1.0 / CLOCKS_PER_SEC
 
#define TASK "hypercube"
 
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
 
const int dd = 1e5 + 7;
 
const ll mod = 100003;
 
ll bp(ll a, ll n) {
    ll res = 1;
    ll cur = a;
    for (; n; n >>= 1) {
        if (n & 1) {
            res = res * cur % mod;
        }
        cur = cur * cur % mod;
    }
    return res;
}
 
ll fact[dd];
ll tcaf[dd];
 
ll C(ll n, ll k) {
    return fact[n] * tcaf[k] * tcaf[n - k] % mod;
}
 
int solve() {
    fact[0] = tcaf[0] = 1;
 
    int n, m, k;
    cin >> n >> m >> k;
 
    fornn(i, 1, n + 1) {
        fact[i] = fact[i - 1] * i % mod;
        tcaf[i] = bp(fact[i], mod - 2);
    }
 
    ll ans = 0;
    for (int i = k; i <= n; i++) {
        ll cur = fact[i] * tcaf[i - k] * C(n, i) % mod;
        ans = (ans + cur) % mod;
    }
 
    int a = 0;
    for (int i = 0; i < n; i++) {
        if (m & (1 << i)) {
            a = m - (1 << i);
            break;
        }
    }
    int b = 0;
    for (int i = 0; i < n; i++) {
        if (!(m & (1 << i))) {
            b = m + (1 << i);
            break;
        }
    }
 
    cout << a << "\n";
    cout << b << "\n";
    cout << ans;
    return 0;
}