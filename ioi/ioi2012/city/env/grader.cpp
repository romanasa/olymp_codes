#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
int DistanceSum(int N, int *X, int *Y);

int main() {
  freopen("example.txt", "r", stdin);
  freopen("01", "w", stdout);
  int N, i;
  scanf("%d", &N);

  int *sq_x, *sq_y;
  sq_x = (int*) malloc(N * sizeof(int));
  sq_y = (int*) malloc(N * sizeof(int));

  for (i = 0; i < N; i++) {
    scanf("%d %d", &sq_x[i], &sq_y[i]);
  }

  int ds = DistanceSum(N, sq_x, sq_y);
  printf("%d\n", ds);

  return 0;

}
