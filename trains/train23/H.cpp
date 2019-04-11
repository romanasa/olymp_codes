#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int main() {
    freopen("game.in", "r", stdin);
    freopen("game.out", "w", stdout);
    int a, b;
    cin >> a >> b;
    int f = 0;
    if (a == 2 * b) f = 1;
    if (a * 2 == b) f = 1;
    if (f == 0) cout << 0, exit(0);

    int x = 0, y = 0;
    while (a % 2 == 0) a /= 2, x++;
    while (b % 2 == 0) b /= 2, y++;
    if (x % 2 == 1) x++;
    if (y % 2 == 0) y++;
    cout << min(x + 1, y + 1);
    return 0;
}

