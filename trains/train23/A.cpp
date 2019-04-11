#include <bits/stdc++.h>

using namespace std;

int n, m;

int main() {
    freopen("mines.in", "r", stdin);
    freopen("mines.out", "w", stdout);
    cin >> n >> m;
    int ans = 0;

    ans = ((n + 2) / 3) * ((m + 2) / 3);

    cout << ans;
}
