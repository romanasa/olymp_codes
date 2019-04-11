#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fprintf(stderr, "\n"), fflush(stderr)

typedef long long ll;

using namespace std;

ll n, m, k, len;
int a[15];
unordered_map<ll, int> ind;

int cnt = 0;


void dfs(ll v) {
    //if (cnt >= k) return;
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
        //if (cnt >= k) return;
    }
}


void solve() {
	//freopen("01", "r", stdin);
    cin >> n >> m >> k;
    for (int i = 0; i < m; i++) cin >> a[i];
    
    mt19937 rnd(1);
    len = 1;
    for (int i = 1; i < n; i++) {
        len *= m;
        if (len * m > (ll)1e7) {
        	for (int it = 0; it < n + k - 1; it++) cout << a[rnd() % m];
        	return;
        }
    }
    
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