#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SECRET "user"

#include "grader.h"

#define MIN_T (1)
#define MAX_T (10)
#define MIN_N (1)
#define MAX_N (10000)

static int isRun = 0;

static char top [MAX_N + 1], middle [MAX_N + 2], bottom [MAX_N + 1];
static int n, answer;

int main (void)
{
 int test, tests;

 if (isRun)
 {
  printf ("%s SV recursive call of main", SECRET);
  exit (123);
 }
 isRun = 1;

 // call initialization
 init ();

 // read the number of test cases
 scanf (" %d", &tests);
 assert (MIN_T <= tests && tests <= MAX_T);

 for (test = 0; test < tests; test++)
 {
  // read n and three strings
  scanf (" %d", &n);
  assert (MIN_N <= n && n <= MAX_N);
  scanf (" %s", top);
  assert ((int) strlen (top) == n);
  scanf (" %s", middle);
  assert ((int) strlen (middle) == n + 1);
  scanf (" %s", bottom);
  assert ((int) strlen (bottom) == n);

  // call solution
  answer = solve (n, top, middle, bottom);

  // output the answer
  printf ("%s ", SECRET);
  if (answer == FIRST)
   printf ("FIRST\n");
  else if (answer == SECOND)
   printf ("SECOND\n");
  else
   printf ("ERROR\n");
 }
 
 isRun = 0;
 return 0;
}
