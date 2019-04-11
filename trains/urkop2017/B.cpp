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
int a[5];

int main() {
#ifdef WIN
    freopen("01", "r", stdin);
#endif // WIN
    cin >> a[1] >> a[2] >> a[3];

    bool fl1 = true, fl2 = true;
    for (int i = 1; i <= 3; i++)
    {
        if (a[i] == 1)
            fl1 = false;
        if (a[i] != 0)
            fl2 = false;
    }
    if (fl2)
        cout << 1 << ' ';
    else
        cout << 0 << ' ';
    if (fl1)
        cout << 1 << ' ';
    else
        cout << 0 << ' ';
    cout << 1;

    return 0;
}

