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

#define TASK "color"

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

vector<vector<int> > e, eR;
int n, m;

int used[dd];
int comp[dd];

void add(int a, int b) {
    e[a ^ 1].push_back(b);
    e[b ^ 1].push_back(a);

    eR[b].push_back(a ^ 1);
    eR[a].push_back(b ^ 1);
}

vector<int> H;

void dfs1(int v) {
    used[v] = true;
    for (int to : e[v]) {
        if (!used[to])
            dfs1(to);
    }
    H.push_back(v);
}

void dfs2(int v, int c) {
    comp[v] = c;
    for (int to : eR[v]) {
        if (!comp[to])
            dfs2(to, c);
    }
}

int solve() {
    cin >> n >> m;
    
    e.resize(2 * n);
    eR.resize(2 * n);

    string s;
    cin >> s;

    forn(i, m) {
        int a, b;
        cin >> a >> b;

        a--, b--;

        if (s[a] == s[b]) {
            add(2 * a, 2 * b);
            add(2 * a + 1, 2 * b + 1);
        }

        if (s[a] == 'R') {
            if (s[b] == 'G') {
                add(2 * a + 1, 2 * b);
            }
            if (s[b] == 'B') {
                add(2 * a, 2 * b);
            }
        }
        if (s[a] == 'G') {
            if (s[b] == 'R') {
                add(2 * a, 2 * b + 1);
            }
            if (s[b] == 'B') {
                add(2 * a + 1, 2 * b + 1);
            }
        }
        if (s[a] == 'B') {
            if (s[b] == 'R') {
                add(2 * a, 2 * b);
            }
            if (s[b] == 'G') {
                add(2 * a + 1, 2 * b + 1);
            }
        }
    }

    forn(i, 2 * n) {
        if (!used[i])
            dfs1(i);
    }

    reverse(all(H));

    int cur = 1;
    for (int v : H) {
        if (comp[v] == 0) {
            dfs2(v, cur++);
        }
    }
    bool ok = true;
    forn(i, 2 * n) {
        if (comp[i] == comp[i ^ 1])
            ok = false;
    }
    if (!ok) {
        puts("Impossible");
        return 0;
    }

    forn(i, n) {
        if (s[i] == 'R') {
            cout << (comp[2 * i] > comp[2 * i + 1] ? 'B' : 'G');
        }
        if (s[i] == 'G') {
            cout << (comp[2 * i] > comp[2 * i + 1] ? 'R' : 'B');
        }
        if (s[i] == 'B') {
            cout << (comp[2 * i] > comp[2 * i + 1] ? 'R' : 'G');
        }
    }
	return 0;
}