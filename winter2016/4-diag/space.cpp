#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__)
 
using namespace std;
 
typedef long long ll;
 
const int dd = (int)1e6;
 
int go[11][dd];
int cnt[11][dd];
int maxd[dd];
 
int main() {
    ll n;
    scanf("%lld", &n);
 
    for (int i = 0; i < 10; i++) {
        maxd[i] = i;
    }
 
    for (int i = 10; i < dd; i++) {
        maxd[i] = max(maxd[i / 10], i % 10);
    }
 
    for (int c = 0; c < 10; c++) {
 
        for (int i = dd - 1; i >= 0; i--) {
 
            if (i + max(maxd[i], c) < dd) {
                go[c][i] = go[c][i + max(maxd[i], c)];
                cnt[c][i] = cnt[c][i + max(maxd[i], c)] + 1;
            } else {
                go[c][i] = i;
                cnt[c][i] = 0;
            }
 
        }
    }
 
    /*for (int i = 0; i < dd; i++) {
        for (int j = 0; j < 10; j++) {
            err("go[%d][%d] = %d, cnt[%d][%d] = %d, ", j, i, go[j][i], j, i, cnt[j][i]);
        }
        err("\n");
    }*/
 
    ll cur = 1;
    ll ans = 1;
 
    while (cur < n) {
 
        int a = cur / dd;
        int b = cur % dd;
 
        int c = maxd[a];
 
        if (cnt[c][b] == 0) {
            int t = max(maxd[a], maxd[b]);
            cur += t;
            ans++;
            continue;
        }
 
 
        if (cur - b + go[c][b] <= n) {
            ans += cnt[c][b];
            cur = cur - b + go[c][b];
            b = go[c][b];
        } else {
            while (cur < n) {
                cur += max(maxd[cur / dd], maxd[cur % dd]);
                ans++;
            }
        }
    }
 
    if (cur == n) {
        printf("%lld\n", ans);
    } else {
        puts("-1");
    }
 
    return 0;
}