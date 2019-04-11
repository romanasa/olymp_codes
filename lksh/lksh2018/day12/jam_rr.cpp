#pragma comment(linker, "/STACK:64000000")
#include <algorithm>
#include <memory.h>
#include <cstdio>
#include <iostream>
#include <cmath>
#include <string>
#include <cassert>
#include <map>
#include <set>
#include <vector>
#include <queue>

using namespace std;
#define prev privet1
#define next privet2
#define y1 privet3
#define rank privet4
#define left privet5
#define right privet6
#define y0 privet7

const double pi = 3.141592653589793238;
const int maxn = 100333, sz = 450;


int n, i, j, ans[maxn], tmp, l[maxn], r[maxn], x[maxn], y[maxn], k, num[maxn], m;
long long a[maxn], b[maxn], sum_x[maxn], sum_y[maxn], sub[maxn];

void do_lazy_update()
{
    int i, j;
    for (i = 1; i <= k; i++)
    {
        sum_x[l[i]] += x[i];
        sum_x[r[i] + 1] -= x[i];
        sum_y[l[i] + 1] += y[i];
        sum_y[r[i] + 1] -= y[i];
        sub[r[i] + 1] += (long long) y[i] * (r[i] - l[i]);
    }
    long long add = 0, initial_value;
    for (i = 1; i <= n; i++)
    {
        sum_x[i] += sum_x[i - 1];
        initial_value = a[i];
        a[i] += sum_x[i];
        sum_y[i] += sum_y[i - 1];
        add = add + sum_y[i] - sub[i];
        a[i] += add;
        if (ans[i] == -1 && a[i] >= b[i])
        {
            long long value = initial_value;
            for (j = 1; j <= k; j++)
            {
                if (l[j] > i || r[j] < i) continue;
                value += x[j];
                value += (long long) y[j] * (i - l[j]);
                if (value >= b[i]) 
                {
                    ans[i] = num[j];
                    break;
                }
            }
        }
        sum_x[i - 1] = sum_y[i - 1] = sub[i - 1] = 0;
    }
    sum_x[n] = sum_y[n] = sub[n] = 0;
    k = 0;
}

int main()
{
    freopen("jam.in", "r", stdin);
    freopen("jam.out", "w", stdout);
    scanf("%d", &n);
    for (i = 1; i <= n; i++)
    {
        scanf("%d", &tmp);
        a[i] = tmp;
    }
    for (i = 1; i <= n; i++)
    {
        scanf("%d", &tmp);
        b[i] = tmp;
        if (a[i] >= b[i]) ans[i] = 0;
        else ans[i] = -1;
    }
    scanf("%d", &m);
    k = 0;
    for (i = 1; i <= m; i++)
    {
        k++;
        scanf("%d%d%d%d", &l[k], &r[k], &x[k], &y[k]);
        num[k] = i;
        if (k == sz) do_lazy_update();
    }
    if (k > 0) do_lazy_update();
    for (i = 1; i < n; i++)
        printf("%d ", ans[i]);
    printf("%d\n", ans[n]);
}
