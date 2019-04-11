#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fprintf(stderr, "\n"), fflush(stderr)

typedef long long ll;

using namespace std;

ll n, m, k, len;
int a[15];
unordered_map<ll, int> ind;

int cnt = 0;

void dfs(ll v) {
    while (ind[v] < m) {

        ll to = (v * m + ind[v]) % len;
        int cur = a[ind[v]];
        ind[v]++;


        if (cnt + 1 < k) {
            dfs(to);
        }

        int out = -1;
        if (cnt < k) out = cur;

        cnt++;
        if (out != -1) cout << out;
    }
}

void solve() {
    cin >> n >> m >> k;

    len = 1;
    for (int i = 1; i < n; i++) {
        len *= m;
        if (len > (ll)1e10) break;
    }

    for (int i = 0; i < m; i++) cin >> a[i];

    dfs(0);
    for (int i = 1; i < n; i++) cout << a[0];
    cout << "\n";

}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
#ifdef SIR
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    solve();
}