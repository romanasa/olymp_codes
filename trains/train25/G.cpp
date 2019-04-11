#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define TASK "prizes"

int main() {
#ifdef WIN
    freopen("01", "r", stdin);
#else
    freopen(TASK".in", "r", stdin);
    freopen(TASK".out", "w", stdout);
#endif // WIN

    int n, m;
    cin >> n >> m;

    if (min(n, m) == 1) {
        if (n > m) swap(n, m);
        if (n == 1 && m == 1) cout << 0, exit(0);
        if (n == 1 && m == 2) cout << 0, exit(0);
        cout << (m - 3) / 4 + 1;
        return 0;
    }
    if (min(n, m) == 2){
        cout << 0;
        exit(0);
    }
    cout << 1;
    return 0;
}


