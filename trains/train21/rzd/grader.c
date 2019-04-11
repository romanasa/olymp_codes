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
#define maxN 310000



static int isRun = 0;

static char secret[maxL + 1];
static int a[maxN + 10];
static int b[maxN + 10];
static int n;
static int m;
static int c;

static int answer[maxN + 10];

int main()
{
  int i;
  if (isRun)
  {
    printf("%s\nSV User tries to hack the system", secret);
    exit(3128);
  }

  assert(gets(secret));

  scanf("%d %d %d",&n,&m,&c);


  for (i = 0; i < m; i++){
      scanf("%d %d",&a[i],&b[i]);
  }

  int ans = solve(n,m,c,a,b, answer);

  printf("%s\n",secret);
  if (ans)
      printf("YES\n");
  else
      printf("NO\n");
  if (ans)
  {
      for (i = 1; i <= n; i ++)
      {
          printf("%d", answer[i]);
          if (i == n)
              printf("\n");
          else
              printf(" ");
      }
  }

  return 0;
}
