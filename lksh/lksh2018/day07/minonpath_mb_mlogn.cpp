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
#define taskname "minonpath"
#ifdef DEBUG
#define deb(x) cerr<<#x<<'='<<x<<endl
#else
#define deb(x) 
#endif
typedef long long ll;

using namespace std;

const int N=50000;
int deg[N],p[30][N];
int upcost[30][N];
const int maxlog=18;
int up(int v,int t,int &mn)
{
  for(int i=0;i<=maxlog;i++)
    if(t>>i&1)
    {
      mn=min(mn,upcost[i][v]);
      v=p[i][v];
    }
  return v;
}
int main()         
{
  assert(freopen(taskname".in","r",stdin));                         
  assert(freopen(taskname".out","w",stdout));
  int n,m;
  scanf("%d",&n);
  assert(n>0&&n<=N);
  forn(i,n-1)
  {
    #define check(v) assert(0 <= (v) && (v) < n)
    scanf("%d %d ",&p[0][i+1],&upcost[0][i+1]);
    p[0][i+1]--;
    deg[i+1]=deg[p[0][i+1]]+1;
    check(p[0][i+1]);
  }
  for(int k=1;k<=maxlog;k++)
    forn(i,n)
    {
      p[k][i]=p[k-1][p[k-1][i]];
      upcost[k][i] = min(upcost[k-1][i],upcost[k-1][p[k-1][i]]);
     
    }
  scanf("%d",&m);
  assert(m>0&&m<=N);
  forn(i,m)
  {
    int a,b;
    scanf("%d %d",&a,&b);
    a--,b--;
    int ans=1<<30;
    check(a),check(b);
    if(deg[a] > deg[b])
      a = up(a,deg[a]-deg[b],ans);
    else
      b = up(b,deg[b]-deg[a],ans);
    for (int k = maxlog; k >= 0; k--)
      if (p[k][a] != p[k][b])
      {
        ans = min(ans, min(upcost[k][a],upcost[k][b]) );
        a = p[k][a];
        b = p[k][b];
      }
    if (a != b)
    {
       ans = min(ans,min(upcost[0][a],upcost[0][b]));
       a = p[0][a], b = p[0][b];
    }
    printf("%d\n",ans == 1<<30 ? 0:ans);      
  }  
  return 0;
}

