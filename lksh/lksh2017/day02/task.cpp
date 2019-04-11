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
	node *p = x->P;
	if (x->R) x->R->P = p;
	if (p->P) (p->P->L == p ? p->P->L : p->P->R) = x;
	
	x->pathP = p->pathP;
	if (p->pathP) p->pathP = NULL;
	
	p->L = x->R; x->R = p;
	x->P = p->P; p->P = x;
	
	upd(x), upd(p);
} 

void zag(node *x) {
	node *p = x->P;
	if (x->L) x->L->P = p;
	if (p->P) (p->P->L == p ? p->P->L : p->P->R) = x;
	
	x->pathP = p->pathP;
	if (p->pathP) p->pathP = NULL;
	
	p->R = x->L; x->L = p;
	x->P = p->P; p->P = x;
	upd(x), upd(p);
}

node* splay(node *x) {
	while (x && x->P) {
		node *p = x->P;
		if (!p->P) {
			push(p), push(x);
			if (p->L == x) zig(x);
			else zag(x);
		} else {
			node *g = p->P;
			push(g), push(p), push(x);
			if (g->L == p && p->L == x) zig(p), zig(x);
			else if (g->L == p && p->R == x) zag(x), zig(x);
			else if (g->R == p && p->L == x) zig(x), zag(x);
			else if (g->R == p && p->R == x) zag(p), zag(x);
		}
	}
	return x;
}

node* upmax(node *t) {
	if (!t) return t;
	push(t);
	if (t->R) return upmax(t->R);
	else return splay(t);
}

node* merge(node *A, node *B) {
	if (!A) return B;
	if (!B) return A;
	
	A = upmax(A);
	
	A->R = B;
	B->P = A;
	
	upd(A), push(A);
	return A;
}

node* find(node *t, int x, int add = 0) {
	if (!t) return t;
	
	push(t);
	
	int key = (t->L ? t->L->cnt : 0) + add;
	
	if (key == x) {
		return splay(t);
	} else if (x < key) {
		if (t->L) return find(t->L, x, add);
		else return splay(t);
	} else {
		if (t->R) return find(t->R, x, add + 1 + (t->L ? t->L->cnt : 0));
		else return splay(t);
	}
}

pair<node*, node*> split(node *t, int x) {
	if (!t) return { t, t };
	
	push(t);
	if (x >= t->cnt) return { t, NULL };
	
	t = find(t, x);
	auto c = t->L;
	
	if (c) c->P = NULL;
	t->L = NULL;
	
	upd(c), upd(t);
	return { c, t };
}

node* expose(node *x) {
	while (1) {
		push(x);
		x = splay(x);
		
		if (!x->pathP) break;
		
		node* p = x->pathP;
		
		p = splay(p);
		
		if (p->R) p->R->P = NULL;
		if (p->R) p->R->pathP = p;
		
		p->R = x;
		
		x->P = p;
		x->pathP = NULL;
		
		upd(p), upd(x);
		push(p);
		
		//err("p key = %d, x key = %d\n", p->key, x->key);
		//print(x); err("\n");
		//err("----------\n");
	}
	upd(x);
	return x;
}

node* reroot(node *x) {
	x = expose(x);
	x = splay(x);
	
	push(x);
	
	if (x->L) {
		x->L->rev ^= 1;
		x->L->P = NULL;
		x->L->pathP = x;
		x->L = 0;
	}
	upd(x);
	return x;
}

void link(node *v, node *u) {
	push(v), push(u);
	v = reroot(v);

	v = expose(v);
	u = expose(u);

	//err("v = "); print(v); err("\n");
	//err("u = "); print(u); err("\n");
	
	//assert(v->L == NULL);
	
	v->L = u;
	
	u->P = v;
	u->pathP = NULL;
	
	upd(u), upd(v);
	//out();
}

void cut(node *a, node *b) {
	a = expose(a);
	if (a->L == b) {
		a->L = NULL, b->P = NULL, b->pathP = NULL;
		return;
	}
	swap(a, b);
	//out();
	a = expose(a); //err("_________\n");
	//out();
	if (a->R == b) {
		a->R = NULL, b->P = NULL, b->pathP = NULL;
		return;
	}
	
	a = expose(a);
	if (a->L == b) {
		a->L = NULL, b->P = NULL, b->pathP = NULL;
		return;
	}
	swap(a, b);
	//out();
	a = expose(a); //err("_________\n");
	//out();
	if (a->R == b) {
		a->R = NULL, b->P = NULL, b->pathP = NULL;
		return;
	}
	assert(0);
}

int get(node *A, node *B) {
	if (A == B) return 0;
	
	A = expose(A);
	B = expose(B);
	
	if (!A->pathP && !A->P && !B->pathP && !B->P) {
		return -1;
	}
	
	A = splay(A);
	
	if (!A->pathP) {
		//out();
		A = splay(A);
		int s1 = (A->L ? A->L->cnt : 0);
		B = splay(B);
		int s2 = (B->L ? B->L->cnt : 0);
		return abs(s2 - s1);
	}
	
	node *q = A->pathP;
	
	q = splay(q);
	int s1 = (q->L ? q->L->cnt : 0);
	
	B = splay(B);
	int s2 = (B->L ? B->L->cnt : 0);
	
	A = splay(A);
	int t1 = (A->L ? A->L->cnt : 0);
	
	return abs(s1 - s2) + 1 + t1;
}

void print(node *t) {
	if (!t) return;
	push(t);
	
	print(t->L);
	
	err("( ");
	err("key = %d, ", t->key);
	if (!t->L) err("L = NULL, ");
	else err("L.key = %d, ", t->L->key);
	
	if (!t->R) err("R = NULL, ");
	else err("R.key = %d, ", t->R->key);
	
	if (!t->P) err("P = NULL, ");
	else err("P.key = %d, ", t->P->key);
	
	if (!t->pathP) err("pathP = NULL, ");
	else err("pathP.key = %d, ", t->pathP->key);
	
	err(" ), ");
	
	print(t->R);
}


vector<node*> T;
int n, q;

void out() {
	err("____________________\n");
	for (int i = 0; i < n; i++) {
		print(T[i]); err("\n");
	}
	err("____________________\n");
}

#define TASK "linkcut"

char s[11];

int main() {
#ifndef HOME
	freopen(TASK".in", "r", stdin), freopen(TASK".out", "w", stdout);
#endif
	
	scanf("%d %d", &n, &q);
	
	T.resize(n);
	for (int i = 0; i < n; i++) T[i] = newnode(i, NULL);
	
	while (q--) {
		scanf("%s", s);
		int a, b;
		scanf("%d %d", &a, &b);
		a--, b--;
		
		if (s[0] == 'g') {
			printf("%d\n", get(T[a], T[b]));
		}
		if (s[0] == 'l') {
			link(T[a], T[b]);
		}
		if (s[0] == 'c') {
			cut(T[a], T[b]);
		}
		//out();
	}
	
	return 0;
}