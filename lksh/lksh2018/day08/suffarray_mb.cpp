#include<cassert>
#include<queue>
#include<cstring>
#include<cstdio>
#include<vector>
#include<string>
#include<set>
#include<map>
#include<cmath>
#include<iostream>
#include<algorithm>

#define eps 1e-12

#define sqr(a) ((a)*(a))
#define mp(a,b) make_pair(a,b) 
#define forn(i,n) for(int i=0;i<(int)n;i++)
#define taskname "suffarray"
#ifdef DEBUG
#define deb(x) cerr<<#x<<'='<<x<<endl
#else
#define deb(x) 
#endif
typedef long long ll;

using namespace std;

const int Text_len=(int)1e5;
char t[Text_len+1];
int p[Text_len];
bool cmp(int a,int b)
{
  return strcmp(t+a,t+b)<0;
}
int main()         
{
  assert(freopen(taskname".in","r",stdin));                         
  assert(freopen(taskname".out","w",stdout));
  assert(gets(t));
  //scanf("%s", t);
  
  int n=strlen(t);
  forn(i,n)
    assert(t[i]>=' ');
  assert(n>0&&n<=Text_len);
  forn(i,n)
    p[i]=i;
  sort(p,p+n,cmp);
//  assert(Leature_text(t));
  forn(i,n)
    printf("%d ",p[i]+1);
 // forn(i,n)
   // puts(t+p[i]);
  return 0;
}

