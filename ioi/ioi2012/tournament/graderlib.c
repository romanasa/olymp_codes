#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "grader.h"

int _main(GetBestPositionFunction GetBestPosition) {
  int tmp;

  int N, C, R;
  int *K, *S, *E;
  tmp = scanf("%d %d %d", &N, &C, &R);
  assert(tmp == 3);
  K = (int*) malloc((N-1) * sizeof(int));
  S = (int*) malloc(C * sizeof(int));
  E = (int*) malloc(C * sizeof(int));
  int i;
  for (i = 0; i < N-1; i++) {
    tmp = scanf("%d", &K[i]);
    assert(tmp == 1);
  }
  for (i = 0; i < C; i++) {
    tmp = scanf("%d %d", &S[i], &E[i]);
    assert(tmp == 2);
  }

  printf("%d\n", GetBestPosition(N, C, R, K, S, E));

  return 0;

}
