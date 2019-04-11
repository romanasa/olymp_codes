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

#define TASK "cubes"

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
    //freopen(TASK".in", "r", stdin), freopen(TASK".out", "w", stdout);
    //freopen("input.txt", "r", stdin), freopen("output.txt", "w", stdout), freopen("test.txt", "w", stderr);
#endif
    solve();
    return 0;
}

vector<vector<int> > e;
int pr[207], used[207];
int tmm = 1;

bool dfs(int v) {
    if (used[v] == tmm) return false;
    used[v] = tmm;
    forn(i, e[v].size()) {
        int to = e[v][i];
        if (pr[to] == -1 || dfs(pr[to])) {
            pr[to] = v;
            return true;
        }
    }
    return false;
}

int solve() {
    int n;
    cin >> n;
    string name;
    cin >> name;
    e.resize(name.size() + n);
    forn(i, n) {
        string cur;
        cin >> cur;
        forn(k, name.size()) {
            bool ok = false;
            forn(j, cur.size())
                if (cur[j] == name[k])
                    ok = true;
            if (ok)
                e[k].pk(i + name.size());
        }
    }
    forn(i, name.size() + n)
        pr[i] = -1;
    forn(i, name.size()) {
        tmm++;
        dfs(i);
    }

    int res = 0;
    forn(i, name.size() + n)
        if (pr[i] != -1)
            res++;

    if (res == name.size()) {
        cout << "YES\n";
        vector<int> ans(name.size());
        forn(i, name.size() + n)
            if (pr[i] != -1)
                ans[pr[i]] = i - name.size() + 1;
        forn(i, ans.size())
            cout << ans[i] << " ";
    }
    else 
        cout << "NO\n";
    return 0;
}