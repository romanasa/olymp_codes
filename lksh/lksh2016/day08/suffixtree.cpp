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

#define TASK "suffixtree"

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
    freopen(TASK".in", "r", stdin), freopen(TASK".out", "w", stdout);
    //freopen("input.txt", "r", stdin), freopen("output.txt", "w", stdout), freopen("test.txt", "w", stderr);
#endif
    solve();
    return 0;
}

const int dd = 2e5 + 7;

string s;
map<char, int> go[dd];
int l[dd], r[dd], p[dd], suf[dd];
int nv = 2;

void dfs(int v, int ind, int pos) {
    if (ind >= s.size())
        return;
    char c = s[ind];

    if (pos >= r[v]) {
        if (!go[v].count(c)) {

            int x = nv++;
            p[x] = v;   
            l[x] = ind, r[x] = dd, go[v][c] = x;

            dfs(suf[v], ind, r[v]);
            return;
        }
        dfs(go[v][c], ind + 1, l[go[v][c]] + 1);
    } else if (c == s[pos]) {
        dfs(v, ind + 1, pos + 1);
    } else {
        int x = nv++;

        l[x] = l[v], r[x] = pos, p[x] = p[v];
        l[v] = pos, p[v] = x;

        go[p[x]][s[l[x]]] = x;
        go[x][s[pos]] = v;

        int y = nv++;

        p[y] = x, l[y] = ind, r[y] = dd;
        go[x][c] = y;

        v = suf[p[x]];
        pos = l[x];

        while (pos < r[x]) {
            v = go[v][s[pos]];
            pos += r[v] - l[v];
        }

        suf[x] = (pos == r[x] ? v : nv);

        dfs(v, ind, r[v] - (pos - r[x]));
    }
}

int solve() {
    cin >> s;

    l[1] = -1;
    forn(i, 127)
        go[0][i] = 1;

    dfs(1, 0, 0);

    int c = 0;
    fornn(i, 1, dd)
        c += go[i].size();

    cout << nv - 1 << " " << c << "\n";

    fornn(i, 1, dd) {
        for (auto c : go[i]) {
            cout << i << " " << c.second << " " << l[c.second] + 1 << " " << min(r[c.second], (int)s.size()) << "\n";
        }
    }
    return 0;
}