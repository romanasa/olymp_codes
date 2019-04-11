#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define TASK "wrong"

bool was[11111];

int main() {
#ifdef WIN
    freopen("01", "r", stdin);
#else
    freopen(TASK".in", "r", stdin);
    freopen(TASK".out", "w", stdout);
#endif // WIN
    int n, k;
    cin >> n >> k;
    k %= n;
    int x = 0;
    while(1){
        was[x] = 1;
        x += k;
        while(x >= n) x -= n;
        if (was[x]) break;
    }
    int dd = 0;
    for (int i = 0; i < n; i++) if (!was[i]) dd++;
    cout << dd;

    return 0;
}
