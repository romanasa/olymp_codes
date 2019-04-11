#include <bits/stdc++.h>
#define ll long long
#define mp make_pair
#define pb push_back
#define X first
#define Y second
#define pii pair<int, int>

using namespace std;

int solve(int n);

const int MAXN = (int)1e5 + 200;

int a[MAXN], color[MAXN], head[MAXN], new_a[MAXN], new_color[MAXN], a_r[MAXN], s[MAXN];
pii mas[MAXN];

int main()
{
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    #ifdef DEBUG
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #endif // DEBUG
    int n;
    while (cin >> n)
    {
        if (n == 0)
            return 0;
        solve(n);
    }
    return 0;
}

int solve(int n)
{
    int k = 1;
    for (int i = 0; i < n; i++)
    {
        cin >> mas[i].X;
        s[i] = mas[i].X;
        mas[i].Y = i;
    }
    sort(mas, mas + n);
    for (int i = 0; i < n; i++)
        a[i] = mas[i].Y;
    color[a[0]] = 0;
    for (int i = 1; i < n; i++)
    {
        if (mas[i].X == mas[i - 1].X)
            color[a[i]] = color[a[i - 1]];
        else
        {
            color[a[i]] = color[a[i - 1]] + 1;
            head[color[a[i]]] = i;
        }
    }
    while (k < n)
    {
        for (int i = 0; i < n; i++)
        {
            int p = (a[i] - k + n) % n;
            new_a[head[color[p]]++] = p;
        }
        new_color[new_a[0]] = 0;
        head[0] = 0;
        for (int i = 1; i < n; i++)
        {
            bool f = (color[new_a[i]] == color[new_a[i - 1]]);
            f = f && (color[(new_a[i] + k) % n] == color[(new_a[i - 1] + k) % n]);
            if (f)
                new_color[new_a[i]] = new_color[new_a[i - 1]];
            else
            {
                new_color[new_a[i]] = new_color[new_a[i - 1]] + 1;
                head[new_color[new_a[i]]] = i;
            }
        }
        for (int i = 0; i < n; i++)
        {
            color[i] = new_color[i];
            a[i] = new_a[i];
        }
        k *= 2;
    }
    for (int i = 0; i < n; i++)
        a_r[a[i]] = i;
    ll ans = 0;
    ll cur = 0;
    for (int i = 1; i < n; i++)
    {
        while (s[(i + cur) % n] == s[(cur + a[a_r[i] + 1]) % n] && cur < n)
               cur++;
               
        cout << i << " = " << cur << "\n";
        ans += cur;
        if (cur > 0)
            cur--;
    }
    cout << ans << endl;
    return 0;
}