/**
 * Author: Sergey Kopeliovich (Burunduk30@gmail.com)
 * Date: 2015.02.27
 */

#include <bits/stdc++.h>

using namespace std;

#define forn(i, n) for (int i = 0; i < (int)(n); i++)
#define STAMP fprintf(stderr, "time = %.2f\n", 1. * clock() / CLOCKS_PER_SEC); 

const int N = 3e5 + 1;	
int n, a[N], l[N], ans[N];
int e = 1, he[N], ne[N], to[N];

inline void addToList( int v, int x ) {
  ne[e] = he[v], to[e] = x, he[v] = e++;
}

int sum[N];

inline void add( int x, int d ) {
  for (x = n - x; x < N; x |= x + 1)
    sum[x] += d;
}

inline int get( int x ) {
  int r = 0;
  for (x = n - x; x >= 0; x &= x + 1, x--)
    r += sum[x];
  return r;
}

inline int readChar();
inline int readInt();              // skip spaces, read signed int
template <class T> inline void writeInt( T x );
inline void writeChar( int x ); // you may use putchar() instead of it
inline void flush();

int main() {
  #define NAME "distinctnum"
  assert(freopen(NAME ".in", "r", stdin));
  assert(freopen(NAME ".out", "w", stdout));

  n = readInt();
  assert(n <= N);
  forn(i, n) 
    a[i] = readInt();
  int q = readInt();
  assert(q <= N);
  forn(i, q) {
    l[i] = readInt();
    addToList(readInt() - 1, i);
  }
  STAMP

  unordered_map<int, int> pos(n);
  pos.rehash(n);
  forn(i, n) { 
    int &r = pos[a[i]];
    if (r)
      add(r, -1);
    add(r = i + 1, +1);
    for (int e = he[i]; e; e = ne[e]) 
      ans[to[e]] = get(l[to[e]]);
  }

  STAMP
  forn(i, q)
    writeInt(ans[i]), writeChar('\n');
  flush();

  STAMP
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

inline int readInt() {
  int x = 0, s = 1, c = readChar();
  if (c == '-')
    s = -1, c = getchar_fast();
  while ('0' <= c && c <= '9')
    x = x * 10 + c - '0', c = getchar_fast();
  return s == 1 ? x : -x;
}

/** Write */

static int write_pos = 0;
static char write_buf[buf_size];

inline void writeChar( int x ) {
  if (write_pos == buf_size)
    fwrite(write_buf, 1, buf_size, stdout), write_pos = 0;
  write_buf[write_pos++] = x;
}

inline void flush() {
  if (write_pos)
    fwrite(write_buf, 1, write_pos, stdout), write_pos = 0;
}

template <class T> 
inline void writeInt( T x ) {
  if (x < 0)
    writeChar('-'), x = -x;

  char s[24];
  int n = 0;
  while (x || !n)
    s[n++] = '0' + x % 10, x /= 10;
  while (n--)
    writeChar(s[n]);
}
