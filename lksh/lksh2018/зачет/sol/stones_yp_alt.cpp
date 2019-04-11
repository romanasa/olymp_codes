#include <algorithm>
#include <cassert>
#include <cstdio>
#include <iostream>
#include <iomanip>

using namespace std;

typedef long long crd;

const int maxN = 5000;
const crd maxX = 100000000;

struct vec
{
  int x, y;
  vec() {}
  vec( int _x, int _y ): x(_x), y(_y) {}
  vec operator - ( vec b ) { return vec(x - b.x, y - b.y); }
  crd operator ^ ( vec b ) { return (crd)x * b.y - (crd)y * b.x; }
  crd d2() { return (crd)x * x + (crd)y * y; }
};

crd _( crd a ) { return (a > 0) ? a : -a; }
crd sq( vec a, vec b, vec c ) { return _((b - a) ^ (c - a)); }

int n, o[maxN], s[maxN * 2], k;
vec p[maxN], z[maxN * 2];

crd sq( int a, int b, int c ) { return sq(p[s[a]], p[s[b]], p[s[c]]); }

bool lessLex( vec a, vec b )
{
  if (a.x != b.x) return a.x < b.x;
  return a.y < b.y;
}

bool lessAng( int a, int b )
{
  if (((p[a] - p[o[0]]) ^ (p[b] - p[o[0]])) != 0)
    return ((p[a] - p[o[0]]) ^ (p[b] - p[o[0]])) < 0;
  return (p[a] - p[o[0]]).d2() < (p[b] - p[o[0]]).d2();
}

inline crd ss( int a, int b, int c )
{
  return _((z[b] - z[a]) ^ (z[c] - z[a]));
}

int main()
{
  assert(freopen("stones.in", "r", stdin));
  assert(freopen("stones.out", "w", stdout));
  assert(cin >> n);
  assert(4 <= n && n <= maxN);
  for (int i = 0; i < n; i++)
  {
    assert(cin >> p[i].x >> p[i].y);
    assert(-maxX <= p[i].x && p[i].x <= maxX);
    assert(-maxX <= p[i].y && p[i].y <= maxX);
  }

  sort(p, p + n, lessLex);
  for (int i = 1; i < n; i++)
    assert(lessLex(p[i - 1], p[i]));
  for (int i = 0; i < n; i++)
  {
    o[i] = i;
    if (lessLex(p[o[i]], p[o[0]]))
      swap(o[i], o[0]);
  }
  sort(o + 1, o + n, lessAng);
  k = 0;
  for (int i = 0; i < n; s[k++] = o[i++])
    while (k >= 2 && ((p[s[k - 1]] - p[s[k - 2]]) ^ (p[o[i]] - p[s[k - 1]])) >= 0)
      k--;

  crd ans = 0;
  for (int i = 0; i < k; i++)
    s[i + k] = s[i];
  for (int i = 0; i < 2 * k; i++)
    z[i] = p[s[i]];
  if (k == 3)
  {
    for (int i = 0; i < n; i++)
      if (i != s[0] && i != s[1] && i != s[2])
        for (int j = 0; j < k; j++)
          ans = max(ans, sq(p[s[0]], p[s[1]], p[s[2]]) -
                         sq(p[s[j]], p[s[j + 1]], p[i]));
  }
  else
    for (int i = 0; i < (k + 1) / 2; i++)
    {
      int l1 = i, l2 = i, l3 = i, l4 = i;
      while (l3 < i + k)
      {
        l3++;
        crd s132 = ss(l1, l3, l2), t;
        while (l2 < l3 && (l2 < l1 || s132 < (t = ss(l1, l3, l2 + 1))))
          l2++, s132 = t;
        crd s134 = ss(l1, l3, l4);
        while (l4 < l1 + k && (l4 < l3 || s134 < (t = ss(l1, l3, l4 + 1))))
          l4++, s134 = t;
        if (l1 <= l2 && l2 <= l3 && l3 <= l4 && l4 <= l1 + k)
          ans = max(ans, s132 + s134);
      }
    }
  assert(ans > 0);

  cout << ans / 2 << "." << 5 * (ans & 1) << endl;
  return 0;
}
