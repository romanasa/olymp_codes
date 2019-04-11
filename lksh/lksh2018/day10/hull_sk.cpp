// Quick Hull algorithm

#ifdef _WIN32
#define LLD "%I64d"
#else
#define LLD "%lld"
#endif


#include <cstdio>
#include <cmath>
#include <cstring>
#include <cassert>

#include <algorithm>

using namespace std;

#define forn(i, n) for (int i = 0; i < (int)(n); i++)
#define mp make_pair

typedef long long ll;

struct pnt 
{
  int x, y;

  pnt() { }
  pnt( int x_, int y_ ) { x = x_, y = y_; }

  pnt operator - ( pnt a ) const { return pnt(x - a.x, y - a.y); }
  ll operator * ( pnt a ) const { return (ll)x * a.y - (ll)y * a.x; }

  bool operator < ( pnt a ) { return mp(x, y) < mp(a.x, a.y); }
  bool operator == ( pnt a ) { return mp(x, y) == mp(a.x, a.y); }
};

const int maxn = 1000002;

int n, rn = 0;
pnt p[maxn], r[maxn];

struct list
{
  int n;
  pnt *p;
};

int cnt = 0;

void Build( pnt a, pnt b, list &l );

void Get( pnt a, pnt b, list &l, list &x )
{
  cnt += l.n;
  x.n = 0;
  forn(i, l.n)
    if ((b - a) * (l.p[i] - a) > 0)
      x.p[x.n++] = l.p[i];
  Build(a, b, x);
}

void Build( pnt a, pnt b, list &l )
{ 
  cnt += l.n;

  ll A = a.y - b.y;
  ll B = b.x - a.x;
  ll C = -(A * a.x + B * a.y);

  int k = 0;
  ll ma1 = 0, ma2 = 0, tmp1, tmp2;
  forn(i, l.n)
    if (mp(ma1, ma2) < mp(tmp1 = A * l.p[i].x + B * l.p[i].y + C, tmp2 = -B * l.p[i].x + A * l.p[i].y))
      ma1 = tmp1, ma2 = tmp2, k = i;

  if (ma1 > 0)
  {
    list x;
    x.p = new pnt[l.n];
    Get(a, l.p[k], l, x);
    Get(l.p[k], b, l, x);
    delete [] x.p;
  }
  else
    r[rn++] = a;
}

int main()
{
  freopen("hull.in", "r", stdin);
  freopen("hull.out", "w", stdout);

  scanf("%d", &n);
  assert(1 <= n && n <= (int)1e5);
  forn(i, n)
  {
    const int M = (int)1e9;
    scanf("%d%d", &p[i].x, &p[i].y);
    assert(-M <= p[i].x && p[i].x <= M);
    assert(-M <= p[i].y && p[i].y <= M);
  }

  int k1 = 0, k2, k3;
  for (k2 = k1 + 1; k2 < n && p[k1] == p[k2]; k2++)
    ;
  for (k3 = k2 + 1; k3 < n && (p[k3] - p[k1]) * (p[k3] - p[k2]) == 0; k3++)
    ;
  assert(k3 < n);

  int mi = 0, ma = 0;
  forn(i, n)
    if (p[i] < p[mi])
      mi = i;
    else if (p[ma] < p[i])
      ma = i;

  list a, b;
  a.n = n, a.p = p, b.p = new pnt[n];
  Get(p[mi], p[ma], a, b);
  Get(p[ma], p[mi], a, b);
  
  long long sq = 0;

  printf("%d\n", rn);
  r[rn] = r[0];
  forn(i, rn) {
    printf("%d %d\n", r[i].x, r[i].y);
    sq += r[i].x * 1LL * r[(i+1)].y - r[i].y * 1LL * r[(i+1)].x;
  }
  if (sq < 0) {
      sq = -sq;
  }
  printf(LLD "." LLD "\n", sq / 2, (sq % 2) * 5);
//  fprintf(stderr, "cnt=%9d n=%7d rn=%7d : %.5lf\n", cnt, n, rn, (double)rn / pow(n, 1.0 / 3));
  return 0;
}
