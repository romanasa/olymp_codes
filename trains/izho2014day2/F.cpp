#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)
 
using namespace std;
 
typedef long long ll;
 
#define TASK "marriage"
 
 
const int dd = (int)3.2e4 + 7;
 
vector<int> E[dd];

int cnt = 0, tmm;
int pr[dd], used[dd];
 
bool dfs(int v) {
    used[v] = tmm;
    for (int to : E[v]) if (pr[to] == -1) {
        pr[to] = v, pr[v] = to;
        cnt++;
        return true;
    }
    for (int to : E[v]) if (used[pr[to]] != tmm && dfs(pr[to])) {
        pr[to] = v, pr[v] = to;
        return true;
    }
    return false;
}
 
bool dfs2(int v, int l, int r) {
    used[v] = tmm;
    for (int to : E[v]) if (l < to && to < r) {
        if (pr[to] == -1) {
            pr[to] = v, pr[v] = to;
            cnt++;
            return true;
        }
    }
    for (int to : E[v]) if (l < to && to < r) {
        if (used[pr[to]] != tmm && dfs2(pr[to], l, r)) {
            pr[to] = v, pr[v] = to;
            return true;
        }
    }
    return false;
}

 
int main() {
#ifndef HOME
    freopen(TASK".in", "r", stdin), freopen(TASK".out", "w", stdout);
#endif
    ios_base::sync_with_stdio(0);
    cin.tie(0);
     
    int n, m, k;
    cin >> n >> m >> k;
     
    for (int i = 0; i < k; i++) {
        int a, b;
        cin >> a >> b;
        E[a - 1].push_back(b - 1 + n);
        E[b - 1 + n].push_back(a - 1);
    }
    
    for (int i = 0; i < n + m; i++) random_shuffle(E[i].begin(), E[i].end());
     
    int ans = 0;
    int r = 0;
     
    fill(pr, pr + n + m, -1);
     
    for (int l = 0; l + m <= n; l++) {
    
    	tmm++;
        while (r < n && cnt < m) {
            if (dfs(r)) tmm++;
            r++;
        }
        
        if (cnt < m) break;
        ans += n - r + 1;
         
        if (pr[l] != -1) {
            cnt--;  
            pr[pr[l]] = -1;
            tmm++;  
            dfs2(pr[l], l, r);
        }
    }
     
    cout << ans << "\n";
    return 0;
}