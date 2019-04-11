#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)
 
typedef long long ll;
 
using namespace std;
 
vector<vector<int> > E;
 
const int dd = (int)5e5 + 1;
 
int ans[2 * dd], h[dd];
 
void upd(int &a, int b) { if (a < b) a = b; }
 
void calc(int v, int pr = -1, int hh = 0) {
    h[v] = 0;
    for (int to : E[v]) if (to != pr) {
        calc(to, v, hh + 1);
        h[v] = max(h[v], h[to] + 1);
    }
}
 
vector<pair<int, int> > X[2 * dd];
    int n;
 
void upd(pair<pair<int, int> , pair<int, int> > &a, pair<int, int> b) {
    if (a.first.second == -1 || b.first >= a.first.first) {
        a.second = a.first;
        a.first = b;
    } else if (a.second.second == -1 || b.first >= a.second.first) {
        a.second = b;
    }
}
 
void dfs(int v, int pr, int hp) {
 
    vector<int> cur;
    if (hp) cur.push_back(hp);
    for (int to : E[v]) if (to != pr)
        cur.push_back(h[to] + 1);
 
    sort(cur.begin(), cur.end());
 
    //err("v = %d, hp = %d\n", v, hp);
    for (int i = 0; i < (int)cur.size(); i++) {
        int l = i ? cur[i - 1] : 0;
        int r = cur[i];
        int c = 2;
 
        if (l <= r) {
            //err("add [%d, %d], %d\n", l, r, c);
            X[l].push_back({ 1, c });
            X[r].push_back({ -1, c});
        }
    }
 
    for (int i = 0; i < (int)cur.size(); i++) {
        int l = max(i ? cur[i - 1] : 0, 1);
        int r = cur[i];
        int c = (int)cur.size() - i;
 
        l = 2 * l, r = 2 * r;
 
        if (l <= r) {
            //err("add [%d, %d], %d\n", l, r, c);
            X[l].push_back({ 1, c });
            X[r].push_back({ -1, c});
        }
    }
 
    pair<pair<int, int>, pair<int, int> > cc;
    cc.first = {-1, -1};
    cc.second = {-1, -1 };
 
    upd(cc, { hp, pr });
 
    for (int to : E[v]) if (to != pr)
        upd(cc, { h[to] + 1, to });
 
    //err("((%d, %d), (%d, %d))\n", cc.first.first, cc.first.second,
    //    cc.second.first, cc.second.second);
 
    for (int to : E[v]) if (to != pr) {
        int mx = (cc.first.second == to ? cc.second.first : cc.first.first);
        dfs(to, v, mx + 1);
    }
}
 
int main() {
    scanf("%d", &n);
    E.resize(n);
    for (int i = 0; i + 1 < n; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        E[a - 1].push_back(b - 1);
        E[b - 1].push_back(a - 1);
    }
 
    calc(0);
    dfs(0, -1, 0);
 
    multiset<int> S;
    for (int i = 0; i <= n; i++){
        for (auto c : X[i]) {
            if (c.first == 1) {
                S.insert(c.second);
            }
        }
 
        ans[i] = S.size() ? *S.rbegin() : 1;
 
        for (auto c : X[i]) {
            if (c.first == -1) {
                S.erase(S.find(c.second));
            }
        }
 
 
    }
 
 
    for (int i = 1; i <= n; i++) {
        if (i % 2 == 1) ans[i] = min(ans[i], 2);
        printf("%d%c", ans[i], " \n"[i == n]);
    }
    return 0;
}