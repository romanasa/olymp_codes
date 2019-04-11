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
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; i++) cout << i + 1 << " "; cout << "\n";
    for (int i = 0; i < m; i++) cout << (i + 1) * (n + 1) << " ";
    return 0;
}

