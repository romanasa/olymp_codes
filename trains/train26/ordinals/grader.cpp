#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "grader.h"

#define maxN 3000000

static char secret[999];
static char s[maxN + 1];
static char ans[maxN + 1];

int main () {
  int n,i;
  assert (scanf ("%s", secret) == 1);
  assert (scanf ("%s", s) == 1);
  fix(s, ans);
  n = strlen(s);
  n++;
  printf ("%s\n", secret);
  for (i = 0; i < n; i++)
    if (ans[i] != ',' && ans[i] != '{' && ans[i] != '}'){
        printf("PE: symbol with code %d found\n",(int)ans[i]);
        return 0;
    }
  if (ans[n] != 0){
    printf("PE: add more then one sybmol\n");
    return 0;
  }
  puts(ans);      
  return 0;
}
