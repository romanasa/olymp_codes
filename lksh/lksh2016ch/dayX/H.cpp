#include <bits/stdc++.h>
 
using namespace std;
 
long long a[100007];
 
int main()
{
    int n, p;
    cin >> n >> p;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    sort(a + 1, a + n + 1);
    long long ans = 0;
    for (int i = 1; i <= n - p + 1; i++)
        ans += a[i];
    for (int i = 2; i <= p; i++)
        ans += min(a[n - p + i], ans / (i - 1) + 1);
    cout << ans;
    return 0;
}