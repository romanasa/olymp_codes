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

#define TASK "kthzero"

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

const int MAXN = 2e5 + 7;

int T[4 * MAXN], a[MAXN];

int f(int a) {
    return (a & (-a));
}

void update(int pos, int val) {
    for (int i = pos; i < MAXN; i += f(i))
        T[i] += val;
}

int sum(int pos) {
    int ans = 0;
    for (int i = pos; i > 0; i -= f(i))
        ans += T[i];
    return ans;
}

int get(int l, int r) {
    if (l > 0)
        return sum(r) - sum(l - 1);
    return sum(r);
}

int solve() {
    int n, m; 
    cin >> n;
    forn(i, n) {
        scanf("%d", &a[i]);
        update(i + 1, (a[i] == 0));
    }

    cin >> m;
    forn(i, m) {
        string c;
        cin >> c;
        if (c == "u") {
            int pos, val;
            scanf("%d %d", &pos, &val);
            if (a[pos - 1] && !val)
                update(pos, 1);
            if (!a[pos - 1] && val)
                update(pos, -1);
            a[pos - 1] = val;
        }
        else {
            int l, r, k;
            scanf("%d %d %d", &l, &r, &k);

            if (get(l, r) < k)
                printf("-1 ");
            else {
                int ll = l - 1, rr = r;
                while (rr - ll > 1) {
                    int m = (ll + rr) / 2;
                    int cur = get(l, m);
                    if (cur < k)
                        ll = m;
                    else
                        rr = m;
                }
                printf("%d ", rr);
            }
        }
    }
    return 0;
}