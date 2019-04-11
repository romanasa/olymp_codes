#include <bits/stdc++.h>

#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

#define x first
#define y second
#define mp make_pair
#define pub push_back
#define all(v) (v).begin(), (v).end()

using namespace std;

typedef long long ll;
typedef double db;

int main() {
#ifdef WIN
    freopen("01", "r", stdin);
#endif // WIN
    ll s, b;
    cin >> s >> b;
    cout.precision(10);
    cout << fixed << sqrt(b * b + 4 * s);
    return 0;
}

