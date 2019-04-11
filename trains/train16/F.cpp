#include <bits/stdc++.h>

using namespace std;
int tek[1005], pl[1005], num[1005];

int main() {
    int n, k;
    cin >> n >> k;
    for (int i = 1; i <= n; i++)
    {
        tek[i] = i;
        pl[i] = i;
        num[i] = i;
    }

    for (int i = 1; i <= k; i++)
    {
        int a, u, pr;
        cin >> a;
        for (int j = 1; j <= n; j++)
            if (tek[j] == a)
            {
                u = j;
                break;
            }

        if (u == 1)
            pr = n;
        else
            pr = u - 1;

        int b = tek[pr];

        if (num[a] == num[b] + 1)
        {
            swap(pl[num[a]], pl[num[b]]);
            swap(num[a], num[b]);
        }

        swap(tek[u], tek[pr]);
    }

    if (n < 6)
    {
        for (int i = 1; i <= n; i++)
            cout << pl[i] << ' ';
    }
    else
    {
        for (int i = 1; i <= 6; i++)
            cout << pl[i] << ' ';
    }
    return 0;
}
