#include <bits/stdc++.h>
using namespace std;
int a[70007];
int main()
{
    freopen("forum.in", "r", stdin);
    freopen("forum.out", "w", stdout);
    int kol1 = 0, kol2 = 0;
    string s, str = "";
    while (cin >> s)
    {
        str = "";
        for (int i = 0; i < (int) s.length(); i++)
            if (s[i] >= 'a' && s[i] <= 'z')
                str += s[i];
            else
            {
                if (str == "tram")
                    kol1++;
                if (str == "trolleybus")
                    kol2++;
                str = "";
            }
        if (str == "tram")
            kol1++;
        if (str == "trolleybus")
            kol2++;
        str = "";
    }
    if (kol1 > kol2)
        cout << "Tram driver";
    else
        if (kol2 > kol1)
            cout << "Trolleybus driver";
        else
            cout << "Bus driver";
    return 0;
}

