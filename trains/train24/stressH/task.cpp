#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define mp make_pair
#define pub push_back
#define x first
#define all(a) a.begin(), a.end()
#define y second

#define TASK "rbtrees"

const ll base = (ll)10;
const int MAXC = 100;

struct bigInt{
    int a[MAXC];
    bigInt() { for (int i = 0; i < MAXC; i++) a[i] = 0; }
};

void add(bigInt &a, bigInt b, bigInt c){
    ll now = 0;
    for (int i = 0; i < MAXC; i++){
        now += b.a[i] + c.a[i];
        a.a[i] = now % base;
        now /= base;
    }
    assert(now == 0);
}

void mult(bigInt &a, bigInt b, bigInt c){
    bool f1 = 1, f2 = 1;
    for (int i = 0; i < MAXC; i++){
        if (b.a[i] != 0) f1 = 0;
        if (c.a[i] != 0) f2 = 0;
    }
    if (f1 || f2) return;
    ll ost = 0;
    for (int i = 0; i < MAXC; i++){
        a.a[i] = ost;
        ost = 0;
        for (int j = 0; j <= i; j++){
            ll now = b.a[j] * (ll)c.a[i - j] + a.a[i];
            a.a[i] = now % base;
            ost += now / base;
        }
        //cout << a.a[i] << endl;
    }
    assert(ost == 0);
}

int getLen(ll x){
    if (x == 0) return 1;
    int ans = 0;
    while(x){
        ans++;
        x /= 10;
    }
    return ans;
}

void print(bigInt &a){
    bool st = 0;
    for (int i = MAXC - 1; i >= 0; i--){
        if (st){
            for (int i = 0; i < 1 - getLen(a.a[i]); i++) cout << 0;
            cout << a.a[i];
        } else {
            if (a.a[i] > 0){
                cout << a.a[i];
                st = 1;
            }
        }
    }
    if (!st) cout << 0;
}

int n, root;
vector<int> g[1111];
bool stop[1111];
bool was[1111];

void dfs(int v){
    if (g[v].size() != 2){
        stop[v] = 1;
        if (g[v].size() == 1){
            if (g[g[v][0]].size() != 0) cout << 0, exit(0);
        }
        return;
    }
    for (int to : g[v]) dfs(to);
}

bigInt dp[2][1001][2];

int NOW;

void calc(int v){
    if (stop[v]){
        if (NOW != 1) return;
        if (g[v].size() == 0){
            dp[0][v][0].a[0] = 1;
            dp[1][v][1].a[0] = 1;
        } else {
            dp[1][v][1].a[0] = 1;
        }
        return;
    }
    for (int to : g[v]) calc(to);
    if (g[v].size() == 1){
        int to1 = g[v][0];
        dp[0][v][1] = dp[1][to1][1];
        if (1) add(dp[1][v][1], dp[0][to1][1 - 1], dp[1][to1][1 - 1]);
    } else {
        int to1 = g[v][0], to2 = g[v][1];
        mult(dp[0][v][1], dp[1][to1][1], dp[1][to2][1]);
        if (1){
            bigInt tmp1, tmp2;
            add(tmp1, dp[0][to1][1 - 1], dp[1][to1][1 - 1]);
            add(tmp2, dp[0][to2][1 - 1], dp[1][to2][1 - 1]);
            mult(dp[1][v][1], tmp1, tmp2);
        }
    }
}

bigInt ans;

int main() {
    ios_base::sync_with_stdio(0);
    cin >> n;
    for (int i = 0; i < n; i++){
        int a, b;
        cin >> a >> b;
        if (a != 0) g[i].pub(a - 1), was[a - 1] = 1;
        if (b != 0) g[i].pub(b - 1), was[b - 1] = 1;
    }
    if (n == 1) cout << 2, exit(0);
    for (int i = 0; i < n; i++) if (!was[i]) root = i;
    dfs(root);
    for (int i = 1; i < 1001; i++){
        NOW = i;
        calc(root);
        bigInt tmp;
        add(tmp, dp[0][root][1], dp[1][root][1]);
        add(ans, ans, tmp);
        for (int j = 0; j < n; j++) for (int w = 0; w < 2; w++){
            dp[w][j][0] = dp[w][j][1];
            for (int jj = 0; jj < MAXC; jj++) dp[w][j][1].a[jj] = 0;
        }
    }
    print(ans);
}


