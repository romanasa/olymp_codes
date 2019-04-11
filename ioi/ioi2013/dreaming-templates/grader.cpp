#include <stdio.h>
#include <stdlib.h>
#include "grader.h"

#define MAX_N 100000

int A[MAX_N];
int B[MAX_N];
int T[MAX_N];

int main() {
	int N, M, L, i;
	int res;

	res = scanf("%d%d%d", &N, &M, &L);
	for (i = 0; i < M; i++)
		res = scanf("%d%d%d", &A[i], &B[i], &T[i]);

	int answer = travelTime(N, M, L, A, B, T);
	printf("%d\n", answer);

	return 0;
}
