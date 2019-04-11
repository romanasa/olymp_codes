#include <bits/stdc++.h>

#define ll long long

int n;
int a[11111];
ll ans1 = 0, ans2 = 0;

using namespace std;
int main() {
    freopen("captains.in", "r", stdin);
    freopen("captains.out", "w", stdout);
    cin >> n;
    for (int i = 0; i < n; i++) cin >> a[i];
    sort(a, a + n);
    reverse(a, a + n);
    for (int i = 0; i < n; i += 2){
        if ((i / 2) % 2 == 0){
            ans1 += a[i];
            ans2 += a[i + 1];
        } else {
            ans2 += a[i];
            ans1 += a[i + 1];
        }
    }
    if (ans1 > ans2) cout << "YES\n";
    else cout << "NO\n";
    cout << ans1 << ' ' << ans2;
}
