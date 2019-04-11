#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <set>
#include <map>
#include <bitset>
#include <string>
#include <fstream>
#include <vector>
#include <cstring>
#include <cassert>
#include <random>
#include <ctime>
#include <numeric>
 
using namespace std;
 
typedef long long ll;
typedef double ld;
 
int solve();
#define TASK "ant"
#define err(...) //fprintf(stdout, __VA_ARGS__), fflush(stdout)
 
 
int n, m;
 
int main() {
#ifdef HOME
    //freopen("input.txt", "r", stdin), freopen("output.txt", "w", stdout);
#else
    //freopen(TASK".in", "r", stdin), freopen(TASK".out", "w", stdout);
#endif
    solve();
}
 
const int dd = (int)2e4 + 7;
const int inf = (int)2e9 + 1;
 
struct req { int l, r, cnt; };
 
vector<req> T[dd];
int point[dd], P[dd];
char A[51][dd];
 
int dp1[dd], dp2[dd];
int F[51][dd];
 
void upd(int &a, int b) {
    if (a > b) a = b;
}
 
int solve() {
    int n, t, s;
    scanf("%d %d %d", &n, &t, &s);
 
    for (int i = 0; i < t; i++) {
        scanf("%d", &point[i]);
        P[i + 1] = point[i] + P[i];
    }
 
    for (int i = 0; i < n; i++) {
        scanf("%s", A[i]);
    }
 
    set<pair<int, int> > S;
 
    vector<int> last(n, -1);
 
    for (int j = 0; j < n; j++)
        S.insert({ last[j], j });
 
    for (int i = 0; i < t; i++) {
 
        for (int j = 0; j < n; j++) {
            if (A[j][i] == '0') {
                S.erase({ last[j], j });
                last[j] = i;
                S.insert({ last[j], j });
            }
        }
 
        int pr = -1, cur = 0;
        for (auto c : S) {
            if (pr + 1 <= c.first) {
                T[i].push_back({ pr + 1, c.first, cur });
                pr = c.first;
            }
            cur++;
        }
 
        if (T[i].empty()) {
            T[i].push_back({ pr + 1, i, n });
        }
        if (T[i].back().r < i) {
            T[i].push_back({ T[i].back().r + 1, i, n });
        }
 
    }
 
    fill(dp1, dp1 + t + 1, inf);
    fill(dp2, dp2 + t + 1, inf);
    dp1[0] = 0;
 
    for (int cnt = 0; cnt <= n; cnt++) {
        for (int i = 0; i <= t; i++) {
            F[cnt][i] = inf;
        }
    }
 
    for (int cnt = 0; cnt <= n; cnt++) {
        for (int j = 0; j <= t; j++) {
            int cur = dp1[j] - cnt * P[j];
            F[cnt][j] = min((j ? F[cnt][j - 1] : inf), cur);
        }
    }
 
    for (int it = 1; it <= s; it++) {
        fill(dp2, dp2 + t + 1, (int)2e9 + 1);
 
        for (int i = it; i <= t; i++) {
            for (auto &e : T[i - 1]) {
                upd(dp2[i], F[e.cnt][min(e.r, i - 1)] + e.cnt * P[i]);
            }
        }
 
         
        copy(dp2, dp2 + t + 1, dp1);
        fill(dp2, dp2 + t + 1, inf);
 
 
        for (int cnt = 0; cnt <= n; cnt++) {
            for (int i = 0; i <= t; i++) {
                F[cnt][i] = inf;
            }
        }
 
 
        for (int cnt = 0; cnt <= n; cnt++) {
            for (int j = 0; j <= t; j++) {
                int cur = dp1[j] - cnt * P[j];
                F[cnt][j] = min((j ? F[cnt][j - 1] : inf), cur);
            }
        }
 
        printf("%d\n", dp1[t]);
    }
 
    return 0;
}