/**
 * Author: Sergey Kopeliovich (Burunduk30@gmail.com)
 * Date: 2014.10.14
 */

#include <ctime>
#include <cstdio>
#include <cassert>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;

#define size dfasfdasdf
#define forn(i, n) for (int i = 0; i < (int)(n); i++)
#define fill(a, x) memset(a, x, sizeof(a))
#define pb push_back
#define all(a) (a).begin(), (a).end()

/** Begin fast allocation */
const int MAX_MEM = 1e8;
int mpos = 0;
char mem[MAX_MEM];
inline void * operator new ( size_t n ) {
  char *res = mem + mpos;
  mpos += n;
  assert(mpos <= MAX_MEM);
  return (void *)res;
}
inline void operator delete ( void * ) { }
/** End fast allocation */

const int N = 3e4;
const int M = 2e3;
const int K = 1e5;

int n, m, k, a[K], b[K], l[M], r[M];
int pa[M], pb[N];
vector<int> c[M], rc[N];
int cc, u[N];
int L = 0, R = 0, size = 0;

int dfs( int a ) {
  u[a] = cc;
  for (auto b : rc[a]) 
    if (pa[b] == -1 || (u[pa[b]] != cc && dfs(pa[b]))) {
      pa[b] = a, pb[a] = b;
      return 1;
    }
  return 0;
}

int find_change( int b ) {
  u[b] = cc;
  for (int i = l[b]; i < r[b]; i++) {
    int a = c[b][i];
    if (pb[a] == -1 || (u[pb[a]] != cc && find_change(pb[a]))) {
      pa[b] = a, pb[a] = b;
      return 1;
    }
  }
  return 0;
}

void add() {
  cc++;
  while (R < n && size < m) {
    for (auto b : rc[R])
    	  r[b]++;
    if (dfs(R++))
      size++, cc++;
  }
}

template <class T = int> inline T readInt(); 

int main() {
  #define NAME "marriage"
  assert(freopen(NAME ".in", "r", stdin));
  assert(freopen(NAME ".out", "w", stdout));

  n = readInt();
  m = readInt();
  k = readInt();
  forn(i, k) {
    a[i] = readInt() - 1;
    b[i] = readInt() - 1;
    c[b[i]].pb(a[i]);
    rc[a[i]].pb(b[i]);
  }
  forn(i, m)
    sort(all(c[i])), l[i] = r[i] = 0;

  int ans = 0;
  fill(pa, -1), fill(pb, -1);
  add();

  fprintf(stderr, "time = %.2f\n", 1. * clock() / CLOCKS_PER_SEC);

  for (; size == m && L < n; L++) {
    ans += n - R + 1; 
    for (auto b : rc[L])
      l[b]++;
    if (pb[L] != -1) {
      pa[pb[L]] = -1, cc++;
      if (!find_change(pb[L]))
        size--, add();
    }
  }
  printf("%d\n", ans);
  fprintf(stderr, "time = %.2f\n", 1. * clock() / CLOCKS_PER_SEC);
  return 0;
}

/** Read */

static const int buf_size = 4096;

inline int getchar_fast() { // you may use getchar() instead of it
  static char buf[buf_size];
  static int len = 0, pos = 0;
  if (pos == len)
    pos = 0, len = fread(buf, 1, buf_size, stdin);
  if (pos == len)
    return -1;
  return buf[pos++];
}

inline int readChar() {
  int c = getchar_fast();
  while (c <= 32)
    c = getchar_fast();
  return c;
}

template <class T>
inline T readInt() {
  int s = 1, c = readChar();
  T x = 0;
  if (c == '-')
    s = -1, c = getchar_fast();
  while ('0' <= c && c <= '9')
    x = x * 10 + c - '0', c = getchar_fast();
  return s == 1 ? x : -x;
}
