#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef WIN32
#define INT64 "%I64d"
#else
#define INT64 "%lld"
#endif

#include "grader.h"

#define MAXBUF (256)
#define MINT (1)
#define MAXT (1000)
#define MINN (1)
#define MAXN (35)
#define MINK (1)
#define MAXK (4000000000000000000LL)

static int isRun = 0;

static char secret [MAXBUF];
static int n;
static int64_t k;

static int answer [MAXN * 2 + 1];

int main (void)
{
 int test, tests;
 int i;

 if (isRun)
 {
  printf ("%s SV recursive call of main", secret);
  exit (123);
 }
 isRun = 1;
 scanf ("%128s", secret);
 printf ("%s\n", secret);

 // read the number of test cases
 scanf (" %d", &tests);
 assert (MINT <= tests && tests <= MAXT);

 for (test = 0; test < tests; test++)
 {
  // read n and k
  scanf (" %d " INT64, &n, &k);
  assert (MINN <= n && n <= MAXN);
  assert (MINK <= k && k <= MAXK);
  memset (answer, 255, sizeof (answer));
  // call solution
  solve (n, k, answer);
  // output the answer
  for (i = 1; i <= n + n; i++)
   printf ("%d%c", answer[i], "\n "[i < n + n]);
 }
 
// printf ("%s OK, %d tests\n", secret, tests);

 isRun = 0;
 return 0;
}
