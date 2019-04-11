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

#define forn(i, n) for (int i = 0; i < (int)n; i++)
#define fornn(i, q, n) for (int i = q; i < (ll)n; i++)
#define mp make_pair
#define pk push_back
#define all(v) v.begin(), v.end()
#define times clock() * 1.0 / CLOCKS_PER_SEC

#define TASK "power"

const double eps = 1e-7;
const double pi = acos(-1.0);

const int INF = (int)2e9 + 1;
const ll LINF = (ll)8e18;
const ll MM = (ll)1e9 + 7;

int solve();
void gen();

int main()
{
#ifdef _DEBUG
    freopen("input.txt", "r", stdin), freopen("output.txt", "w", stdout);
#else
    //freopen(TASK".in", "r", stdin), freopen(TASK".out", "w", stdout);
    //freopen("input.txt", "r", stdin), freopen("output.txt", "w", stdout), freopen("test.txt", "w", stderr);
#endif
    solve();
    return 0;
}

const int MAXN = 2e5 + 7;
const int MAXC = 1e6 + 7;
ll a[MAXN], res[MAXN], cnt[MAXC];
ll ans = 0;

inline void gol1(int l, int L) {
    while (l < L)
        ans += (1 - 2 * cnt[a[l]]) * a[l], cnt[a[l]]--, l++;
}

inline void gol2(int l, int L) {
    l--;
    while (l >= L)
        ans += (1 + 2 * cnt[a[l]]) * a[l], cnt[a[l]]++, l--;
}

inline void gor1(int l, int L) {
    while (l > L)
        ans += (1 - 2 * cnt[a[l]]) * a[l], cnt[a[l]]--, l--;
}

inline void gor2(int l, int L) {
    l++;
    while (l <= L)
        ans += (1 + 2 * cnt[a[l]]) * a[l], cnt[a[l]]++, l++;
}

struct rq {
    int first, second, ind;
};

int solve() {
    int n, m;
    cin >> n >> m;

    int siz = 1249;
    fornn(i, 1, n + 1)
        scanf("%d", &a[i]);

    vector<rq> req(m);
    forn(i, m) {
        scanf("%d %d", &req[i].first, &req[i].second);
        req[i].ind = i;
    }

    sort(all(req), [siz](rq a, rq b)
    {return a.first / siz == b.first / siz ? a.second < b.second : a.first / siz < b.first / siz; });

    int l = 0, r = 0;
    forn(i, m) {
        gol1(l, req[i].first);
        gol2(l, req[i].first);

        gor1(r, req[i].second);
        gor2(r, req[i].second);

        res[req[i].ind] = ans;
        l = req[i].first, r = req[i].second;
    }

    forn(i, m)
        printf("%lld\n", res[i]);
    return 0;
}
