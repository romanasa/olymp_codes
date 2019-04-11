/**
 * Author: Sergey Kopeliovich (Burunduk30@gmail.com)
 * Date: 2015.02.20
 * OK, 0.766 sec
 */

#include <bits/stdc++.h>

using namespace std;

#define forn(i, n) for (int i = 0; i < (int)(n); i++)

const int K = 100;
const int N = 1e5 + K;

int n, q, a[N], b[N];

struct T {
  int i, add_all;
  void build() {
    forn(j, K)
      b[i + j] = a[i + j] = a[i + j] + add_all;
    add_all = 0;
    sort(b + i, b + i + K);
  }
  bool get( int x ) {
    x -= add_all;
    auto it = lower_bound(b + i, b + i + K, x);
    return it < b + i + K && *it == x;
  }
};

T t[N / K + 1];

inline int readChar();
int readInt();

int main() {
  #define NAME "fabro"
  assert(freopen(NAME ".in", "r", stdin));
  assert(freopen(NAME ".out", "w", stdout));

  n = readInt();
  q = readInt();
  forn(i, n)
    a[i] = readInt();
  for (int i = 0; i < n; i += K)
    t[i / K].i = i, t[i / K].build();
  while (q--) {
    char type = readChar();
    int l = readInt() - 1;
    int r = readInt();
    int x = readInt();
    int l_i = l / K, r_i = r / K;
    const int L = (l_i + 1) * K, R = r_i * K;
    if (type == '?') {
      bool res = 0;
      while (l < r && l < L)
        res |= (a[l++] == x - t[l_i].add_all);
      while (l < r && r > R)
        res |= (a[--r] == x - t[r_i].add_all);
      for (l_i++; l_i < r_i && !res; l_i++)
        res |= t[l_i].get(x);
      puts(res ? "YES" : "NO");
    } else {
      if (l < L) {
        while (l < r && l < L) 
          a[l++] += x;
        t[l_i].build();
      }        
      if (r > R) {
        while (l < r && r > R)
          a[--r] += x;
        t[r_i].build();
      }
      for (l_i++; l_i < r_i; l_i++)
        t[l_i].add_all += x;
    }
  }
}

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
