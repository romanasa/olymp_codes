#include <vector>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <cassert>
#define pb push_back

using namespace std;

bool a[3][11000];
int n;

int g[11000][3][3];

int bad(int x,int l,int cnt){
    int res = 0;
    for (int i = l; i < l+cnt; i++)
        if (i >= 0 && i < n + (x%2) && a[x][i])
            res++;
    return res;
}


void init(){
    memset(g,-1,sizeof(g));
}



inline int base(int len,int lf,int rg){
    if (len <= 0) return -2;
    if (len >= 3) return -1;

    if (lf == 2) lf = 2 - lf, rg = 2 - rg;
    if (lf == 0 && rg == 1 && len == 2) return -2;
    if (lf == 0 && rg == 2) return -1;
    if (len <= 1) return -2;
    return -1;
}


int used[11000],usedptr;

int grundy(int len,int lf,int rg){
    /*if (lf == 1){
        swap(lf,rg);
        len+= 1 - (lf==1);
    }*/
    if (lf == 2) lf = 2 - lf, rg = 2 - rg;

    if (g[len][lf][rg] != -1)
        return g[len][lf][rg];

    int temp = base(len,lf,rg);
    if (temp == -2)
        return g[len][lf][rg] = -2;

    vector<int> v ;

    for (int i = 1; i < len; i++)
        for (int j = 0; j < 3; j++){
            int a = grundy(i,lf,j);
            int b = grundy(len-i,j,rg);
            if (a == -2 || b == -2)
                continue;
            v.pb(a^b);;
        }
    ++usedptr;

    for (int i = 0; i < (int)v.size(); i++)
        used[v[i]] = usedptr;

    for (int i = 0; ; i++)
        if (used[i] != usedptr) {
            return g[len][lf][rg] = i;
        }
    assert(false);
}

int get(int& _lf,int& _lpos,int rg,int rpos){
    int lf = _lf, lpos = _lpos;
    _lf = rg, _lpos = rpos;
    return grundy(rpos - lpos,lf,rg);
}


int _solve(char* _up,char* _mid, char* _low){
   n = strlen(_up);
   memset(a[0],0,sizeof(bool)*(n+10));
   memset(a[1],0,sizeof(bool)*(n+10));
   memset(a[2],0,sizeof(bool)*(n+10));

   if (n == 1){
      int cnt = (_up[0] == '#') + (_mid[0] == '#') + (_mid[1] == '#') + (_low[0] == '#');
      if (cnt == 0)
        return 1;
      if (cnt == 1 && ((_up[0] == '#') || (_low[0] == '#')))
        return 0;
      if (cnt == 1)
        return 1;
      if (cnt == 3)
        return 1;
      if (_mid[0] == '#' && _mid[1] == '#')
        return 0;
      return 1;
   }

   for (int i = 0; i < n; i++){
      a[0][i] = (_up[i] == '#');
      a[1][i] = (_mid[i] == '#');
      a[2][i] = (_low[i] == '#');
   }
   a[1][n] = (_mid[n] == '#');

   int lf = 1;
   int lpos = -2;

   int g = 0;

   a[0][n] = a[2][n] = 0;

   for (int i = 0; i < n+1; i++)
       for (int j = 0; j < 3; j++)
          if (a[j][i]){
            int t = get(lf,lpos,j,i);
            if (t == -2)
               return 1;
            g ^= t;
          }

   int t = get(lf,lpos,1,n+2);
   g ^= t;
   return !!g;
}

int solve(int,char* _up,char* _mid,char* _low){
    return 2 - _solve(_up,_mid,_low);
}
