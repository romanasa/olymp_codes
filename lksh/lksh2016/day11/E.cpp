#define _CRT_SECURE_NO_WARNINGS
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

#define forn(i, n) for (int i = 0; i < (int)(n); i++)
#define fornn(i, q, n) for (ll i = q; i < (ll)n; i++)
#define mp make_pair
#define all(v) v.begin(), v.end()
#define times clock() * 1.0 / CLOCKS_PER_SEC

#define TASK "hull"

const double eps = 1e-7;
const double pi = acos(-1.0);

const ll inf = (ll)2e9 + 1;
const ll linf = (ll)8e18;

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

const int dd = 1e6 + 7;

vector<int> e[dd];
ll A[dd], dp[dd];

struct tr{
    vector<ll> k, b;
    vector<double> x;
    int j = 0;

    void add(ll K, ll B) {
        while (1) {

            if (k.size() == 0) {
                k.push_back(K);
                b.push_back(B);
                x.push_back(0);
                break;
            }

            if (k.back() == K) {
                if (B > b.back())
                    break;
            } else {
                double t = (B - b.back()) * 1.0 / (k.back() - K);

                if (t > x.back()) {
                    k.push_back(K);
                    b.push_back(B);
                    x.push_back(t);
                    break;
                }
            }

            x.pop_back();
            k.pop_back();
            b.pop_back();
        }
    }

    ll get(ll t) {
        while (j + 1 < x.size() && x[j + 1] < t)
            j++;
        return k[j] * t + b[j];
    }
} F;

int solve() {
    int n;
    scanf("%d", &n);

    int maxx = 0;

    multiset<int> S;

    forn(i, n) {
        int a, b;
        scanf("%d %d", &a, &b);

        maxx = max(maxx, a);
        e[a].push_back(b);
        S.insert(b);
    }

    forn(i, dd) {
        A[i] = (S.size() ? *S.rbegin() : inf);
        for (int x : e[i])
            S.erase(S.find(x));
    }

    forn(i, dd)
        dp[i] = inf;

    dp[0] = 0;
    
    for (int i = 1; i <= maxx; i++) {
        F.add(A[i], dp[i - 1]);
        dp[i] = F.get(i);
    }
    printf("%lld", dp[maxx]);
    return 0;
}