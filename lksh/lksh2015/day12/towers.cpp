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
#include <unordered_set>

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

#define TASK "towers"

const double eps = 1e-7;
const double pi = acos(-1.0);

const int inf = (int)2e9 + 1;
const ll linf = (ll)9e18 + 7;
const ll MM = (ll)1e9 + 7;

int solve();
void gen();

int main() {
#ifdef _DEBUG
    freopen("input.txt", "r", stdin), freopen("output.txt", "w", stdout);
#else
    freopen(TASK".in", "r", stdin), freopen(TASK".out", "w", stdout);
    //freopen("input.txt", "r", stdin), freopen("output.txt", "w", stdout), freopen("test.txt", "w", stderr);
#endif
    solve();
    return 0;
}

int s[100007], a[100007], c[100007], head[100007], na[100007], nc[100007], b[100007], lcp[100007];

int solve() {
    int n;
    while (scanf("%d", &n)) {
        if (!n)
            break;

        forn(i, n) 
            scanf("%d", &s[i]);

        fornn(i, n, n + n)
            s[i] = s[i - n];

        s[n + n] = -1;

        int old = n;
        n = 2 * n + 1;

        int L = 1;
        
        vector<pair<int, int> > cur;
        forn(i, n) cur.pk(mp(s[i], i));
        sort(all(cur));
        forn(i, n) a[i] = cur[i].second;

        int cc = -1;
        forn(i, n) {
            if (!i || s[a[i]] != s[a[i - 1]])
                cc++, head[cc] = i;
            c[a[i]] = cc;
        }
        
        while (L < n) {
            forn(i, n) {
                int j = (a[i] - L + n) % n;
                na[head[c[j]]++] = j;
            }
            int cc = -1;
            forn(i, n) {
                if (!i || c[na[i]] != c[na[i - 1]] || c[(na[i] + L) % n] != c[(na[i - 1] + L) % n])
                    cc++, head[cc] = i;
                nc[na[i]] = cc;
            }
            forn(i, n) c[i] = nc[i], a[i] = na[i];
            L *= 2;
        }

        forn(i, n)
            b[a[i]] = i;

        int z = 0;
        ll ans = 0;
        forn(j, n) {
            int i = b[j];
            if (i == n - 1)
                continue;

            int t = a[i + 1];
                
            while (z < n && s[(j + z) % n] == s[(t + z) % n])
                z++;
            
            lcp[i] = z;
            if (z > 0)
                z--;
        }

        for(int i = n - 2; i >= 0; i--) {
            if (a[i] >= old && a[i + 1] >= old)
                lcp[i] = min(lcp[i + 1], lcp[i]);
            
            if (a[i] < old) {
                if (a[i + 1] >= old)
                    lcp[i] = min(lcp[i + 1], lcp[i]);
            }
            lcp[i] = min(old, lcp[i]);
            if (a[i] < old)
                ans += lcp[i];
        }
        printf("%lld\n", ans);  
    }
    return 0;
}