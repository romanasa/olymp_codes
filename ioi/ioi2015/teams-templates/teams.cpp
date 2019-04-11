#include "teams.h"
#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stdout)

typedef long long ll;

using namespace std;

const int dd = (int)1e6 + 7;

pair<int, int> G[dd];
int n;

const int MAXMEM = (int)9e8;
char MEM[MAXMEM];
int mpos;

inline void* operator new(size_t n) {
	char *res = MEM + mpos;
	mpos += n;
	return (void*)res;
}

inline void operator delete(void*) {}

struct node {
	node *L, *R;
	int sum;
	
	node() {}
	node(node *_L, node *_R): L(_L), R(_R) {
		sum = (L ? L->sum : 0) + (R ? R->sum : 0);
	}
};

node* build(int tl, int tr) {
	if (tl == tr) {
		return new node(NULL, NULL);
	} else {
		int tm = (tl + tr) / 2;
		return new node(build(tl, tm), build(tm + 1, tr));
	}
}

node* upd(node *v, int tl, int tr, int pos, int val) {
	if (tl == tr) {
		node *cur = new node(NULL, NULL);
		cur->sum = v->sum + val;
		return cur;
	} else {
		int tm = (tl + tr) / 2;
		if (pos <= tm) return new node(upd(v->L, tl, tm, pos, val), v->R);
		else return new node(v->L, upd(v->R, tm + 1, tr, pos, val));
	}
}

node* del(node *v, int tl, int tr, int pos) {
	if (v->sum == 0) return v;
	if (pos < tl) return v;
	if (tr <= pos) {
		auto c = new node(v->L, v->R);
		c->sum = 0;
		return c;
	}
	int tm = (tl + tr) / 2;
	return new node(del(v->L, tl, tm, pos), del(v->R, tm + 1, tr, pos));
}

void out(node *v, int tl, int tr) {
	if (tl == tr) err("T[%d] = %d, ", tl, v->sum);
	else {
		int tm = (tl + tr) / 2;
		out(v->L, tl, tm);
		out(v->R, tm + 1, tr);
	}
}

node* go(node* A, node* used, int K, int tl, int tr) {
	int sz = (A->L ? A->L->sum : 0) - (used->L ? used->L->sum : 0);
	if (tl == tr) {
		node *cur = new node(NULL, NULL);
		cur->sum = used->sum + K;
		return cur;
	}
	int tm = (tl + tr) / 2;
	if (sz >= K) 
		return new node(go(A->L, used->L, K, tl, tm), used->R);
	return new node(A->L, go(A->R, used->R, K - sz, tm + 1, tr));
}

node *U;
node *T[dd];
vector<pair<int, int>> E[dd];

void init(int N, int A[], int B[]) {
	n = N;
	for (int i = 0; i < n; i++) {
		E[A[i]].push_back({ B[i], 0 });
		E[B[i]].push_back({ B[i], 1 });
	}
	T[0] = build(0, N);
	U = build(0, N);
	node *cur = T[0];
	for (int i = 1; i <= N; i++) {
		for (auto c : E[i]) if (c.second == 0)
			cur = upd(cur, 0, N, c.first, 1);
		T[i] = cur;
		for (auto c : E[i]) if (c.second == 1)
			cur = upd(cur, 0, N, c.first, -1);
	}
}

int can(int M, int K[]) {
	if (accumulate(K, K + M, 0) > n) return 0;
	sort(K, K + M);
	node *cur = U;
	for (int i = 0; i < M; i++) {
		cur = del(cur, 0, n, K[i] - 1);
		if (T[K[i]]->sum - cur->sum < K[i]) return 0;		
		cur = go(T[K[i]], cur, K[i], 0, n);
	}
	return 1;
}
