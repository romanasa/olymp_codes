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
static int w[maxN + 10];
static int n;
static int maxW;

int main()
{
  int i;
  if (isRun)
  {
    printf("%s\nSV User tries to hack the system", secret);
    exit(3128);
  }

  assert(gets(secret));

  scanf("%d %d",&n,&maxW);


  for (i = 0; i < n-1; i++){
      scanf("%d %d %d",&a[i],&b[i],&w[i]);
  }

  int res = calculate(n,maxW,a,b,w);

  printf("%s\n%d\n",secret,res);

  return 0;
}
