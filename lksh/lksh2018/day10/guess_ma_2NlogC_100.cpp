// Бинпоиски по горизонтали и по наклонённой прямой
// Наклонённый бинпоиск - только по нужной вертикали, т. е. тоже за NlogC

#include <cstdio>
#include <cassert>
#include <vector>
#include <algorithm>
using namespace std;

#define eprintf(...) fprintf(stderr, __VA_ARGS__)

typedef long long llong;

struct vt
{
    llong x, y;
    vt(llong _x, llong _y)
    {
        x = _x, y = _y;
    }
    friend vt operator +(vt a, vt b)
    {
        return vt(a.x + b.x, a.y + b.y);
    }
    friend vt operator -(vt a, vt b)
    {
        return vt(a.x - b.x, a.y - b.y);
    }
    friend llong operator *(vt a, vt b)
    {
        return a.x * b.x + a.y * b.y;
    }
    friend llong operator ^(vt a, vt b)
    {
        return a.x * b.y - b.x * a.y;
    }
    friend vt operator *(vt a, llong k)
    {
        return vt(a.x * k, a.y * k);
    }
    friend bool operator <(vt a, vt b)
    {
        return (a ^ b) > 0;
    }
};

int n;

pair<int, int> ask(vt a, vt b)
{
    printf("? %d %d %d %d\n", (int)a.x, (int)a.y, (int)b.x, (int)b.y);
    fflush(stdout);
    pair<int, int> ret;
    scanf("%d %d", &ret.first, &ret.second);
    return ret;
}

int mx;

llong get_x(int i)
{
    int l = -mx - 1, r = mx + 1;
    while (r - l > 1)
    {
        int m = (l + r) / 2;
        if (ask(vt(m, 0), vt(m, 1)).second >= n - i)
            l = m;
        else
            r = m;
    }
    return r;
}

llong get_q(int i, llong x)
{
    llong q = 2 * mx + 2;
    llong l = q * x - mx - 1, r = q * x + mx + 1;
    // y = -qx + m
    while (r - l > 1)
    {
        llong m = (l + r) / 2;
        vt a(0, m), b = a + vt(1, -q);
        llong d = m / q;
        a = a + vt(1, -q) * d;
        b = b + vt(1, -q) * d;
        //eprintf("%lld %lld %lld %lld\n", a.x, a.y, b.x, b.y);
        assert(max(max(abs(a.x), abs(a.y)), max(abs(b.x), abs(b.y))) < 5 * mx);
        if (ask(b, a).second >= n - i)
            l = m;
        else
            r = m;
    }
    return r;
}


int main()
{
    scanf("%d %d", &n, &mx);
    vector<vt> V, U;
    for (int i = 0; i < n; i++)
    {
        llong x = get_x(i);
        llong v = get_q(i, x);
        llong q = 2 * mx + 2;
        llong y = -q * x + v;
        //eprintf("found %lld %lld\n", x, y);
        V.push_back(vt(x, y));
    }
    vt O(1e9, 1e9);
    for (int i = 0; i < n; i++)
        if (V[i].y < O.y)
            O = V[i];
    for (int i = 0; i < n; i++)
        if (V[i].x != O.x || V[i].y != O.y)
            U.push_back(V[i] - O);
    sort(U.begin(), U.end());
    U.insert(U.begin(), O);
    for (int i = 1; i < n; i++)
        U[i] = U[i] + O;
    printf("Ready!\n");
    for (int i = 0; i < n; i++)
        printf("%d %d\n", (int)U[i].x, (int)U[i].y);
    return 0;
}

