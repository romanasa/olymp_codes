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

#define TASK "bridges"

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

const int MAXN = 2e4 + 7;
const int MAXE = 2e5 + 7;

int tmm = 1, used[MAXN], enter[MAXN], up[MAXN];
int mul[MAXE];

vector<vector<int> > e;
vector<pair<int, int> > ans, edge;
vector<map<int, int> > num;

void dfs(int v, int p = -1) {
    used[v] = true;
    enter[v] = up[v] = tmm++;

    forn(i, e[v].size()) {
        int to = e[v][i];
        if (!used[to]) {
            dfs(to, v);
            if (up[to] >= enter[to]) {
                ans.pk(mp(v, to));
            }
            up[v] = min(up[v], up[to]);
        }
        else if (to != p) {
            up[v] = min(up[v], enter[to]);
        }
    }
}

int solve() {
    int n, m;
    cin >> n >> m;
    e.resize(n);
    num.resize(n);
    forn(i, m) {
        int a, b;
        cin >> a >> b;
        
        int cur = num[a - 1][b - 1];
        
        if (cur)
            mul[cur] = true;
        else {
            num[a - 1][b - 1] = num[b - 1][a - 1] = i + 1;
            e[a - 1].pk(b - 1);
            e[b - 1].pk(a - 1);
        }
    }

    forn(i, n)
        if (!used[i])
            dfs(i);

    int res = 0;
    forn(i, ans.size())
        if (!mul[num[ans[i].first][ans[i].second]])
            res++;

    vector<int> number;
    cout << res << "\n";
    forn(i, ans.size())
        if (!mul[num[ans[i].first][ans[i].second]])
            number.pk(num[ans[i].first][ans[i].second]);
    sort(all(number));
    forn(i, number.size())
        cout << number[i] << "\n";
    return 0;
}