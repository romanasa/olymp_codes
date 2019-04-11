#include <bits/stdc++.h>
#define ll long long
  
using namespace std;
  
int P[3];
  
struct box { 
    int a, b, c, ind;
    box() {}
    box(int a, int b, int c, int ind) : a(a), b(b), c(c), ind(ind) {}
};
box T[207];
//unordered_map<ll, int> H(1234567);
      
const int BB = (1 << 21) - 1;
 
struct mp{
    pair<ll, int> T[BB + 1];
     
    mp() {
        fill(T, T + BB + 1, make_pair(-1, -1));
    }
     
    inline void add(ll h, int v) {
        int x = h & BB;
        for (; T[x].first != -1; x = (x + 1) & BB) {
            if (T[x].first == h) 
                break;
        }
        T[x].first = h;
        T[x].second = v;
    }
     
    inline int get(ll h) {
        int x = h & BB;
        for (; T[x].first != -1; x = (x + 1) & BB) {
            if (T[x].first == h)
                return T[x].second;
        }
    }
     
} H;
 
int best = 0;
int n;
  
const int dd = 181;
 
int used, c;
unsigned char ind[dd], X[dd], Y[dd];
 
int beg[dd], fin[dd];
int nxt[dd * dd];
int W[dd * dd];
int nv = dd;
 
int TT[dd];
 
void dfs(int v) {
    used |= (1 << ind[v]);
    c += T[v].c;
      
    for (int i = beg[v]; i != fin[v]; i = nxt[i]) {
        if (!((used >> ind[W[i]]) & 1))
            dfs(W[i]);
    }
}
  
ll B[3], K[3];
 
int cnt = 0;
bool is_tl = false;
 
inline void tl() {
    if (++cnt == 1000)
        is_tl |= clock() > 0.48 * CLOCKS_PER_SEC, cnt = 0;
}
 
void dfs(ll is, int v, int x) {
    if (x < H.get(is * 3 * n + v))
        return;
    H.add(is * 3 * n + v, x);
     
    if (x > best) {
        best = x;
        K[0] = B[0], K[1] = B[1], K[2] = B[2];
    }
     
    tl();
    if (is_tl)
        return;
     
    if (x + TT[v] - T[v].c < best)
        return;
         
    for (int i = beg[v]; i != fin[v]; i = nxt[i]) {
        int to = W[i];       
        if ((is >> ind[to]) & 1)
            continue;
              
        B[X[to]] ^= 1ll << Y[to];
        dfs(is | (1 << ind[to]), to, x + T[to].c);
        B[X[to]] ^= 1ll << Y[to];
         
        tl();
        if (is_tl)
            return;
    }
}
 
int main() {
#ifndef HOME
    freopen("boxes.in", "r", stdin);
    freopen("boxes.out", "w", stdout);
#endif
    scanf("%d", &n);
      
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 3; j++)
            scanf("%d", &P[j]);
            
        T[3 * i + 0] = box(min(P[0], P[1]), max(P[0], P[1]), P[2], i);
        T[3 * i + 1] = box(min(P[0], P[2]), max(P[0], P[2]), P[1], i);
        T[3 * i + 2] = box(min(P[1], P[2]), max(P[1], P[2]), P[0], i);
    }
 
    fill(nxt, nxt + 33 * n * n, -1);
    for (int i = 0; i < 3 * n; i++)
        beg[i] = i, fin[i] = i;
     
    for (int i = 0; i < 3 * n; i++)
        T[i].ind = i;
      
    for (int i = 0; i < 3 * n; i++)
        for (int j = 0; j < 3 * n; j++)
            if (i != j && T[i].a >= T[j].a && T[i].b >= T[j].b &&
                T[i].ind / 3 != T[j].ind / 3) {
                 
                 
                W[fin[i]] = j;      
                nxt[fin[i]] = nv++;
                fin[i] = nxt[fin[i]];
            }
                  
    //for (int i = 0; i < 3 * n; i++)
    //  random_shuffle(E[i].begin(), E[i].end());
    //  sort(E[i].begin(), E[i].end(), [](int a, int b) {return T[a].c > T[b].c;});
                  
    for (int i = 0; i < 3 * n; i++) {
        ind[i] = i / 3;
        X[i] = i / 60;
        Y[i] = i % 60;
    }
     
    for (int i = 0; i < 3 * n; i++) {
        used = 0, c = 0;
        dfs(i);
        TT[i] = c;
    }
                  
    for (int i = 0; i < 3 * n; i++) {
        B[X[i]] ^= 1ll << Y[i];
        dfs(1 << ind[i], i, T[i].c);
        B[X[i]] ^= 1ll << Y[i];
    }
          
    printf("%d\n%d\n", best, __builtin_popcountll(K[0]) + __builtin_popcountll(K[1]) +
                 __builtin_popcountll(K[2]));
      
    vector<box> res;
    for (int i = 0; i < 3 * n; i++)
        if (K[X[i]] & (1ll << Y[i]))
            res.push_back(T[i]);
              
    sort(res.begin(), res.end(), [](box a, box b) { return a.a == b.a ? a.b > b.b : a.a > b.a; });
      
    for (auto c : res) {
        printf("%d %d %d %d\n", ind[c.ind] + 1, c.a, c.b, c.c);
    }
      
    return 0;
}