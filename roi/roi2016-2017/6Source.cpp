#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <vector>
#include <map>
#include <set>
#include <string>
#include <cstring>
#include <queue>
 
using namespace std;
typedef long long ll;
 
int solve();
#define TASK "servers"
 
int main() {
#ifdef ROII
    freopen("input.txt", "r", stdin), freopen("output.txt", "w", stdout);
#else
    freopen(TASK".in", "r", stdin), freopen(TASK".out", "w", stdout);
#endif
    solve();
}
 
 
const int dd = (int)2e5 + 1;
ll T[dd], L[dd], R[dd];
ll D[dd];
 
pair<ll, ll> goR[dd], goL[dd];
pair<ll, ll> EM(-1, 0);
 
pair<ll, ll> merge(pair<ll, ll> a, pair<ll, ll> b) {
    if (a == EM || b == EM) return EM;
    ll l = max(a.first, b.first);
    ll r = min(a.second, b.second);
    return (l > r ? EM : make_pair( l, r ));
}
 
int solve() {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%lld", &T[i]);
    }
    for (int i = 0; i + 1 < n; i++) {
        scanf("%lld %lld", &L[i], &R[i]);
    }
 
 
    goR[n - 1] = { 0, (ll)1e18 };
    for (int i = n - 2; i >= 0; i--) {
        pair<ll, ll> cur = { max(L[i] - T[i], 0ll), R[i] };
        auto c = merge(make_pair(L[i], R[i]), goR[i + 1]);
        if (c == EM) {
            goR[i] = EM;
        } else {
            if (c.first <= L[i])
                c.first = max(0ll, c.first - T[i]);
            goR[i] = merge(cur, c);
        }
    }
 
    goL[0] = { 0, (ll)1e18 };
    for (int i = 1; i < n; i++) {
        pair<ll, ll> cur = { max(L[i - 1] - T[i], 0ll), R[i - 1] };
        auto c = merge(make_pair(L[i - 1], R[i - 1]), goL[i - 1]);
        if (c == EM) {
            goL[i] = EM;
        } else {
            if (c.first <= L[i - 1])
                c.first = max(0ll, c.first - T[i]);
            goL[i] = merge(cur, c);
        }
        //if (i + 1 < n)
        //  goL[i] = merge(goL[i], make_pair(L[i], R[i]));
    }
 
 
    for (int i = 0; i < n; i++) {
        auto c = merge(goL[i], goR[i]);
 
        if (c == EM) printf("-1\n");
        else printf("%lld\n", c.first);
    }
 
    return 0;
}