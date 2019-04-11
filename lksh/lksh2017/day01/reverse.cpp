#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

const int maxN = (int)2e5 + 1;

struct node {
	node *L, *R, *P;
	int cnt, key, rev, mn;
} mem[maxN];

int nv = 0;

void upd(node *x) {
	if (x) {
		x->mn = x->key, x->cnt = 1;
		if (x->L) x->mn = min(x->mn, x->L->mn), x->cnt += x->L->cnt;
		if (x->R) x->mn = min(x->mn, x->R->mn), x->cnt += x->R->cnt;
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
	mem[cur].L = mem[cur].R = NULL;
	mem[cur].P = p;
	mem[cur].key = mem[cur].mn = x;
	mem[cur].cnt = 1;
	mem[cur].rev = 0;
	return &mem[cur];
}

void zig(node *x) {
	node *p = x->P;
	if (x->R) x->R->P = p;
	if (p->P) (p->P->L == p ? p->P->L : p->P->R) = x;
	p->L = x->R; x->R = p;
	x->P = p->P; p->P = x;
	upd(x), upd(p);
} 

void zag(node *x) {
	node *p = x->P;
	if (x->L) x->L->P = p;
	if (p->P) (p->P->L == p ? p->P->L : p->P->R) = x;
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

void print(node *t) {
	if (!t) return;
	//push(t);
	
	print(t->L);
	
	err("key = %d, ", t->key);
	/*if (!t->L) err("L = NULL, ");
	else err("L.key = %d, ", t->L->key);
	
	if (!t->R) err("R = NULL, ");
	else err("R.key = %d, ", t->R->key);
	
	if (!t->P) err("P = NULL, ");
	else err("P.key = %d, ", t->P->key);
	err(" ), ");*/
	
	print(t->R);
}

#define TASK "reverse"

int main() {
#ifndef HOME
	freopen(TASK".in", "r", stdin), freopen(TASK".out", "w", stdout);
#endif
	int n, q;
	
	scanf("%d %d", &n, &q);
		
    node *T = NULL;
    
    for (int i = 0; i < n; i++) {
    	int t;
    	scanf("%d", &t);
    	T = merge(T, newnode(t, NULL));
    }
    
    for (int i = 0; i < q; i++) {
    	int tp, l, r;
    	scanf("%d %d %d", &tp, &l, &r);
    	
    	auto c = split(T, r);
    	auto d = split(c.first, l - 1);
    	
    	if (tp == 1) {
    		d.second->rev ^= 1;
    	} else {
    		printf("%d\n", d.second->mn);
    	}
    	
    	auto q = merge(d.first, d.second);
    	T = merge(q, c.second);
    	
    	//print(T); err("\n");
    	//l--, r--;
    }
	return 0;
}