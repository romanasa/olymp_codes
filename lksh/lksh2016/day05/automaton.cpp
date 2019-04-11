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

#define TASK "automaton"

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

const int dd = 2e5 + 7;

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

int solve() {
    forn(i, dd) {
        forn(j, 31) {
            go[i][j] = -1;
        }
    }
    suf[0] = -1;

    string s;
    cin >> s;

    for (auto c : s)
        add(c - 'a');
    
    vector<pair<pair<int, int>, int> > edges;
    forn(i, nv) {
        forn(j, 31) {
            if (go[i][j] != -1) {
                edges.push_back(mp(mp(i, go[i][j]), j));
            }
        }
    }
    cout << nv << " " << edges.size() << "\n";
    for (auto c : edges)
        cout << c.first.first + 1 << " " << c.first.second + 1 << " " << (char)('a' + c.second) << "\n";

    vector<int> ans;
    for (int p = last; p != -1; p = suf[p])
        ans.push_back(p);
    cout << ans.size() << "\n";
    for (int x : ans)
        cout << x + 1 << " ";

    return 0;
}