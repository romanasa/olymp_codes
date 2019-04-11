#include <cassert>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

#if (defined(WIN32) || !defined(__GNUC__))
#  define I64 "%I64d"
#else
#  define I64 "%Ld"
#endif

#define forn(i, n) for (int i = 0; i < (int)(n); i++)

typedef vector <int> vi;
typedef long long ll;

#define maxn 100010
#define maxd 17

int n, m, bn[2 * maxn];
vi c[maxn];
int tt = 0, t[maxn], pos[maxn];
int an = 0, a[maxn * 2], av[maxn * 2];
int x, y, z, a1, a2;
int f[maxn * 2][maxd + 1];

void dfs( int v, int pr )
{
  t[v] = tt++;
  pos[v] = an, av[t[v]] = v, a[an++] = t[v];
  forn(i, c[v].size())
    if (c[v][i] != pr)
      dfs(c[v][i], v), av[an] = v, a[an++] = t[v];
}

int ans = 0;
ll sum = 0;

int Get( int l, int r )
{
  if (l > r)
    swap(l, r);

  int i = bn[r - l + 1] - 1;
  return min(f[l][i], f[r - (1 << i) + 1][i]);
}             

void Solve( int v, int u )
{
  sum += (ans = av[Get(pos[v], pos[u])]);
}

#define CHECK(x, l, r) assert((l) <= (x) && (x) <= (r))

int main()
{
  freopen("lca2.in", "r", stdin);
  freopen("lca2.out", "w", stdout);

  scanf("%d%d", &n, &m);
  CHECK(n, 1, 100000);
  CHECK(m, 1, 10000000);

  for (int i = 1; i < n; i++)
  {
    int pr;
    scanf("%d", &pr);
    CHECK(pr, 0, n - 1);
    c[pr].push_back(i);
  }

  memset(t, -1, sizeof(t));
  dfs(0, -1);
  forn(i, n)
    assert(t[i] != -1);

  bn[0] = 0;
  for (int i = 1; i <= an + 1; i++)
    bn[i] = bn[i >> 1] + 1;

  fprintf(stderr, "Calculate F\n");

  forn(i, an)
    f[i][0] = a[i];
  for (int j = 1; j <= maxd; j++)
    for (int i = 0; i + (1 << j) <= an; i++)
      f[i][j] = min(f[i][j - 1], f[i + (1 << (j - 1))][j - 1]);

  fprintf(stderr, "Process queries\n");

  assert(scanf("%d%d%d%d%d", &a2, &a1, &x, &y, &z) == 5);

  CHECK(a2, 0, n - 1);
  CHECK(a1, 0, n - 1);
  CHECK(x, 0, (int)1e9);
  CHECK(y, 0, (int)1e9);
  CHECK(z, 0, (int)1e9);

  while (m--)
  {
    Solve((a2 + ans) % n, a1);
    forn(w, 2)
    {
      int a0 = ((ll)x * a2 + (ll)y * a1 + z) % n;
      a2 = a1, a1 = a0;
    }
  }

  printf(I64 "\n", sum);
  return 0;
}
