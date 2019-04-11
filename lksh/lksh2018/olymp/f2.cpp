#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

const int maxN = 4e5;

vector<int> g[maxN];
vector<int> rg[maxN];
vector<int> order;
bool used[maxN];
int tout[maxN];
int pos[maxN];
int timer = 0;
long long dp[maxN];
const long long MOD = 1e9 + 7;

void dfs(int v) {
    used[v] = true;
    for(int u : g[v]) 
        if(!used[u])
            dfs(u);
    order.push_back(v);
    tout[v] = timer++;
}

bool cmp(int a, int b) {
    return pos[a] < pos[b];
}

int main() {
    int n, m, k;
    scanf("%d%d%d", &n, &m, &k);
    int s, t;
    for(int i = 0; i < m; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        u--, v--;
        g[u].push_back(v);
        rg[v].push_back(u);
    }
    for(int i = 0; i < n; i++) 
        if(!used[i])
            dfs(i);
    reverse(order.begin(), order.end());
    for(int i = 0; i < n; i++) {
        pos[order[i]] = i;
    }
    scanf("%d%d", &s, &t);
    s--, t--;
    vector<int> v(k);
    for(int i = 0; i < k; i++) {
        scanf("%d", &v[i]);
        v[i]--;
    }
    v.push_back(s);
    v.push_back(t);
    sort(v.begin(), v.end(), cmp);
    //for(int x : v) cerr << x << " ";
    if(v[0] != s || v.back() != t) {
        printf("0");
        return 0;
    }
    dp[v[0]] = 1;
    //for(int i = 0; i <= pos[v[0]]; i++) {
    //    dp[order[i]] = 1;
    //    for(int u : rg[order[i]])
    //        dp[order[i]] = (dp[order[i]] + dp[u]) % MOD;
    //}
    for(int i = 1; i < order.size(); i++) {
        for(int j = pos[v[i - 1]] + 1; j <= pos[v[i]]; j++) {
           // dp[order[j]] = 1;
            for(int u : rg[order[j]]) {
                if(pos[v[i - 1]] <= pos[u] && pos[u] < pos[v[i]])
                    dp[order[j]] = (dp[order[j]] + dp[u]) % MOD;
            }
        }
    }
    long long res = dp[v.back()];
    //for(int i = pos[v[k - 1]] + 1; i < n; i++) {
    //    for(int u : rg[order[i]])
    //        if(pos[v[i - 1]] <= pos[u])
    //            dp[order[i]] = (dp[order[i]] + dp[u]) % MOD;
    //    res = (res + dp[order[i]]) % MOD;
    //}
    printf("%lld", res);
    return 0;
}
