/* Grader program for the task Treasure Hunt
 * Reads from the standard input a positive integer q and then
 * q lines of the form:
 *
 * "p a l" (representing "path a l")
 * "d a b" (representing "dig a b")
 *
 * It calls the corresponding procedures of the graded program and
 * writes the results of the "dig" calls to the standard output. */

#include <cstdio>
#include "treinc.h"

int main()
{
  int num_calls;
  scanf("%d", &num_calls);
  for (int i = 1; i <= num_calls; i++)
  {
    char call[2];
    int a, b;
    scanf("%s%d%d", call, &a, &b);
    if (call[0] == 'i')
      init();
    else if (call[0] == 'p')
      path(a, b);
    else
      printf("%d\n", dig(a, b));
  }
  return 0;
}
