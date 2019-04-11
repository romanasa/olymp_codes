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

const int mod = (int)1e9 + 7;

int main() {
#ifdef WIN
    freopen("01", "r", stdin);
#endif // WIN
    int n;
    cin >> n;

    ll cur = 1;
    int curM = 1;

    ll maxC = 2e18;
    int ok = 0;

    for (int i = 0; i < n; i++) {
        ll t;
        cin >> t;

        curM = (curM + curM) % mod;
        cur *= 2;

        if (!ok && t > cur) return 0 * puts("error");

        cur -= t;
        curM -= t % mod;
        if (curM < 0) curM += mod;

        if (cur > maxC) ok = 1;
    }
    cout << curM;
    return 0;
}

