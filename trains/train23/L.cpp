#include <bits/stdc++.h>

#define ll long long

using namespace std;

int n, m;

int main() {
    freopen("ants.in", "r", stdin);
    freopen("ants.out", "w", stdout);
    cin >> n >> m;
    ll ans = m * (ll)m * 6;
    set<int> se1, se2;
    for (int i = 0; i < n; i++){
        int x, y;
        char c;
        cin >> x >> y >> c;
        if (c == 'W' || c == 'E'){
            se1.insert(y);
        } else {
            se2.insert(x);
        }
    }
    ans -= m * 4 * (ll)(se1.size() + se2.size());
    ans += (ll)se1.size() * (ll)se2.size() * 2;
    cout << ans;
}
