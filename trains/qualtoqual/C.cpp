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
    int n;
    cin >> n;
    int len = (n - 1) / 9;
    int cur = n - 9 * len;
    cout << string(len + 1, (char)(cur + '0'));
    return 0;
}

