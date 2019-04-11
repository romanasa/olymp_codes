#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)
 
using namespace std;
 
typedef long long ll;
 
#define TASK "g"
 
/*struct segment {
    int val, len, pos;
    bool operator < (const segment &b) const {
        return pos < b.pos;
    }
};*/
 
typedef pair<int, pair<int, int> > segment;
 
#define val second.first
#define len second.second
#define pos first
 
set<segment> S;
priority_queue<pair<int, int> > T;
 
void calc(int pos, int mx, vector<int> &x) {
    int n = (int)x.size();
     
    vector<pair<int, int> > cur;
     
    for (int i = 0; i < n; i++) {
        int ind = (pos + i) % n;
        if (cur.empty() || cur.back().first != x[ind]) cur.push_back({ x[ind], 1 });
        else cur.back().second++;
    }
     
    for (int i = 0; i < (int)cur.size(); i++) {
        auto c = cur[i];
         
        int pr = cur[i ? i - 1 : (int)cur.size() - 1].first;
        int nt = cur[(i + 1) % (int)cur.size()].first;
         
        S.insert(make_pair(pos, c));
        if (c.first < pr && c.first < nt) T.push({ -c.second, pos });
     
        pos = (pos + c.second) % n;
    }
}
 
 
 
 
void add(segment c) {
    auto it = S.insert(c).first;
     
    auto prv = it;
    if (it == S.begin()) prv = --S.end();
    else --prv;
     
    auto nxt = it;
    if (it == --S.end()) nxt = S.begin();
    else ++nxt;
     
    if (c.val < nxt->val && c.val < prv->val) T.push({ -c.len, c.pos });
}
 
int main() {
#ifndef HOME
    freopen(TASK".in", "r", stdin), freopen(TASK".out", "w", stdout);
#endif
    ios_base::sync_with_stdio(0);
    cin.tie(0);
     
    int n, k;
    cin >> n >> k;
     
    vector<int> x(n);
    for (int i = 0; i < n; i++) cin >> x[i];
     
    int pos = -1;
    for (int i = 0; i < n; i++) {
        if (x[i] != x[(i + 1) % n]) pos = (i + 1) % n;
    }
    if (pos == -1) return 0 * puts("0");
     
    int mx = *max_element(x.begin(), x.end());
    calc(pos, mx, x);
     
    int ans = 0;
     
     
    while (T.size() && k >= -T.top().first) {
        k -= (-T.top().first);
         
        auto it = S.lower_bound(make_pair(T.top().second, make_pair(-1, -1)));
        T.pop();
 
        ans += 2;
         
        if (S.size() == 1) break;
         
        auto prv = it;
        if (it == S.begin()) prv = --S.end();
        else --prv;
         
        auto nxt = it;
        if (it == --S.end()) nxt = S.begin();
        else ++nxt;
         
        if (prv == nxt) {
            if (it->val + 1 < prv->val) {
                auto c = *it;
                S.erase(it);
                c.val++;
                add(c);
            } else {
                auto c = *it;
                 
                c.val++;
                c.len += prv->len;
                 
                S.erase(it);
                S.erase(prv);
                add(c); 
            }
        } else {
            if (it->val + 1 < prv->val && it->val + 1 < nxt->val) {
                auto c = *it;
                S.erase(it);
                c.val++;
                add(c);
            } else if (it->val + 1 < prv->val) {
                auto c = *it;
                c.len += nxt->len;
                c.val++;
                 
                S.erase(it);
                S.erase(nxt);
                 
                add(c);
            } else if (it->val + 1 < nxt->val) {
                auto c = *it;
                c.len += prv->len;
                c.pos = prv->pos;
                c.val++;
                 
                S.erase(it);
                S.erase(prv);
                 
                add(c);
            } else {
                auto c = *it;
                c.len += prv->len;
                c.len += nxt->len;
                c.pos = prv->pos;
                c.val++;
                 
                S.erase(it);
                S.erase(prv);
                S.erase(nxt);
                 
                add(c);
            }
        }
    }
     
    cout << ans << "\n";
    return 0;
}