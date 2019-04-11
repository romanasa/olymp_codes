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

const double pi = atan2(1, 1) * 4.0;

int main() {
#ifdef WIN
    freopen("01", "r", stdin);
#endif // WIN
    int n, a, v;
    cin >> n >> a >> v;

    double ans = a * n / (2.0 * sin(pi / n) * cos(pi / 2 * (n - 2) / n));
    cout.precision(10);
    cout << fixed << ans;
    return 0;
}

