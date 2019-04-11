#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int main() {
#ifdef WIN
    freopen("01", "r", stdin);
#endif // WIN
    int t, p, n;
    cin >> t >> p >> n;
    cout << n * t + (n - 1) * p;
    return 0;
}

