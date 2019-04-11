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
#include <sstream>
#include <numeric>

using namespace std;

typedef unsigned long long ull;
typedef long long ll;
typedef long double ld;

#define forn(i, n) for (int i = 0; i < (int)n; i++)
#define fornn(i, q, n) for (ll i = q; i < (ll)n; i++)
#define mp make_pair
#define pk push_back
#define all(v) v.begin(), v.end()
#define times clock() * 1.0 / CLOCKS_PER_SEC

#define TASK "freedom"

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

const int dd = 5e5 + 7;

int go[dd][31];
int len[dd], suf[dd];

int last = 0, nv = 1;

int clone(int v) {
    int cur = nv++;

    forn(i, 31)
        go[cur][i] = go[v][i];

    return cur;
}

void add(int c) {
    int nlast = nv++;

    len[nlast] = len[last] + 1;

    int p = last;
    while (p != -1 && go[p][c] == -1) {
        go[p][c] = nlast;
        p = suf[p];
    }

    if (p == -1) {
        suf[nlast] = 0;
    } else {
        int q = go[p][c];

        if (len[q] == len[p] + 1)
            suf[nlast] = q;
        else {
            int r = clone(q);

            len[r] = len[p] + 1;

            suf[r] = suf[q], suf[q] = r;
            suf[nlast] = r;

            while (p != -1 && go[p][c] == q) {
                go[p][c] = r;
                p = suf[p];
            }
        }
    }
    last = nlast;
}

int h[dd], used[dd];
vector<int> topsort;
pair<int, int> p[dd];

void dfs(int v) {
    used[v] = true;
    forn(j, 31) {
        if (go[v][j] != -1 && !used[go[v][j]])
            dfs(go[v][j]);
    }
    topsort.push_back(v);
}

int P1[dd], P2[dd];
int term[dd];

bool find1(int v) {
    used[v] = true;

    if (term[v])
        P2[v] = true;

    forn(j, 31) {
        if (go[v][j] != -1 && P2[go[v][j]] && j != 27)
            P2[v] = true;

        if (go[v][j] != -1 && !used[go[v][j]]) {
            if (find1(go[v][j])) {
                
                if (j != 27)
                    P2[v] = true;
            }
            
        }
    }
    return P2[v];
}

bool find2(int v) {
    used[v] = true;

    forn(j, 31) {
        if (go[v][j] != -1 && P1[go[v][j]])
            P1[v] = true;

        if (go[v][j] != -1 && !used[go[v][j]]) {
            if (find2(go[v][j])) {
                P1[v] = true;
            }
        }
    }
    if (go[v][27] != -1)
        P1[v] = true;

    return P1[v];
}

int solve() {
    forn(i, dd) {
        forn(j, 31) {
            go[i][j] = -1;
        }
    }
    suf[0] = -1;

    int n;
    cin >> n;

    string s, t;
    cin >> s >> t;

    for (auto c : s)
        add(c - 'A');

    add(27);

    for (auto c : t)
        add(c - 'A');

    for (int v = last; v != -1; v = suf[v])
        term[v] = true;

    find1(0);

    memset(used, 0, sizeof(int) * dd);

    find2(0);
    memset(used, 0, sizeof(int) * dd);
    dfs(0);

    reverse(all(topsort));

    forn(i, nv)
        p[i] = mp(-1, -1);

    for (int v : topsort) {
        forn(j, 31) {
            if (go[v][j] != -1)
                if (h[go[v][j]] < h[v] + 1) {
                    h[go[v][j]] = h[v] + 1;
                    p[go[v][j]] = mp(v, j);
                }
        }
    }
/*
    forn(i, nv) {
        forn(j, 31) {
            if (go[i][j] != -1) {
                cout << i << " " << go[i][j] << " " << j << "\n";
            }
        }
    }*/

    int ans = 0, cur = 0;
    forn(i, nv) {
        if (P1[i] && P2[i]) {
            if (ans < h[i]) {
                ans = h[i];
                cur = i;
            }
        }
    }

    memset(used, 0, sizeof(int) * dd);
    
    string path;
    for (int v = cur; p[v].first != -1; v = p[v].first)
        path += (char)('A' + p[v].second);
    reverse(all(path));
    cout << path;
    return 0;
}