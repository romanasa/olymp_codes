#define _CRT_SECURE_NO_DEPRECATE
#pragma comment(linker, "/STACK:50000000")
#include <cstdio>
#include <vector>
#include <cassert>
using namespace std;

int n, ctime;
vector<int> adj[100100];
int in[100100], out[100100], was[100100];

void dfs(int a){
  assert(was[a] == 0);
  was[a] = 1;
  in[a] = ++ctime;
  int i;
  for (i=0; i<adj[a].size(); i++){
    int k = adj[a][i];
    dfs(k);
  }
  out[a] = ctime;
}


int main(){
  freopen("ancestor.in", "r", stdin);
  freopen("ancestor.out", "w", stdout);
  int i, a, b, root=0;
  scanf("%d", &n);
  assert(1<=n && n<=100000);
  for (i=1; i<=n; i++){
    scanf("%d", &a);
    assert(0<=a && a<=n && a != i);
    if (a == 0) root = i;
    else adj[a].push_back(i);
  }
  assert(root > 0);
  dfs(root);
  int m;
  scanf("%d", &m);
  assert(1<=m && m<=100000);
  for (i=1; i<=m; i++){
    scanf("%d%d", &a, &b);
    assert(1<=a && a<=n && 1<=b && b<=n && a!=b);
    printf("%d\n", ((in[a] <= in[b]) && (out[b] <= out[a])));
  }
  return 0;
}
