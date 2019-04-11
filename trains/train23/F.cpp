#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

pair<int, int> a[5];


bool check(int a, int b, int c, int d) {
    if (a == c && b + d == a) return true;
    if (b == d && a + c == b) return true;
    return false;
}

int main() {
    freopen("square.in", "r", stdin);
    freopen("square.out", "w", stdout);

    for (int i = 0; i < 3; i++) cin >> a[i].first >> a[i].second;


    sort(a, a + 3);

    do {
        int q = a[0].first;
        int w = a[0].second;

        int ok = 1;
        if (a[1].first == a[0].first) {
            w += a[1].second;
        } else if (a[1].second == a[0].second) {
            q += a[1].first;
        } else {
            ok = 0;
        }

        if (ok && check(q, w, a[2].first, a[2].second)) {
            puts("YES");
            return 0;
        }
    } while (next_permutation(a, a + 3));


    do {
        int q = a[0].first;
        int w = a[0].second;

        int ok = 1;
        if (a[1].second == a[0].second) {
            q += a[1].first;
        } else if (a[1].first == a[0].first) {
            w += a[1].second;
        } else {
            ok = 0;
        }

        if (ok && check(q, w, a[2].first, a[2].second)) {
            puts("YES");
            return 0;
        }
    } while (next_permutation(a, a + 3));

    puts("NO");
    return 0;
}

