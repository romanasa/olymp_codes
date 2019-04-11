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

#define TASK "owls"

const double eps = 1e-7;
const double pi = acos(-1.0);

const int INF = (int)2e9 + 1;
const ll LINF = (ll)9e18 + 7;
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
    //gen();
    //double t = times;
    solve();
    //cerr << times - t;
    return 0;
}

vector<vector<int> > e;

const int MAXN = 3e5 + 7;
int cnt = 550;
bool w[MAXN];

int solve() {
    int n, m;
    cin >> n >> m;

    e.resize(n);
    forn(i, m) {
        int a, b;
        scanf("%d %d", &a, &b);
        e[a - 1].pk(b - 1);
        e[b - 1].pk(a - 1);
    }

    forn(i, n)
        sort(all(e[i]));

    vector<int> fat;
    int c = 0;
    forn(i, n)
        if (e[i].size() > cnt)
            w[i] = 1, c++, fat.pk(i);

    vector<vector<bool> > ew(c, vector<bool>(n, false));

    forn(j, c) {
        int i = fat[j];
        for (int to : e[i])
            ew[j][to] = 1;
    }

    ll ans1 = 0, ans2 = 0, ans3 = 0, ans4 = 0;
    forn(j, c) {
        int v = fat[j];
        forn(i, n)
            for (int to : e[i]) {
                if (ew[j][i] && ew[j][to]) {
                    if (w[i] && w[to])
                        ans1++;
                    if (w[i] ^ w[to])
                        ans2++;
                    if (!w[i] && !w[to])
                        ans3++;
                }
            }
    }

    forn(v, n)
        if (!w[v])
            for (int to : e[v])
                if (!w[to]) {
                    int i = 0, j = 0;
                    while (i < e[v].size() && j < e[to].size()) {
                        if (e[v][i] == e[to][j] && !w[e[v][i]])
                            ans4++;

                        if (e[v][i] < e[to][j])
                            i++;
                        else
                            j++;
                    }
                }

    ans1 /= 6;
    ans2 /= 4;
    ans3 /= 2;

    ans4 /= 6;

    cout << ans1 + ans2 + ans3 + ans4;
    return 0;
}