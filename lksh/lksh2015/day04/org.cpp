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

#define TASK "org"

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

int dp[1007][107], used[1007], money[1007], k, n;
vector<vector<int> > e;
vector<int> global_ans;

void dfs(int v) {
    used[v] = true;
    for (int to : e[v]) 
        if (!used[to])
            dfs(to);
    
    vector<vector<int> > cost(e[v].size() + 1, vector<int>(k + 1, INF));
    cost[0][0] = 0;

    fornn(i, 1, e[v].size() + 1){
        int to = e[v][i - 1];
        forn(j, k + 1){
            if (dp[to][j] == INF)
                continue;
            forn(l, k + 1){
                if (j + l <= k){
                    cost[i][j + l] = min(cost[i][j + l], cost[i - 1][l] + dp[to][j]);
                }
            }
        }
    }

    int f = e[v].size();
    dp[v][0] = money[v];
    forn(i, e[v].size()){
        int sum = INF;
        forn(j, k + 1){
            sum = min(sum, dp[e[v][i]][j]);
        }
        dp[v][0] += sum;
    }
    for (int cur = 1; cur <= k; cur++) {
        dp[v][cur] = cost[f][cur - 1];
    }
}

void go(int v, int g) {
    if (g) {
        g--;
        vector<vector<pair<int, pair<int, int> > > > cost(e[v].size() + 1, vector<pair<int, pair<int, int> > >(k + 1, {INF, {-1, -1}}));
        cost[0][0] = {0, {-1, -1}};

        fornn(i, 1, e[v].size() + 1){
            int to = e[v][i - 1];
            forn(j, k + 1){
                if (dp[to][j] == INF)
                    continue;
                forn(l, k + 1){
                    if (j + l <= k){
                        cost[i][j + l] = min(cost[i][j + l], mp(cost[i - 1][l].first + dp[to][j], mp((int)to, (int)j)));
                    }
                }
            }
        }

        vector<pair<int, int> > p;
        int ff = e[v].size(), ss = g;
        while (ff) {
            int cc = e[v][ff - 1], gg = cost[ff][ss].second.second;

            if (gg != -1) {
                p.pk({cc, gg});
                ss -= gg;
            }
            else {
                p.pk({cc, 0});
            }
            ff--; 
        }

        for (auto pr : p) {
            go(pr.first, pr.second);
        }
    }
    else {
        global_ans.pk(v);
        forn(i, e[v].size()){
            int sum = INF;
            forn(j, k + 1){
                sum = min(sum, dp[e[v][i]][j]);
            }
            int ind = -1;
            forn(j, k + 1)
                if (sum == dp[e[v][i]][j] && ind == -1)
                    ind = j;
            go(e[v][i], ind);
        }
    }
}

int solve() {
    cin >> k >> n;
    k--;
    e.resize(n);
    fornn(i, 1, n) {
        int to;
        cin >> to;
        to--;
        e[to].pk(i);
    }
    forn(i, n)
        cin >> money[i];
    forn(i, n)
        if (!used[i])
            dfs(i);
    int ans = 0;
    forn(i, k + 1)
        if (dp[0][i] < dp[0][ans])
            ans = i;
    cout << dp[0][ans] << "\n";
    go(0, ans);
    for (int x: global_ans)
        cout << x + 1 << " ";
    return 0;
}