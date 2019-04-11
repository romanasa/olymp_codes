#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)
 
typedef long long ll;
 
using namespace std;
 
const int dd = (int)2e5 + 1;
 
struct segment {
    int l, r, c;
    bool operator < (segment b) const {
        return r < b.r;
    }
} A[dd];
 
int n, m;
int dp1[dd], dp2[dd];
int opt1[dd], opt2[dd];
int X = 0;
 
struct Fen {
    int T[dd];
    void clear() {
        memset(T, 0, sizeof(int) * X);
    }
    void upd(int pos, int val) {
        for (int i = pos + 1; i < dd; i += (i&-i)) T[i] += val;
    }
    int get(int pos) {
        int res = 0;
        for (int i = pos + 1; i; i -= (i&-i)) res += T[i];
        return res;
    }
    int get(int l, int r) {
        return get(r) - get(l - 1);
    }
} F;
 
vector<pair<int, int> > E[dd];
 
void dfs(int l, int r, int oL, int oR) {
 
    if (l > r) return;
 
    int m = (l + r) / 2;
 
    int opt = 0;
    int tmp;
 
    for (int x = m; x <= r; x++) {
        for (auto c : E[x]) {
            F.upd(c.first, c.second);
        }
    }
 
    for (int t = oL; t <= min(oR, m - 1); t++) {
        if (dp2[m] < (tmp = dp1[t] + F.get(t + 1, m))) {
            dp2[m] = tmp;
            opt = t;
        }
    }
 
    dfs(l, m - 1, oL, opt);
 
    for (int x = m; x <= r; x++) {
        for (auto c : E[x]) {
            F.upd(c.first, -c.second);
        }
    }
 
    dfs(m + 1, r, opt, oR);
}
 
int main() {
    scanf("%d %d", &n, &m);
 
    int ind = 0;
    for (int i = 0; i < n; i++) {
        int a, b, c;
        scanf("%d %d %d", &a, &b, &c);
        b--;
        if (a <= b) {
            A[ind++] = { a, b, c};
            X = max(X, b);
 
            E[b].push_back({ a, c });
        }
    }
    n = ind;
 
    sort(A, A + n);
 
    for (int j = 0; j <= X; j++) {
        dp1[j] = dp2[j] = -(int)2e9;
    }
 
    int ans = 0;
    dp1[0] = 0;
 
    for (int i = 1; i <= m; i++) {
 
        dfs(1, X, 0, X);
 
        for (int j = 0; j <= X; j++) {
            ans = max(ans, dp2[j]);
            dp1[j] = dp2[j], dp2[j] = -(int)2e9;
            opt1[j] = opt2[j], opt2[j] = X;
        }
    }
 
    printf("%d\n", ans);
    return 0;
}