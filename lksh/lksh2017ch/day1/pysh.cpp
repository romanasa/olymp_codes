#ifdef DEBUG
#define _GLIBCXX_DEBUG
#endif
 
//#include <bits/stdc++.h>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <cstdlib>
#include <vector>
#include <cassert>
 
using namespace std;
/*
mt19937 mrand(random_device{} ()); 
 
int rnd(int x) {
  return mrand() % x;
}
*/
 
typedef long double ld;
typedef long long ll;
 
#ifdef DEBUG
#define eprintf(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)
#else
#define eprintf(...) ;
#endif
 
#define pb push_back
#define mp make_pair
#define sz(x) ((int) (x).size())
#define TASK "text"
 
const int inf = (int) 1.01e9;
const ld eps = 1e-9;
const ld pi = acos((ld) -1.0);
 
void precalc() {
}
 
 
const int maxn = (int) 1.5e3 + 10;
int xs[maxn], ys[maxn], cs[maxn];
 
int n;
 
int read() {
  if (scanf("%d", &n) < 1) {
    return 0;
  }
  for (int i = 0; i < n; ++i) {
    scanf("%d%d%d", xs + i, ys + i, cs + i);
  }
  return 1;
}
 
pair<int, int> xsort[maxn];
 
pair<int, long long> a[maxn];
 
void solve() {
  for (int i = 0; i < n; ++i) {
    xsort[i] = mp(xs[i], i);
  }
  sort(xsort, xsort + n);
 
  long long res = -1e18;
  int ans11 = -1, ans12 = -1;
  for (int i1 = 0; i1 < n; ++i1) {
    if (i1 && xsort[i1].first == xsort[i1 - 1].first) {
      continue;
    }
    int cnt = 0;
    for (int i2 = i1; i2 < n; ++i2) {
      int id = xsort[i2].second;
      int y = ys[id], c = cs[id];
      int pos = lower_bound(a, a + cnt, mp(y, -(long long) 1e18)) - a;
      if (pos < cnt && a[pos].first == y) {
        a[pos].second += c;
      } else {
        for (int i = cnt; i > pos; --i) {
          a[i] = a[i - 1];
        }
        a[pos] = mp(y, c);
        ++cnt;
      }
      if (i2 + 1 == n || xsort[i2].first != xsort[i2 + 1].first) {
        long long best = a[0].second;
        for (int i = 1; i < cnt; ++i) {
          const long long &cur = a[i].second;
          best += cur;
          if (res < best) {
            res = best;
            ans11 = xsort[i1].first, ans12 = xsort[i2].first;
          }
          if (best < cur) {
            best = cur;
          }
        }
      }
    }
  }
  {
    bool need = 0;
    int resy = -1;
    for (int i1 = 0; i1 < n; ++i1) {
      int y = ys[i1];
      vector<pair<int, int> > v;
      for (int i = 0; i < n; ++i) {
        if (ys[i] != y) {
          continue;
        }
        v.pb(mp(xs[i], i));
      }
      sort(v.begin(), v.end());
      for (int i = 0; i < sz(v); ++i) {
        if (!i || v[i].first != v[i - 1].first) {
          long long sum = 0;
          for (int j = i; j < sz(v); ++j) {
            sum += cs[v[j].second];
            if (j - i >= 1 && (j == sz(v) - 1 || v[j].first != v[j + 1].first)) {
              if (sum > res) {
                need = 1;
                res = sum;
                resy = y;
                ans11 = v[i].first, ans12 = v[j].first;
              }
            }
          }
        }
      }
    }
    if (need) {
      eprintf("%lld\n", res);
      printf("%d %d\n", ans11, ans12);
      printf("%d %d\n", resy, resy);
      return;
    }
  }
  eprintf("%lld\n", res);
  printf("%d %d\n", ans11, ans12);
  vector<pair<int, int> > v;
  for (int i = 0; i < n; ++i) {
    if (ans11 <= xs[i] && xs[i] <= ans12) {
      v.pb(mp(ys[i], i));
    }
  }
  sort(v.begin(), v.end());
  for (int i = 0; i < sz(v); ++i) {
    if (!i || v[i].first != v[i - 1].first) {
      long long sum = 0;
      for (int j = i; j < sz(v); ++j) {
        sum += cs[v[j].second];
        if (j - i >= 1 && (j == sz(v) - 1 || v[j].first != v[j + 1].first)) {
          if (sum == res) {
            printf("%d %d\n", v[i].first, v[j].first);
            return;
          }
        }
      }
    }
  }
  assert(0);
}
 
int main() {
  precalc();
#ifdef LOCAL
  freopen(TASK ".out", "w", stdout);
  assert(freopen(TASK ".in", "r", stdin));
#else
  freopen("output.txt", "w", stdout);
  assert(freopen("input.txt", "r", stdin));
#endif
 
  while (1) {
    if (!read()) {
      break;
    }
    solve();
#ifdef DEBUG
    eprintf("Time %.2f\n", (double) clock() / CLOCKS_PER_SEC);
#endif
  }
  return 0;
}
