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
#else
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif // WIN
    int n, sum = 0;
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        int x;
        string s;
        cin >> x >> s;
        sum += x;
    }
    cout << sum;
    return 0;
}

