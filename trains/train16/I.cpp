#include <bits/stdc++.h>
using namespace std;
int a[1000005];
int main()
{
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n;
    long long kol = 0;
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
        if (a[i] < 0)
            kol++;
    }
    long long ans = 0;
    for (int i = 1; i <= n; i++)
        if (a[i] >= 0)
            ans += kol;
        else
            ans += kol - 1;
    cout << ans;
}
