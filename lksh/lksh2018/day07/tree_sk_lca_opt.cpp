/**
 * Author: Sergey Kopeliovich (Burunduk30@gmail.com)
 * OK, O(nlogn), 0.630 sec, 56 mb
 * LCA in O(logn) and solution in O(n * LCA)
 */

#include <cstdio>
#include <cstring>

#define forn(i, n) for (int i = 0; i < (int)(n); i++)

const int maxn = (int)1e6 + 1;

int last[maxn], P[maxn];
int n, root, p[maxn], x[maxn], sum[maxn];
int e = 1, ne[maxn], he[maxn], to[maxn];

inline int Get( int v ) {
  return (P[v] == v ? v : (P[v] = Get(P[v])));
}

void dfs( int v ) {
  int &L = last[x[v]];
  if (L != -1)
    sum[Get(L)]--;
  L = v;
  for (int i = he[v]; i; i = ne[i])
    dfs(to[i]), sum[v] += sum[to[i]];
  P[v] = p[v]; // join
}

inline int Read() {
  int c = getchar(), x = 0;
  while (c <= 32)
    c = getchar();
  while ('0' <= c && c <= '9')
    x = x * 10 + c - '0', c = getchar();
  return x;
}

inline void Write( int x ) {
  char s[24];
  int n = 0;
  while (x || !n)
    s[n++] = '0' + x % 10, x /= 10;
  while (n--)
    putchar(s[n]);
}

int main() {
  freopen("tree.in", "r", stdin);
  freopen("tree.out", "w", stdout);

  memset(last, -1, sizeof(last));
  n = Read();
  forn(i, n) {
    p[i] = Read() - 1;
    x[i] = Read() - 1;
    sum[i] = 1, P[i] = i;
    if (p[i] == -1)
      root = i;
    else
      ne[e] = he[p[i]], to[e] = i, he[p[i]] = e++;
  }
  dfs(root);
  forn(i, n)
    Write(sum[i]), putchar(' ');
  return 0;
}
