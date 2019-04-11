#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int main() {
    freopen("snipers.in", "r", stdin);
    freopen("snipers.out", "w", stdout);

    int n, m;
    cin >> n >> m;

    if (min(n, m) == 1) {
        cout << max(n, m) << "\n";
        return 0;
    }

    cout << (n + m - 2) * 2 << "\n";
    return 0;
}

