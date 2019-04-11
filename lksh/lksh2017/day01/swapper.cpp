#include <bits/stdc++.h>
#define err(...) //fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

const int maxN = (int)2e5 + 1;

struct node {
	node *L, *R, *P;
	int cnt, key;
	ll sum;
} mem[maxN];

int nv = 0;

void upd(node *x) {
	if (x) {
		x->sum = x->key + (x->L ? x->L->sum : 0) + (x->R ? x->R->sum : 0);
		x->cnt = 1 + (x->L ? x->L->cnt : 0) + (x->R ? x->R->cnt : 0);
	}
}

node* newnode(int x, node* p) {
	int cur = nv++;
	mem[cur].L = mem[cur].R = NULL;
	mem[cur].P = p;
	mem[cur].key = mem[cur].sum = x;
	mem[cur].cnt = 1;
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
	return x;
}

node* upmax(node *t) {
	if (!t) return t;
	if (t->R) return upmax(t->R);
	else return splay(t);
}

node* merge(node *A, node *B) {
	if (!A) return B;
	if (!B) return A;
	A = upmax(A);
	A->R = B;
	B->P = A;
	upd(A);
	return A;
}

node* find(node *t, int x, int add = 0) {
	if (!t) return t;
	
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
	print(t->L);
	
	err("(key = %d, sum = %I64d, ", t->key, t->sum);
	if (!t->L) err("L = NULL, ");
	else err("L.key = %d, ", t->L->key);
	
	if (!t->R) err("R = NULL, ");
	else err("R.key = %d, ", t->R->key);
	
	if (!t->P) err("P = NULL, ");
	else err("P.key = %d, ", t->P->key);
	err(" ), ");
	
	print(t->R);
}

#define TASK "swapper"

int main() {
#ifndef HOME
	freopen(TASK".in", "r", stdin), freopen(TASK".out", "w", stdout);
#endif


	int n, q;
	int test = 1;
	
	while (scanf("%d %d", &n, &q) == 2) {
		if (n + q == 0) break;	
     	node *A = NULL, *B = NULL;
     	
     	for (int i = 0; i < n; i++) {
     		int t;
     		scanf("%d", &t);
     		//A = merge(A, newnode(t, NULL));
     		if (i & 1) A = merge(A, newnode(t, NULL));
     		else B = merge(B, newnode(t, NULL));
     	}
     	
     	//print(A); err("\n");
     	//print(B); err("\n");
     	
     	printf("Swapper %d:\n", test++);
     	
     	for (int i = 0; i < q; i++) {
     		int tp, l, r;
     		scanf("%d %d %d", &tp, &l, &r);
     		//l--, r--;
     		
     		if (tp == 1) {
     			
     			auto c = split(A, r / 2);
     			auto d = split(c.first, (l - 1) / 2);
     					
     			auto e = split(B, (r + 1) / 2);
     			auto f = split(e.first, (l) / 2);
     			
     			
     			A = merge(merge(d.first, f.second), c.second);
     			B = merge(merge(f.first, d.second), e.second);
     			
     		} else {
     			
     			auto c = split(A, r / 2);
     			auto d = split(c.first, (l - 1) / 2);
     					
     			auto e = split(B, (r + 1) / 2);
     			auto f = split(e.first, (l) / 2);
     			
     			err("{ {"); print(d.first);err("| "); print(d.second); err("}"); print(c.second); err("}\n");
     			err("{ {"); print(f.first);err("| "); print(f.second); err("}"); print(e.second); err("}\n");
     			
     			ll ans = (f.second ? f.second->sum : 0) + (d.second ? d.second->sum : 0);
     			
     			A = merge(merge(d.first, d.second), c.second);
     			B = merge(merge(f.first, f.second), e.second);
     			printf("%lld\n", ans);
     		}
     		
     		print(A); err("\n");
     		print(B); err("\n");
     	}
	}
	return 0;
}