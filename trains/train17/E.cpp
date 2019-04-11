#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int n;

int main() {
#ifdef WIN
    freopen("01", "r", stdin);
#endif // WIN
    cin >> n;
    for (int i = 2; i < n; i++){
        if (i >= 2 && n - i >= 2 && __gcd(i, n - i) == 1) cout << i << ' ' << n - i, exit(0);
    }
    cout << -1;
}
