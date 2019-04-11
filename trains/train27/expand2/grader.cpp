#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#ifdef WIN32
# define LL "%I64d"
#else
# define LL "%lld"
#endif

#include "grader.h"

#define maxL 20
#define maxn 100100


static int isRun = 0;
                                         
#define SECRET "user"

static char s[maxn];
static char res[maxn];
static request_t t[maxn]; 
static int m;

int main()
{
  int i;
  if (isRun)
  {
    printf("%s\nSV User tries to hack the system", SECRET);
    exit(3128);
  }

  assert(scanf("%s\n",s) == 1);
  assert(scanf("%d\n", &m) == 1);
  for (i = 0; i < m; i ++)
  assert(scanf("%c %d\n", &t[i].c, &t[i].cnt) == 2);
  solve(s, m, t, res);
  printf("%s\n",SECRET);
  printf("%s\n", res);
  return 0;
}
