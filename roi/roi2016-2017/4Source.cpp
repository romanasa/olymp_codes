#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)
 
typedef long long ll;
typedef long double ld;
 
using namespace std;
 
const int dd = (int)1e6 + 1;
 
vector<vector<pair<int, int> > > Q, E, ER;
vector<vector<pair<ll, ll> > > G;
 
int n, m;
 
struct line {
    ll k, b;
};
 
ld inter(line a, line b) {
    return (b.b - a.b) * 1.0 / (a.k - b.k);
}
 
struct Convex {
    vector<line> T;
    vector<ld> X;
     
    int j = 0;
     
    void add(line M) {
        while (T.size()) {
            ld x = inter(T.back(), M);
            if (x >= X.back()) T.pop_back(), X.pop_back();
            else {
                T.push_back(M), X.push_back(x);
                return;
            }
        }
        T.push_back(M), X.push_back(1e18);
    }
     
    ll get(ll x) {
        //j = lower_bound(X.begin(), X.end(), -x) - X.begin();// - 1;
        //if (j < 0 || j == (int)X.size()) return -(ll)1e18;
        ll cur = -(ll)1e18;
        for (auto c : T) cur = max(cur, c.k * x + c.b);
        return cur;
    }
};
 
vector<Convex> W;
 
ll sqr(ll x) { return x * x; }
     
vector<ll> get(int v, vector<vector<pair<int, int> > > &E) {
    vector<ll> d(n, (ll)1e18);
    set<pair<int, int> > S;
     
    d[v] = 0;
    S.insert(make_pair(d[v], v));
     
    while (S.size()) {
        int v = S.begin()->second;
        S.erase(S.begin());
        for (int i = 0; i < (int)E[v].size(); i++) {
            int to = E[v][i].first;
            ll cur = d[v] + E[v][i].second;
            if (d[to] > cur) {
                S.erase(make_pair(d[to], to));
                d[to] = cur;
                S.insert(make_pair(d[to], to));
            }
        }
    }
    return d;
}
 
int used[dd];
ll dp[dd];
vector<int> H;
 
void topsort(int v) {
    used[v] = 1;
    for (int i = 0; i < (int)E[v].size(); i++) {
        int to = E[v][i].first;
        if (!used[to]) 
            topsort(to);
    }
    H.push_back(v);
}
 
#define TASK "trains"
 
int main() {
//#ifndef HOM
//    freopen(TASK".in", "r", stdin), freopen(TASK".out", "w", stdout);
//#endif
    scanf("%d %d", &n, &m);
    Q.resize(n);
    E.resize(n);
    ER.resize(n);
    G.resize(m);
     
    for (int i = 0; i < m; i++) {
        int sz;
        scanf("%d", &sz);
         
        int v;
        scanf("%d", &v);
        v--;
         
        G[i].push_back({ v, -1 });
         
        for (int j = 0; j < sz; j++) {
            int to, len;
            scanf("%d %d", &len, &to);
            to--;
             
            G[i].push_back({ to, len });
             
            E[v].push_back(make_pair(to, len));
            ER[to].push_back(make_pair(v, len));
             
            v = to;
        }
    }
     
    vector<ll> d0 = get(0, E);
     
    printf("%lld ", d0[n - 1]);
     
    vector<ll> d1 = get(n - 1, ER);
 
    for (int v = 0; v < n; v++) {
        vector<pair<int, int> > cur;
        for (int i = 0; i < (int)E[v].size(); i++) {
            int to = E[v][i].first;
            if (d0[v] + E[v][i].second + d1[to] == d0[n - 1])
                cur.push_back(E[v][i]);
        }
        E[v] = cur;
    }
     
    int cur = 0;
    for (int num = 0; num < m; num++) {
        int pr = -1;
        ll x = 0;
        cur++;
        for (auto c : G[num]) {
            int v = c.first, len = c.second;
             
            if (pr == -1 || d0[pr] + len + d1[v] == d0[n - 1]) {
                x += max(len, 0);
                Q[v].push_back({ cur, x });
            } else {
                cur++, x = 0;
                Q[v].push_back({ cur, x });
            }
            pr = v;
        }
    }
     
    /*for (int i = 0; i < n; i++) {
        err("Q[%d] = {", i);
        for (auto c : Q[i]) err("(num = %d, x = %d), ", c.first, c.second);
        err("\n");
    }*/
     
    for (int i = 0; i < n; i++) {
        if (!used[i]) {
            topsort(i);
        }
    }
    reverse(H.begin(), H.end());
     
    cur++;
    W.resize(cur);
     
    fill(dp, dp + n, -(ll)1e18);
    dp[0] = 0;
     
    for (int i = 0; i < n; i++) {
        int v = H[i];
         
        //err("calc for %d\n", v);
         
        for (int j = 0; j < (int)Q[v].size(); j++) {
            ll cur = -(ll)1e18;
             
            int ind = Q[v][j].first;
            ll x = Q[v][j].second;
             
            cur = W[ind].get(x) + x * x;
             
            dp[v] = max(dp[v], cur);
        }
         
        for (int j = 0; j < (int)Q[v].size(); j++) {
         
            int ind = Q[v][j].first;
            ll x = Q[v][j].second;
            if (dp[v] != -(ll)1e18) {
                W[ind].add({ -2 * x, dp[v] + x * x});
            }
        }
         
        //err("dp[%d] = %lld\n", v, dp[v]);
    }
     
    printf("%lld\n", dp[n - 1]);
    return 0;
}