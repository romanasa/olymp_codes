#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define mp make_pair
#define pub push_back
#define x first
#define all(a) a.begin(), a.end()
#define y second

#define TASK "rbtrees"

vector<int> g[1111];
int root;
int n;
bool was[1111];

int mm;
int pp;

bool dfs(int v, int pred, int sum){
    sum += ((mm >> v) & 1);
    if (v != root){
        if (!((mm >> v) & 1)) if (!((mm >> pred) & 1)) return 0;
    }
    if (g[v].size() != 2){
        if (pp == -1) pp = sum;
        else if (pp != sum) return 0;
    }
    for (int to : g[v]) if (!dfs(to, v, sum)) return 0;
    return 1;
}

bool ok(int mask){
    mm = mask;
    pp = -1;
    return dfs(root, -1, 0);
}

int main() {
#ifdef WIN
    freopen("01", "r", stdin);
#else
    freopen(TASK".in", "r", stdin);
    freopen(TASK".out", "w", stdout);
#endif // WIN
    ios_base::sync_with_stdio(0);
    cin >> n;
    for (int i = 0; i < n; i++){
        int a, b;
        cin >> a >> b;
        if (a != 0) g[i].pub(a - 1), was[a - 1] = 1;
        if (b != 0) g[i].pub(b - 1), was[b - 1] = 1;
    }
    for (int i = 0; i < n; i++) if (!was[i]) root = i;
    int ans = 0;
    for (int mask = 0; mask < (1 << n); mask++){
        if (ok(mask)) ans++;
    }
    cout << ans;
}


