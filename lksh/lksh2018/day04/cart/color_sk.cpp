/**
 * Author: Sergey Kopeliovich (Burunduk30@gmail.com)
 * Date: 2014.11.11
 *
 * IT'S WRONG SOLUTION TO 2-SAT!!! IT PASSES ALL TESTS, BUT IT'S WRONG
 */

#include <bits/stdc++.h>

using namespace std;

#define forn(i, n) for (int i = 0; i < (int)(n); i++)
#define fill(a, x) memset(a, x, sizeof(a))

const int N = 1000;
const int VN = 2 * N;
const int M = 20000;
const int EN = 4 * M;

char s[N + 1];
const char *colors = "RGB";
int n, m, u[VN], color[N], a[M], b[M];
vector<int> topsort, c[VN];

inline void dfs( int v ) {
  if (u[v])
    return;
  u[v] = 1;
  for (int x : c[v])
    dfs(x);
  topsort.push_back(v);
}

void addEdge( int i, int xi, int j, int xj ) {
  c[i * 2 + xi].push_back(j * 2 + xj);
}

void deny( int i, int xi, int j, int xj ) {
  addEdge(i, xi, j, !xj);
  addEdge(j, xj, i, !xi);
}

int main() {
  #define NAME "color"
  //assert(freopen(NAME ".in", "r", stdin));
  //assert(freopen(NAME ".out", "w", stdout));

  scanf("%d%d ", &n, &m);
  gets(s);
  forn(i, n)
    color[i] = strchr(colors, s[i]) - colors;
  forn(i, m) {
    scanf("%d%d", &a[i], &b[i]), a[i]--, b[i]--;
    forn(xa, 2)
      forn(xb, 2) 
        if ((color[a[i]] + xa) % 3 == (color[b[i]] + xb) % 3)
          deny(a[i], xa, b[i], xb);
  }
  fill(u, 0);
  forn(i, 2 * n)
    dfs(i);
  fill(u, -1);
  for (int v : topsort) 
    if (u[v >> 1] == -1) 
      u[v >> 1] = v & 1;
  forn(i, m)
    if ((color[a[i]] + u[a[i]]) % 3 == (color[b[i]] + u[b[i]]) % 3) {
      puts("Impossible");
      return 0;
    }      
  forn(i, n)
    putchar(colors[(color[i] + u[i] + 1) % 3]);
  return 0;
}
