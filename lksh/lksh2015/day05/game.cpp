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

#define TASK "game"

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
    freopen(TASK".in", "r", stdin), freopen(TASK".out", "w", stdout);
    //freopen("input.txt", "r", stdin), freopen("output.txt", "w", stdout), freopen("test.txt", "w", stderr);
#endif
    solve();
    return 0;
}

int num[150000], dp[150000];
vector<int> res;

void go(int msk) {
    if (num[msk])
        res.pk(num[msk]);
    else {
        for (int pdk = msk; pdk > 0; pdk = (pdk - 1) & msk)
            if (dp[pdk] + dp[msk - pdk] == dp[msk] && msk - pdk > 0) {
                go(pdk), go(msk - pdk);
                break;
            }
    }
}

int solve() {
    int n, m;
    cin >> n >> m;

    forn(i, 1 << n)
        dp[i] = -INF;

    forn(i, m) {
        string s;
        cin >> s;
        int msk = 0;
        bool ok = true;
        forn(j, s.size()) {
            msk |= (1 << (s[j] - 'a'));
            forn(k, s.size())
                if (j != k && s[j] == s[k])
                    ok = false;
        }
        if (ok)
            num[msk] = i + 1, dp[msk] = s.size() - 1;
    }

    dp[0] = 0;
    forn(msk, 1 << n) {
        for (int pdk = msk; pdk > 0; pdk = (pdk - 1) & msk) {
            if (dp[pdk] != -INF && dp[msk - pdk] != -INF)
                dp[msk] = max(dp[msk], dp[pdk] + dp[msk - pdk]);
        }
    }



    int ans = 0;
    forn(msk, 1 << n)
        if (dp[msk] > dp[ans])
            ans = msk;
    go(ans);
    cout << res.size() << "\n";
    for (int x : res)
        cout << x << "\n";
    return 0;
}