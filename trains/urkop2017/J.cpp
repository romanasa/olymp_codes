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
int a[1005][1005];
set <int> op;

int main() {
#ifdef WIN
    freopen("01", "r", stdin);
#endif // WIN
    int r, c;
    cin >> r >> c;
    for (int i = 1; i <= r; i++)
        for (int j = 1; j <= c; j++)
            cin >> a[i][j];

    bool fl = true;
    for (int i = 1; i <= r; i++)
        for (int j = 1; j <= c; j++)
        {
            if (a[i][j] != (i - 1) * c + j)
                fl = false;
        }
    if (fl)
    {
        cout << 0;
        return 0;
    }

    bool fl1 = true, fl2 = true;
    for (int i = 1; i <= r; i++)
    {
        for (int j = 1; j <= c; j++)
        {
            if ((a[i][j] - 1) / c + 1 != i)
                fl1 = false;
        }
    }
    for (int j = 1; j <= c; j++)
    {
        for (int i = 1; i <= r; i++)
        {
            if ((a[i][j] - j) % c != 0)
                fl2 = false;
        }
    }
    if (fl1 || fl2)
    {
        cout << 1;
        return 0;
    }

    fl1 = true, fl2 = true;
    for (int i = 1; i <= r; i++)
    {
        op.clear();
        for (int j = 1; j <= c; j++)
        {
            if (op.find(a[i][j] % c) != op.end())
                fl1 = false;
            op.insert(a[i][j] % c);
        }
    }
    op.clear();
    for (int j = 1; j <= c; j++)
    {
        op.clear();
        for (int i = 1; i <= r; i++)
        {
            if (op.find((a[i][j] - 1) / c + 1) != op.end())
                fl2 = false;
            op.insert((a[i][j] - 1) / c + 1);
        }
    }
    if (fl1 || fl2)
    {
        cout << 2;
        return 0;
    }
    cout << 3;
    return 0;
}

