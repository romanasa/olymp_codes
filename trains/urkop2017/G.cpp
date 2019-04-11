#include <bits/stdc++.h>

#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

#define x first
#define y second
#define mp make_pair
#define pub push_back
#define all(v) (v).begin(), (v).end()
//236695ZVSVG

using namespace std;

typedef long long ll;
typedef double db;

int main() {
#ifdef WIN
    freopen("01", "r", stdin);
#endif // WIN
    int a, b, c;
    cin >> a >> b >> c;

    int ans = 0;
    for (int it = 0; it <= 1000; it++) {

        int ca = a - 3 * it;
        int cb = b - 2 * it;
        int cc = c - it;

        if (ca > cb && cb > cc && cc > 0) {
            ans = max(ans, it + 1);
        }
    }
    cout << ans << "\n";
    return 0;
}

