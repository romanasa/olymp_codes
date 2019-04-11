#include <bits/stdc++.h>

using namespace std;

int main()
{
    freopen("wheels.in", "r", stdin);
    freopen("wheels.out", "w", stdout);
    int n;
    cin >> n;

    map<int, int> m;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        m[x]++;
    }

    int ans = 0;
    for (auto c : m) ans += (c.second / 4);
    cout << ans << "\n";

    return 0;
}

