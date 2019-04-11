#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

const int maxN = (int)2e5 + 1;

char s[11];

struct node {
	node *L, *R, *P;
	int key;
} mem[maxN];

int nv = 0;

node* newnode(int x, node* p) {
	int cur = nv++;
	mem[cur].L = mem[cur].R = NULL;
	mem[cur].P = p;
	mem[cur].key = x;
	return &mem[cur];
}

void zig(node *x) {
	node *p = x->P;
	p->L = x->R, x->R = p;
	x->P = p->P, p->P = x;
}

void zag(node *x) {
	node *p = x->P;
	p->R = x->L, x->L = p;
	x->P = p->P, p->P = x;
}

node* splay(node *x) {
	while (x->P) {
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

node* insert(node *t, int x) {
	if (!t) return newnode(x, NULL);	
	if (x == t->key) {
		return splay(t);
	} else if (x < t->key) {
		if (t->L) return insert(t->L, x);
		else {
			t->L = newnode(x, t);
			return splay(t->L);
		}
	} else {
		if (t->R) return insert(t->R, x);
		else {
			t->R = newnode(x, t);
			return splay(t->R);
		}
	}
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
	return A;
}

node* find(node *t, int x) {
	if (!t) return t;
	if (t->key == x) {
		return splay(t);
	} else if (x < t->key) {
		if (t->L) return find(t->L, x);
		else return splay(t);
	} else {
		if (t->R) return find(t->R, x);
		else return splay(t);
	}
}

node* erase(node *t, int x) {
	t = find(t, x);
	if (!t || t->key != x) return t;
	if (t->L) t->L->P = NULL;
	if (t->R) t->R->P = NULL;
	return merge(t->L, t->R);
}

void print(node *t) {
	if (!t) return;
	print(t->L);
	
	err("(key = %d, ", t->key);
	if (!t->L) err("L = NULL, ");
	else err("L.key = %d, ", t->L->key);
	
	if (!t->R) err("R = NULL, ");
	else err("R.key = %d, ", t->R->key);
	
	if (!t->P) err("P = NULL, ");
	else err("P.key = %d, ", t->P->key);
	err(" ), ");
	
	print(t->R);
}

#define TASK "bst"

int main() {
#ifndef HOME
	freopen(TASK".in", "r", stdin), freopen(TASK".out", "w", stdout);
#endif
	int x;
	
	node *T = NULL;
	
	while (scanf("%s", s) != -1) {
		if (s[0] == 'i') {
			scanf("%d", &x);
			T = insert(T, x);
		} else if (s[0] == 'd') {
			scanf("%d", &x);
			T = erase(T, x);
		} else if (s[0] == 'e') {
			scanf("%d", &x);
			T = find(T, x);
			puts(T && T->key == x ? "true" : "false");
		} else if (s[0] == 'n') {
			scanf("%d", &x);
			T = find(T, x);
			if (T && T->key > x) printf("%d\n", T->key);
			else if (T && T->R) printf("%d\n", T->R->key);
			else puts("none");
		} else if (s[0] == 'p') {
			scanf("%d", &x);
			T = find(T, x);
			if (T && T->key < x) printf("%d\n", T->key);
			else if (T && T->L) printf("%d\n", T->L->key);
			else puts("none");
		}
	}
	return 0;
}
