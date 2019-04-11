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
#define mk make_pair
#define TASK "bubbles"
#define inb push_back
#define outb pop_back

const double eps = 1e-9;
const double pi = acos(-1.0);

const ll INF = (ll)2e9 + 1;
const ll LINF = (ll)8e18;
const ll linf = (ll)8e18;
const ll MM = (ll)1e9 + 7;

int solve();
void gen();

int main()
{
#ifdef _DEBUG
    freopen("input.txt", "r", stdin), freopen("output.txt", "w", stdout);
#else
    //freopen(TASK".in", "r", stdin), freopen(TASK".out", "w", stdout);
    //	freopen("input.txt", "r", stdin), freopen("output.txt", "w", stdout), freopen("test.txt", "w", stderr);
#endif
    solve();
    return 0;
}
const int dd = 407;

vector<vector<int> > E;
vector<vector<int> > I;

int dp[dd][dd];
int PR[dd];

int n, k;

const int inf = (int)1e9 + 7;

int cnt[dd];

void upd(int &a, int b) {
    if (a > b)
        a = b;
}

int T[dd][dd];
pair<int, int> P[dd][dd];

int calc(int v, int p) {
    cnt[v] = 1;
    int ind = -1;
    for (int i = 0; i < (int)E[v].size(); i++) {
        int to = E[v][i];
        if (to != p)
            cnt[v] += calc(to, v);
        else
            ind = i, PR[v] = I[v][i];
    }

    if (ind != -1) {
        E[v].erase(E[v].begin() + ind);
        I[v].erase(I[v].begin() + ind);
    }

    return cnt[v];
}

void restore(int v, int x, int p = -1) {

    if (x == 1) {
        for (int i = 0; i < (int)E[v].size(); i++) {
            printf("%d ", I[v][i] + 1);
        }
        return;
    }

    vector<vector<int> > T(E[v].size() + 1, vector<int>(k + 1, inf));
    vector<vector<pair<int, int> > > P(E[v].size() + 1, vector<pair<int, int> >(k + 1, make_pair(-1, -1)));

    if (x == 0) {
        printf("%d ", PR[v] + 1);
        return;
        x = min_element(dp[v] + 1, dp[v] + k + 1) - dp[v];
    }

    T[0][1] = 0;

    for (int i = 0; i < (int)E[v].size(); i++) {
        int to = E[v][i];

        for (int t = 0; t <= k; t++) {
            for (int j = 0; t + j <= k; j++) {
                if (T[i + 1][t + j] > T[i][t] + dp[to][j]) {
                    T[i + 1][t + j] = T[i][t] + dp[to][j];
                    P[i + 1][t + j] = { t, i };
                }
            }
        }
    }

    int s = E[v].size(), j = x;
    while (s) {
        int t = P[s][j].first;

        restore(E[v][s - 1], j - t, v);

        j = t;
        s--;
    }
}

void dfs(int v, int p) {
    fill(dp[v], dp[v] + k + 1, inf);

    vector<vector<int> > T(E[v].size() + 1, vector<int>(k + 1, inf));

    for (int to : E[v]) {
        if (to != p) {
            dfs(to, v);
        }
    }

    T[0][1] = 0;

    for (int i = 0; i < (int)E[v].size(); i++) {
        int to = E[v][i];
        if (to == p) {
            for (int t = 0; t <= k; t++)
                upd(T[i + 1][t], T[i][t]);
            continue;
        }

        for (int t = 0; t <= k; t++) {
            for (int j = 0; t + j <= k; j++) {
                upd(T[i + 1][t + j], T[i][t] + dp[to][j]);
            }
        }
    }

    for (int i = 0; i <= k; i++)
        dp[v][i] = T[(int)E[v].size()][i];

    if (cnt[v] == 1)
        dp[v][1] = 0;

    dp[v][0] = *min_element(dp[v] + 1, dp[v] + cnt[v] + 1) + 1;
}

int solve() {
    scanf("%d %d", &n, &k);

    E.resize(n);
    I.resize(n);

    for (int i = 0; i < n - 1; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        E[a - 1].push_back(b - 1);
        E[b - 1].push_back(a - 1);
        I[a - 1].push_back(i);
        I[b - 1].push_back(i);
    }

    calc(0, -1);
    dfs(0, -1);

    int ans = inf;
    for (int i = 0; i < n; i++) {
        ans = min(ans, dp[i][k] + (i > 0));
    }
    printf("%d\n", ans);
    for (int i = 0; i < n; i++) {
        if (dp[i][k] + (i > 0) == ans) {

            if (i) printf("%d ", PR[i] + 1);
            restore(i, k);
            return 0;
        }
    }
    return 0;
}
