#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int main() {
#ifdef WIN
    freopen("01", "r", stdin);
#else
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif // WIN
    int n, k;
    cin >> n >> k;
    cout << max(0, max(n - k - 2, k - 3));
    return 0;
}
