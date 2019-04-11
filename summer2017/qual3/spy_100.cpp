#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__)

using namespace std;
 
typedef long long ll;
 
vector<vector<pair<int, int> > > E, ER;
 
const int dd = 1500 + 7;
 
vector<int> H;
int used[dd];
 
void topsort(int v) {
    used[v] = 1;
    for (auto c : E[v]) {
        if (!used[c.first]) {
            topsort(c.first);
        }
    }
    H.push_back(v);
}
 
ll dp[dd][dd];
 
void upd(ll &a, ll b) { if (a > b) a = b; }
 
ll P[dd], S[dd];
 
int main() {
    int n, m;
    scanf("%d %d", &n, &m);
 
    E.resize(n);
    ER.resize(n);
 
    for (int i = 0; i < m; i++) {
        int a, b, c;
        scanf("%d %d %d", &a, &b, &c);
        ER[b - 1].push_back({ a - 1, c });
        E[a - 1].push_back({ b - 1, c });
    }
 
    int s1, s2, f1, f2;
    scanf("%d %d %d %d", &s1, &f1, &s2, &f2);
    s1--, s2--, f1--, f2--;
 
    for (int i = 0; i < n; i++) {
        E[i].push_back({ i, 0 });
        ER[i].push_back({ i, 0 });
 
        sort(E[i].begin(), E[i].end(), [](pair<int, int> a, pair<int, int> b){
             return a.second < b.second;
        });
        sort(ER[i].begin(), ER[i].end(), [](pair<int, int> a, pair<int, int> b){
             return a.second < b.second;
        });
    }
 
    for (int i = 0; i < n; i++) {
        if (!used[i]) {
            topsort(i);
        }
    }
    reverse(H.begin(), H.end());
 
    for (int i = 0; i < n; i++) fill(dp[i], dp[i] + n, (ll)1e18);
 
    dp[s1][s2] = 0;
 
    for (int pa : H) {
        for (int b : H) {
 
            for (int i = 0; i < (int)ER[b].size(); i++) {
                P[i] = (i ? P[i - 1] : (ll)1e18);
                P[i] = min(P[i], dp[pa][ER[b][i].first]);
            }
 
            for (int i = (int)ER[b].size() - 1; i >= 0; i--) {
                S[i] = (i + 1 < (int)ER[b].size() ? S[i + 1] : (ll)1e18);
                S[i] = min(S[i], dp[pa][ER[b][i].first] + ER[b][i].second);
            }
 
            int ind = 0;
 
            for (auto a : E[pa]) {
 
                if (a.first == b) {
                    continue;
                }
 
                //err("pa = %d, a = %d, b = %d, ind = %d\n", pa, a.first, b, ind);
 
                while (ind < (int)ER[b].size() && ER[b][ind].second <= a.second)
                    ind++;
 
                if (ind) upd(dp[a.first][b], P[ind - 1] + a.second);
                if (ind < (int)ER[b].size()) upd(dp[a.first][b], S[ind]);
 
                //err("cur = %lld\n", dp[a.first][b]);
            }
        }
    }
 
    /*for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) if (dp[i][j] != (ll)1e18)
            err("dp[%d][%d] = %lld\n", i, j, dp[i][j]);
        err("\n");
    }*/
 
    if (dp[f1][f2] == (ll)1e18) return 0 * puts("-1");
 
    printf("%lld\n", dp[f1][f2]);
    return 0;
}