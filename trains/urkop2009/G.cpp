#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

string a[105][5], str[5];
int kol[105];


int main() {
#ifdef WIN
    freopen("01", "r", stdin);
#else
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif // WIN
    int n, m;
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> kol[i];
        for (int j = 1; j <= kol[i]; j++)
            cin >> a[i][j];
    }

    int X, Y, ans = -1;
    string name;
    cin >> X >> Y;
    cin >> m;
    for (int i = 1; i <= m; i++)
    {
        string s;
        int Z;
        cin >> s >> Z;
        str[1] = "Efremov", str[2] = "Kantorov", str[3] = s;
        sort(str + 1, str + 4);

        bool fl = true;
        for (int j = 1; j <= n; j++)
        {
            if (kol[j] < 3)
                continue;
            int k = 1;
            for (int z = 1; z <= 3; z++, k++)
                if (a[j][z] != str[z])
                    break;
            if (k == 4)
            {
                fl = false;
                break;
            }
        }
        if (fl)
        {
            if (ans < X + Y + Z)
            {
                ans = X + Y + Z;
                name = s;
                continue;
            }
        }
        else
        {
            bool f = true;
            for (int j = 1; j <= n; j++)
            {
                if (kol[j] != 2)
                    continue;
                if ((a[j][1] == s || a[j][1] == "Kantorov") && (a[j][2] == s || a[j][2] == "Kantorov"))
                {
                    f = false;
                    break;
                }
            }
            if (f)
            {
                if (ans < Y + Z)
                {
                    ans = Y + Z;
                    name = s;
                }
            }
        }
    }

    if (ans == -1)
    {
        cout << "Fail";
    }
    else
    {
        cout << "Win\n" << name;
    }
    return 0;
}

