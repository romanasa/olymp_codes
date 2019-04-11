#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)
//#define _GLIBCXX_DEBUG 
using namespace std;
    
typedef long long ll;
    
const int dd = (int)2e5 + 7;
const int mod = (int)1e9 + 7;
   
int old[dd];
int col[dd], G[dd];
//vector<vector<int> > GR;
    
int ans;
    
void add(int &a, int b) {
    a += b;
    if (a >= mod) a -= mod;
}
    
int mul(int a, int b) { return (1ll * a * b) % mod; }
   
typedef struct node * pnode;
mt19937 rnd(1);
   
const int maxN = (int)2e5 + 7;
  
struct node {
    node *L, *R;
    int pr, key;
    int cnt, q, push, sz, sumQ, sum;
} mem[maxN];
  
const int MAXMEM = (int)2e8;
char MEM[MAXMEM];
int mpos;
   
inline void* operator new (size_t n) {
    char *res = MEM + mpos;
    mpos += n;
    return (void*)res;
}
   
inline void operator delete(void*) {}
   
int nv = 0;
   
node* newnode(int col, int cnt, int q) {
    int cur = nv++;
    mem[cur].L = mem[cur].R = NULL;
    mem[cur].pr = rnd();
    mem[cur].sum = mem[cur].cnt = cnt;
    mem[cur].sumQ = mem[cur].q = q;
    mem[cur].push = mem[cur].sz = 1;
    mem[cur].key = col;
    return &mem[cur];
}
   
   
void push(node *T) {
    if (T && T->push != 1) {
        T->sum = mul(T->sum, T->push);
        T->sumQ = mul(T->sumQ, T->push);
        T->cnt = mul(T->cnt, T->push);
        T->q = mul(T->q, T->push);
           
        if (T->L) T->L->push = mul(T->L->push, T->push);
        if (T->R) T->R->push = mul(T->R->push, T->push);
   
        T->push = 1;     
    }
}
   
void upd(node* T) {
    if (!T) return;
    push(T);
    T->sz = 1;
    T->sumQ = T->q;
    T->sum = T->cnt;
    if (T->L) {
        push(T->L);
        T->sz += T->L->sz;
        add(T->sumQ, T->L->sumQ);
        add(T->sum, T->L->sum);
    }
    if (T->R) {
        push(T->R);
        T->sz += T->R->sz;
        add(T->sumQ, T->R->sumQ);
        add(T->sum, T->R->sum);
    }
}
   
pnode Q[107], W[107], E[107];
int tp[107];
int ind;
   
pnode merge(pnode L, pnode R) {
    ind = 0;
    while (1) {
        push(L), push(R);
        Q[ind] = L;
        W[ind] = R;
        if (!L) { E[ind++] = R; break; }
        if (!R) { E[ind++] = L; break; }
        if (L->pr > R->pr) {
            L = L->R;
            tp[ind] = 0;
        } else {
            R = R->L;
            tp[ind] = 1;
        }
        ind++;
    }
    for (int i = ind - 2; i >= 0; i--) {
        if (tp[i] == 0) {
            Q[i]->R = E[i + 1];
            upd(Q[i]);
            E[i] = Q[i];
        } else {
            W[i]->L = E[i + 1];
            upd(W[i]);
            E[i] = W[i];
        }
    }
    return E[0];
}
   
pair<pnode, pnode> split(pnode T, int key) {
    ind = 0;
    while (1) {
        push(T);
        E[ind] = T;
        if (!T) {
            Q[ind] = W[ind] = NULL;
            ind++;
            break;
        }
        if (T->key <= key) {
            T = T->R;
            tp[ind] = 0;
        } else {
            T = T->L;
            tp[ind] = 1;
        }
        ind++;
    }
    for (int i = ind - 2; i >= 0; i--) {
        if (tp[i] == 0) {
            E[i]->R = Q[i + 1];
            upd(E[i]);
            Q[i] = E[i], W[i] = W[i + 1];
        } else {
            E[i]->L = W[i + 1];
            upd(E[i]);
            Q[i] = Q[i + 1], W[i] = E[i];
        }
    }
    return { Q[0], W[0] };
}

