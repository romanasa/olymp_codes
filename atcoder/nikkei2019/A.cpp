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
    int a, b; cin >> a >> b;
    cout << min(a, b) << " " << max(0, a - (n - b)) << "\n";
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