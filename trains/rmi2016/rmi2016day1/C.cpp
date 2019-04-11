#include <bits/stdc++.h>
#define ll long long
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)
using namespace std;
 
const int MAXMEM = (int)1e8;
char MEM[MAXMEM];
int mpos;
 
inline void* operator new(size_t n) {
    char *res = MEM + mpos;
    mpos += n;
    return (void*) res;
}
 
inline void operator delete(void*) {}
 
vector<vector<int> > E;
 
const int dd = (int)2e5 + 1;
const int LOG = 18;
 
int tin[dd], tout[dd], tmm = 1;
int up[LOG][dd];
vector<int> O[dd], C[dd];
ll ans[dd];
 
bool par(int a, int b) {
    return tin[a] <= tin[b] && tout[b] <= tout[a];
}
 
void calc(int v, int pr = -1) {
    tin[v] = tmm++;
    if (pr == -1) {
        for (int i = 0; i < LOG; i++) up[i][v] = 0;
    } else {
        up[0][v] = pr;
        for (int i = 1; i < LOG; i++) up[i][v] = up[i - 1][up[i - 1][v]];
    }
    for (int to : E[v]) if (to != pr) {
        calc(to, v);
    }
    tout[v] = tmm++;
}
 
mt19937 rnd(1);
 
struct node {
    int key, cnt, pr;
    ll sum;
    node *L, *R;
} mem[dd * LOG];
 
int nv = 0;
node* newnode(int x) {
    int cur = nv++;
    mem[cur].key = x;
    mem[cur].cnt = 1;
    mem[cur].sum = x;
    mem[cur].pr = rnd();
    return &mem[cur];
}
 
int cnt(node *t) { return t ? t->cnt : 0; }
ll sum(node *t) { return t ? t->sum : 0; }
 
void upd(node *t) {
    if (!t) return;
    t->cnt = cnt(t->L) + 1 + cnt(t->R);
    t->sum = sum(t->L) + t->key + sum(t->R);
}
 
node *Q[107], *W[107], *Z[107];
int tp[107];
int ind;
 
node* merge(node *L, node *R) {
    ind = 0;
    while (1) {
        Q[ind] = L;
        W[ind] = R;
        if (!L) { Z[ind++] = R; break; }
        if (!R) { Z[ind++] = L; break; }
        if (L->pr > R->pr) {
            L = L->R, tp[ind] = 0;
        } else {
            R = R->L, tp[ind] = 1;
        }
        ind++;
    }
    for (int i = ind - 2; i >= 0; i--) {
        if (tp[i] == 0) {
            Q[i]->R = Z[i + 1];
            upd(Q[i]), Z[i] = Q[i];
        } else {
            W[i]->L = Z[i + 1];
            upd(W[i]), Z[i] = W[i];
        }
    }
    return Z[0];
}
 
pair<node*, node*> split(node *T, int key) {
    ind = 0;
    while (1) {
        Z[ind] = T;
        if (!T) {
            Q[ind] = W[ind] = NULL;
            ind++;
            break;
        }
        if (T->key < key) {
            T = T->R, tp[ind] = 0;
        } else {
            T = T->L, tp[ind] = 1;
        }
        ind++;
    }
    for (int i = ind - 2; i >= 0; i--) {
        if (tp[i] == 0) {
            Z[i]->R = Q[i + 1];
            upd(Z[i]);
            Q[i] = Z[i], W[i] = W[i + 1];
        } else {
            Z[i]->L = W[i + 1];
            upd(Z[i]);
            Q[i] = Q[i + 1], W[i] = Z[i];
        }
    }
    return { Q[0], W[0] };
}
 
struct magic {
    set<int> S;
    node *T1 = NULL, *T2 = NULL;
     
    void add(int x) {
        if (S.count(x)) return;
        S.insert(x);
         
        auto c = split(T1, x);
        auto d = split(T2, x);
         
        int sz = cnt(c.first) + cnt(d.first);
         
        if ((sz & 1) == 0) c.first = merge(c.first, newnode(x));
        else d.first = merge(d.first, newnode(x));
         
        T1 = merge(c.first, d.second);
        T2 = merge(d.first, c.second);
    }
     
    void erase(int x) {
        if (!S.count(x)) return;
        S.erase(x);
         
        auto c = split(T1, x);
        auto d = split(T2, x);
         
        int sz = cnt(c.first) + cnt(d.first);
         
        if ((sz & 1) == 0) c.second = split(c.second, x + 1).second;
        else d.second = split(d.second, x + 1).second;
         
        T1 = merge(c.first, d.second);
        T2 = merge(d.first, c.second);  
    }
    ll count() {
        return sum(T1);
    }
    int size() {
        return S.size();
    }
};
 
magic dfs(int v, int pr = -1) {
    magic cur;
    for (int to : E[v]) if (to != pr) {
        auto t = dfs(to, v);
        if (cur.size() < t.size()) swap(t, cur);
        for (int x : t.S) {
            cur.add(x);
        }
    }
     
    for (int x : O[v]) cur.add(x); 
    ans[v] = cur.count();
    for (int x : C[v]) cur.erase(x);
    return cur;
}
 
int lca(int a, int b) {
    if (par(a, b)) return a;
    if (par(b, a)) return b;
    for (int i = LOG - 1; i >= 0; i--) {
        if (!par(up[i][a], b))
            a = up[i][a];
    }
    return up[0][a];
}
 
 
int main() {
    int n, m;
    scanf("%d %d", &n, &m);
     
    E.resize(n);
     
    for (int i = 0; i + 1 < n; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        E[a - 1].push_back(b - 1);
        E[b - 1].push_back(a - 1);
    }
    calc(0);
     
    for (int i = 0; i < m; i++) {
        int a, b, c;
        scanf("%d %d %d", &a, &b, &c);
        a--, b--;
        int t = lca(a, b);
        O[a].push_back(c);
        O[b].push_back(c);
        C[t].push_back(c);
    }
    dfs(0);
    for (int i = 0; i < n; i++) printf("%I64d\n", ans[i]);
    return 0;
}