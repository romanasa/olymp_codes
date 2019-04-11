#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define TASK "che"

int main() {
#ifdef WIN
    freopen("01", "r", stdin);
#else
    freopen(TASK".in", "r", stdin);
    freopen(TASK".out", "w", stdout);
#endif // WIN

    int n, d;
    cin >> n >> d;


    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    ll ans = 0;
    for (int i = 0; i < n; i++) {
        int j = upper_bound(a.begin(), a.end(), a[i] + d) - a.begin();
        ans += n - j;
    }
    cout << ans << "\n";

    return 0;
}


