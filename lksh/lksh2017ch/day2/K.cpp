#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

map<char, string> M;

int main() {
#ifdef WIN
    freopen("01.in", "r", stdin);
#endif

    int n;
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        int a, b, c, d, e, f;
        cin >> a >> b >> c >> d >> e >> f;
        int A = b * c - a * d;
        int B = c * f - d * e;

        if (A == 0 && B != 0)
        {
            cout << "?\n";
            continue;
        }

        if (A == 0 && B == 0)
        {
            int m = 1, kol = 0;
            int M, N;
            while (e - a * m > 0)
            {
                if ((e - a * m) % c == 0)
                {
                    kol++;
                    M = m;
                    N = (e - a * m) / c;
                }
                m++;
            }
            if (kol == 1)
            {
                cout << M << ' ' << N << '\n';
                continue;
            }
            else
            {
                cout << "?\n";
                continue;
            }

        }

        if (abs(B) % abs(A) != 0)
        {
            cout << "?\n";
            continue;
        }
        int M = B / A;
        if (M <= 0)
        {
            cout << "?\n";
            continue;
        }

        if ((abs(e - a * M)) % c != 0)
        {
            cout << "?\n";
            continue;
        }
        int N = (e - a * M) / c;
        if (N <= 0)
        {
            cout << "?\n";
            continue;
        }

        cout << M << ' ' << N << '\n';
    }
    return 0;
}

