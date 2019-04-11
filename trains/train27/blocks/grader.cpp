#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SECRET "user"

#include "grader.h"

#define maxN 100000

static int isRun = 0;

static int i, k, n, m, a[maxN], b[maxN], t[maxN];

int main (void) {
  if (isRun) {
    printf ("%s SV recursive call of main", SECRET);
    exit (-1);
  }
  isRun = 1;

  assert (scanf ("%d%d", &n, &m) == 2);
  assert (1 <= n && n <= maxN);
  for (i = 0; i < m; ++i) {
    assert (scanf ("%d%d%d", &t[i], &a[i], &b[i]) == 3);
  }

  init(n, m, t, a, b);

  assert (scanf ("%d", &k) == 1);
  while (k--) {
    char type; 
    assert (scanf(" %c", &type) == 1);
    if (type == '?') {
      int t1, t2, a;
      assert (scanf ("%d%d%d", &t1, &t2, &a) == 3);
      printf("%s %d\n", SECRET, get(t1, t2, a));
    } else {
      int t, a, b;
      assert (scanf ("%d%d%d", &t, &a, &b) == 3);
      add(t, a, b);
    }
  }
  puts(SECRET);

  isRun = 0;
  return 0;
}
