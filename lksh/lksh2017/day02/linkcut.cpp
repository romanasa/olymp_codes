#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

const int maxN = (int)2e5 + 1;

struct node {
	node *L, *R, *P;
	node* pathP;
	int cnt, rev, key;
} mem[maxN];

void print(node* t);
void out();

void check(node *x) {
	if (x && x->P) assert(x->P->L == x || x->P->R == x);
}

int nv = 0;

void upd(node *x) {
	if (x) {
		x->cnt = 1;
		if (x->L) x->cnt += x->L->cnt;
		if (x->R) x->cnt += x->R->cnt;
	}
}

void push(node *x) {
	if (x && x->rev) {
		swap(x->L, x->R);
		if (x->L) x->L->rev ^= 1;
		if (x->R) x->R->rev ^= 1;
		x->rev = 0;
	}
}

node* newnode(int x, node* p) {
	int cur = nv++;
	mem[cur].L = mem[cur].R = mem[cur].pathP = NULL;
	mem[cur].P = p;
	mem[cur].cnt = 1;
	mem[cur].rev = 0;
	mem[cur].key = x;
	return &mem[cur];
}

void zig(node *x) {
	node *y = x->P, *z = y->P;
	if (y->L = x->R) y->L->P = y;
	x->R = y, y->P = x;
	if (x->P = z) {
		if (y == z->L) z->L = x;
		else z->R = x;
	}
	x->pathP = y->pathP;
	y->pathP = NULL;
	upd(y);
} 

void zag(node *x) {
	node *y = x->P, *z = y->P;
	if (y->R = x->L) y->R->P = y;
	x->L = y, y->P = x;
	if (x->P = z) {
		if (y == z->L) z->L = x;
		else z->R = x;
	}
	x->pathP = y->pathP;
	y->pathP = NULL;
	upd(y);
}

vector<node*> Q;

node* splay(node *x) {
	auto old = x;
	while (old) {
		Q.push_back(old);
		old = old->P;
	}
	reverse(Q.begin(), Q.end());
	for (auto c : Q) push(c);
	Q.clear();
	while (x && x->P) {
		node *p = x->P;
		if (!p->P) {
			if (p->L == x) zig(x);
			else zag(x);
		} else {
			node *g = p->P;
			if (g->L == p && p->L == x) zig(p), zig(x);
			else if (g->L == p && p->R == x) zag(x), zig(x);
			else if (g->R == p && p->L == x) zig(x), zag(x);
			else if (g->R == p && p->R == x) zag(p), zag(x);
		}
	}
	upd(x);
	return x;
}

node* expose(node *x) {
	push(x);
	splay(x);
	if (x->R) {
		x->R->pathP = x;
		x->R->P = NULL;
		x->R = NULL;
		upd(x);
	}
	while (x->pathP) {
		node* p = x->pathP;
		splay(p);
		if (p->R) {
			p->R->pathP = p;
			p->R->P = NULL;
		}
		p->R = x;
		x->P = p;
		x->pathP = NULL;		
		upd(p);
		splay(x);
	}
	return x;
}

node* reroot(node *x) {
	push(x);
	x = expose(x);
	if (x->L) {
		x->L->rev ^= 1;
		x->L->P = NULL;
		x->L->pathP = x;
		x->L = NULL;
	}
	upd(x);	
	return x;
}

vector<node*> T;
int n, q;

void link(node *v, node *u) {
	push(v), push(u);
	v = reroot(v);
	u = expose(u);
	v->L = u;
	u->P = v;
	u->pathP = NULL;
	upd(u), upd(v);
}

void cut(node *a, node *b) {
	push(a), push(b);
	b = reroot(b);
	a = expose(a);
	a->L->P = NULL, a->L = NULL;
	upd(a);
	return;
}

int get(node *A, node *B) {
	if (A == B) return 0;
	A = reroot(A), B = reroot(B);
	
	if (!A->pathP && !A->P && !B->pathP && !B->P) {
		return -1;
	}
	
	A = expose(A);
	
	if (!A->pathP) {
		A = expose(A);
		int s1 = (A->L ? A->L->cnt : 0);
		B = expose(B);
		int s2 = (B->L ? B->L->cnt : 0);
		return abs(s2 - s1);
	}
	node *q = A->pathP;
	
	q = expose(q);
	int s1 = (q->L ? q->L->cnt : 0);
	
	B = expose(B);
	int s2 = (B->L ? B->L->cnt : 0);
	
	A = expose(A);
	int t1 = (A->L ? A->L->cnt : 0);
	
	return abs(s1 - s2) + 1 + t1;
}


#define TASK "linkcut"

char s[11];

int main() {
#ifndef HOME
	//freopen(TASK".in", "r", stdin), freopen(TASK".out", "w", stdout);
#endif
	scanf("%d %d", &n, &q);
	
	T.resize(n);
	for (int i = 0; i < n; i++) T[i] = newnode(i, NULL);
	
	while (q--) {
		scanf("%s", s);
		int a, b;
		scanf("%d %d", &a, &b);
		a--, b--;
		if (s[0] == 'g') printf("%d\n", get(T[a], T[b]));
		if (s[0] == 'l') link(T[a], T[b]);
		if (s[0] == 'c') cut(T[a], T[b]);
	}	
	return 0;
}