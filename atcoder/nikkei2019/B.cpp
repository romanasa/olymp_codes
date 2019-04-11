#include <bits/stdc++.h>
#ifdef SIR
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)
#else
#define err(...) 42
#endif

typedef long long ll;

using namespace std;

void solve() {
    int n; cin >> n;
    string a, b, c; cin >> a >> b >> c;

    int ans = 0;
    for (int i = 0; i < n; i++) {
        set<char> s;
        s.insert(a[i]), s.insert(b[i]), s.insert(c[i]);
        if (s.size() == 2) ans += 1;
        else if (s.size() == 3) ans += 2;
    }
    cout << ans << "\n";
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