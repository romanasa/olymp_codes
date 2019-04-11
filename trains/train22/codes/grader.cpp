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

#define SECRET "user"

#define maxN (int)2e5
#define maxK (int)2e5
#define maxQ (int)2e5
#define maxSumLen (int)2e5


static int n;
static int qn;
static char* words[maxK];
static int answer[maxQ+10];

static int pos = 0;
static char mem[maxK + maxSumLen];



int main()
{
  int i, start = clock();
  assert(scanf("%d", &n) == 1);
  for (i = 0; i < n; i++)
  {
    words[i] = mem + pos;
    assert(scanf(" %s", words[i]) == 1);
    pos += strlen(words[i]) + 1;
    assert(pos <= maxK + maxSumLen);
  }
  answer[0] = init(n,words);
  assert(scanf("%d", &qn) == 1);
  for (i = 0; i < qn; i++){
    char c;
    assert(scanf(" %c",&c) == 1);
    if (c == '+'){
       words[n] = mem + pos;
       assert(scanf(" %s", words[n]) == 1);
       pos += strlen(words[n]) + 1;
       assert(pos <= maxK + maxSumLen);
       answer[i+1] = add(words[n]);
       n++;
       continue;
    }
    if (c == '-'){
        int id;
        assert(scanf("%d", &id) == 1);
        assert(0 <= id && id < n);
        answer[i+1] = rem(id);
        continue;
    }
    if (c == '*'){
        int id;
        assert(scanf("%d", &id) == 1);
        assert(0 <= id && id < n);
        answer[i+1] = revert(id);
        continue;
    }
  }

  printf("%s\n", SECRET);

  for (i = 0; i <= qn; i++)
    printf("%d%c", answer[i], (i == qn) ? '\n': ' ');
  fprintf(stderr, "time = %.2f\n", (double)(clock() - start) / CLOCKS_PER_SEC);
  return 0;
}
