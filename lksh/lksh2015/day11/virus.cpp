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

#define TASK "virus"

const double eps = 1e-7;
const double pi = acos(-1.0);

const int INF = (int)2e9 + 1;
const ll LINF = (ll)9e18 + 7;
const ll MM = (ll)1e9 + 7;

int solve();

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

char Z[] = {'0', '1'};
int mv = 1;
vector<vector<int> > go(30007, vector<int>(2, -1));
vector<int> en(30007), suf(30007), par(30007), used(30007), bad(30007);

void add(string s) {
    int cur = 0;
    for (char c : s) {
        if (go[cur][c - '0'] == -1) 
            par[mv] = cur, go[cur][c - '0'] = mv++;
        cur = go[cur][c - '0'];
    }
    en[cur] = true;
}

void dfs(int v, int c = -1) {
    if (used[v])
        return;

    if (v) {
        if (par[v])
            suf[v] = go[suf[par[v]]][c];
        else
            suf[v] = 0;
        dfs(suf[v], c);
    } 

    forn(x, 2) {
        if (go[v][x] == -1)
            go[v][x] = (v == 0 ? 0 : go[suf[v]][x]);
    }

    used[v] = true;

    forn(x, 2)
        dfs(go[v][x], x);
}

bool ok = false;

void check(int v) {
    used[v] = 1;
    forn(c, 2) {
        int to = go[v][c];
        
        if (bad[to])
            continue;

        if (used[to] == 1)
            ok = true;

        if (!used[to])
            check(to);
    }
    used[v] = 2;
}

int solve() {
    int n;
    cin >> n;
    forn(i, n) {
        string s;
        cin >> s;
        add(s);
    }
    dfs(0);

    used.assign(30007, 0);
    
    forn(i, 30007) {
        int g = i, ex = 0;
        while (g) {
            if (en[g]) {
                bad[i] = 1;
                break;
            }
            g = suf[g];
        }
    }

    check(0);

    if (ok)
        cout << "TAK";
    else
        cout << "NIE";
    return 0;
}