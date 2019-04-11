/**
 * Author: Sergey Kopeliovich (Burunduk30@gmail.com)
 */

#include <bits/stdc++.h>

using namespace std;

const int K = 18, N = 2e5 + 1;

int link[N], p[N][K], die[N], dep[N];

int get( int v ) {
  return !die[v] ? v : (link[v] = get(link[v]));
}

void jump( int &v, int d ) {
  for (int k = 0; k < K; k++)
    if (d & (1 << k))
      v = p[v][k];
}

int lca( int a, int b ) {
  jump(dep[a] > dep[b] ? a : b, abs(dep[a] - dep[b])); 
  for (int k = K - 1; k >= 0; k--)
    if (p[a][k] != p[b][k])
      a = p[a][k], b = p[b][k];
  return a == b ? a : p[a][0];
}

int main() {
  #define NAME "carno"
  assert(freopen(NAME ".in", "r", stdin));
  assert(freopen(NAME ".out", "w", stdout));
  ios_base::sync_with_stdio(0), cin.tie(0);

  int n = 1, m, a, b;
  char t;
  cin >> m;
  while (m--) {
    cin >> t >> a, a--;
    if (t == '?') {
      cin >> b, b--;
      cout << get(lca(a, b)) + 1 << "\n";
    } else if (t == '+') {
      dep[n] = dep[a] + 1;
      link[n] = p[n][0] = a;
      for (int k = 0; k + 1 < K; k++)
        p[n][k + 1] = p[p[n][k]][k];
      n++;
    }
    else 
      die[a] = 1;
  }
  return 0;
}
