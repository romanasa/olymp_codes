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
    int h, m;
    cin >> h >> m;

    int t = h * 60 + m;

    int st = 12 * 60;

    if (t == st) puts("Start");
    else {
        int q = (t < st ? st - t : st - t + 24 * 60);
        if (q < 60) printf("%dm\n", q);
        else printf("%dh\n", q / 60);
    }
    return 0;
}

