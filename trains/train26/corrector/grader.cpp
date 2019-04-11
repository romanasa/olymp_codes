#include <time.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "grader.h"

#ifdef _WIN32
#  define I64 "%I64d"
#else
#  define I64 "%lld"
#endif

#define maxN (int)1e5
#define maxK (int)1e5
#define maxQ (int)1e5
#define maxSumLen (int)1e5

static char secret[999];

static int wn, qn;
static char text[maxN + 1];
static char* words[maxK];
static query_t queries[maxQ];
static long long answer[maxQ];

static int pos = 0;
static char mem[maxK + maxSumLen];

int main()
{
  int i, start = clock();
  assert(scanf("%s", secret) == 1);
  assert(scanf("%s", text) == 1);
  assert(scanf("%d", &wn) == 1);
  for (i = 0; i < wn; i++)
  {
    words[i] = mem + pos;
    scanf("%s", words[i]);
    pos += strlen(words[i]) + 1;
    assert(pos <= maxK + maxSumLen);
  }
  assert(scanf("%d", &qn) == 1);
  for (i = 0; i < qn; i++)
    scanf("%d%d", &queries[i].l, &queries[i].r);

  solve(text, wn, words, qn, queries, answer);

  printf("%s\n", secret);

  for (i = 0; i < qn; i++)
    printf(I64"%c", answer[i], (i + 1 == qn) ? '\n': ' ');
  fprintf(stderr, "time = %.2f\n", (double)(clock() - start) / CLOCKS_PER_SEC);
  return 0;
}