node* insert(node* T, node* cur) {
	if (!T) return cur;
	push(T);
	
	if (T->pr < cur->pr) {
		auto c = split(T, cur->key);
		cur->L = c.first, cur->R = c.second;
		upd(cur);
		return cur;
	}
	
	//assert(cur->key != T->key);
	
	if (cur->key < T->key) T->L = insert(T->L, cur);
	else T->R = insert(T->R, cur);
	upd(T);
	return T;
}   

void out(node *T) {
    if (!T) return;
    push(T);
    out(T->L);
    err("(%d, %d), ", T->key, T->cnt);
    out(T->R);
}
   
   
int iM;
node* M[dd];
   
node* A[dd];
int iA;
   
struct magic {
    node *T = NULL;
           
    void insert(int col, int cnt) { 
        T = ::insert(T, newnode(col, cnt, mul(cnt, old[G[col]])));
    }
     
    void insert(node *cur) {
        T = ::insert(T, cur);
    }
       
    void go(node *T) {
        if (!T) return;
        ::push(T);
        go(T->L);
        M[iM++] = T;
        go(T->R);
    }
       
    void merge(magic &other) {
        int cur = 1, sum = 1;
           
        iM = 0;
        go(T);
          
        //err("M = "); for (auto c : M) err("(%d, %d), ", c.first, c.second); err("\n");
           
        iA = 0;
           
        for (int i = 0; i < iM; i++) {
            auto &x = M[i];
            auto c = split(other.T, x->key);
            A[iA++] = c.first;
            other.T = c.second;
               
   
            if (A[iA - 1]) {
                push(A[iA - 1]);
                add(sum, A[iA - 1]->sum);
                if (cur ^ 1) A[iA - 1]->push = mul(A[iA - 1]->push, cur);
            }   
               
            add(cur, x->cnt);
            if (sum ^ 1) {
                x->cnt = mul(x->cnt, sum);
                x->q = mul(x->q, sum);
            } 
        }
           
        A[iA++] = other.T;
        if (A[iA - 1]) A[iA - 1]->push = mul(A[iA - 1]->push, cur);
       
        other.T = NULL;
        for (int i = 0; i < iA; i++) other.T = ::merge(other.T, A[i]);
           
        for (int i = 0; i < iM; i++) {
         
            M[i]->L = M[i]->R = NULL;
            M[i]->sum = M[i]->cnt;
            M[i]->sumQ = M[i]->q;
            M[i]->push = M[i]->sz = 1;
     
            other.insert(M[i]);
        }   
    }
       
    int get() {
        push(T);
        return T ? T->sumQ : 0;
    }
       
    void lstrip(int col) {
        auto c = split(T, col);
        push(c.first);
        int cnt = 1;
        if (c.first) add(cnt, c.first->sum);
        T = c.second;
        insert(col, cnt);
    }
       
    int size() { push(T); return T ? T->sz : 0; }
};

int head[dd], tail[dd], nxt[3 * dd];
int to[3 * dd];
int cntV = 0;

void addE(int a, int b) {
	to[tail[a]] = b;
	nxt[tail[a]] = cntV++;
	tail[a] = nxt[tail[a]];
}

magic dfs(int v, int pr = -1) {
    magic cur;        
    for (int num = head[v]; num != tail[v]; num = nxt[num]) if (to[num] != pr) {
        auto t = dfs(to[num], v);
        if (t.size() > cur.size()) swap(t, cur);
        t.merge(cur);
    }
    cur.lstrip(col[v]);
    add(ans, cur.get());
    return cur;
}
    
int main() {
    int n;
    scanf("%d", &n);
        
    for (int i = 0; i < n; i++) head[i] = tail[i] = i;
    cntV = n;
        
    for (int i = 0; i < n; i++) {
        scanf("%d", &col[i]);
        old[i] = col[i];
    }
        
    for (int i = 0; i < n; i++) G[i] = i;
    sort(G, G + n, [](int a, int b) { return col[a] < col[b]; });
    for (int i = 0; i < n; i++) col[G[i]] = i;
     
         
    for (int i = 0; i + 1 < n; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        addE(a - 1, b - 1);
        addE(b - 1, a - 1);
    }
    /*
    for (int i = 0; i < n; i++) {
        sort(GR[i].begin(), GR[i].end(), [](int a, int b){ return col[a] > col[b]; });
    }
    */
    dfs(0);
    printf("%d\n", ans);
    return 0;
}