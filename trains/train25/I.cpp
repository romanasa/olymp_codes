#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define TASK "sochi"
int a[100005], used[100005];

int main() {
#ifdef WIN
    freopen("01", "r", stdin);
#else
    freopen(TASK".in", "r", stdin);
    freopen(TASK".out", "w", stdout);
#endif // WIN
    int n, d;
    cin >> n >> d;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    sort(a + 1, a + n + 1);
    int ans = a[n];
    if (n >= 2 && a[n] >= d && a[n - 1] >= d)
        ans = max(ans, a[n] - d + a[n - 1] - d);

    int uk = n + 1;
    while (uk - 1 > 0 && a[uk - 1] >= 3 * d)
    {
        uk--;
        used[uk] = 1;
    }
    if (uk - 1 > 0 && a[uk - 1] >= d) used[uk - 1] = -1;
    if (uk - 2 > 0 && a[uk - 2] >= d) used[uk - 2] = -1;

    if (n >= 2)
    {
        int tek = a[n] - d + a[n - 1] - d;
        for (int i = n - 2; i > 0; i--)
        {
            if (used[i] == 0) break;
            tek = tek + a[i] - 2 * d;
            ans = max(ans, tek);
        }
    }
    cout << ans;
    return 0;
}

