#include <bits/stdc++.h>
 
typedef long long ll;
 
using namespace std;
 
const int dd = (int)1e6 + 7;
 
vector<pair<int, int> > F[dd];
vector<int> cnt[dd];
int j, used[dd], pr[dd];
vector<int> ans;
 
void dfs(int v) {
    pr[v] = 1;
    for (auto i : F[v]) if (!used[i.second])
        ans.push_back(i.second), used[i.second] = 1;
    while (++j < (int)ans.size()) {
        int col = ans[j];
        for (int gr : cnt[col]) if (!pr[gr]) {
            dfs(gr);
            return;
        }
    }
}
 
int pos[dd];
set<int> G[dd];
 
int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    for (int i = 0; i < m; ++i) {
        int k;
        scanf("%d", &k);
        F[i].resize(k);
        for (int j = 0; j < k; ++j) {
            scanf("%d", &F[i][j].second), --F[i][j].second;
            cnt[F[i][j].second].push_back(i);
        }
    }
 
    for (int i = 0; i < n; ++i) if (!(int)cnt[i].size())
        ans.push_back(i), ++j;
 
    for (int i = 0; i < m; ++i)
        for (auto &j : F[i]) j.first = (int)cnt[j.second].size();
 
    for (int i = 0; i < n; ++i) if ((int)cnt[i].size() == 2) {
        G[cnt[i][0]].insert(cnt[i][1]);
        G[cnt[i][1]].insert(cnt[i][0]);
    }
 
    for (int i = 0; i < m; ++i) sort(F[i].begin(), F[i].end());
 
    for (int i = n - 1; i >= 0; --i) if (!used[i] && (int)cnt[i].size() == 1 && (int)G[cnt[i][0]].size() < 2)
        dfs(cnt[i][0]);
 
    for (int i = 0; i < n; ++i) pos[ans[i]] = i;
    for (int i : ans) printf("%d ", i + 1);
    return 0;
}