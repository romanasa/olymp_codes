#include "grader.h"
#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

long long gcd(long long X, long long Y) {
    long long tmp;
    while (X != Y && Y != 0) {
        tmp = X;
        X = Y;
        Y = tmp % Y;
    }
    return X;
}

mt19937 rnd(1);

struct node1D {
	node1D *L = NULL, *R = NULL;
	ll val = 0, num = 0;
	int pr, mn, mx;
	int x, y;
	
	node1D(int a, int b, ll t) {
		L = R = NULL;
		val = num = t;
		mn = mx = x = a, y = b;
		pr = rnd();
	}
};

ll val(node1D *T) { return T ? T->val : 0; }

void upd(node1D *T) {
	if (T) {
		T->val = gcd(T->num, gcd(val(T->L), val(T->R)));
		T->mn = min({ T->L ? T->L->mn : (int)1e9, T->R ? T->R->mn : (int)1e9, T->x} );
		T->mx = max({ T->L ? T->L->mx : -1, T->R ? T->R->mx : -1, T->x });
	}
}

node1D* merge(node1D *L, node1D *R) {
	if (!L) return R;
	if (!R) return L;
	if (L->pr > R->pr) {
		L->R= merge(L->R, R);
		upd(L);
		return L;
	} else {
		R->L = merge(L, R->L);
		upd(R);
		return R;
	}
}

pair<node1D*, node1D*> split(node1D *T, int x, int y) {
	if (!T) return { NULL, NULL };
	if (make_pair( x, y ) <= make_pair( T->x, T->y )) {
		auto c = split(T->L, x, y);
		T->L = c.second;
		upd(c.first), upd(T);	
		return { c.first, T };
	} else {
		auto c = split(T->R, x, y);
		T->R = c.first;
		upd(T), upd(c.second);
		return { T, c.second };
	}
}

void upd(node1D *&T, int x, int y, ll val) {
	auto c = split(T, x, y);
	auto d = split(c.second, x, y + 1);
	T = merge(c.first, new node1D(x, y, val));
	T = merge(T, d.second);
}

int R, C;


ll get(node1D *T, int x, int y) {
	
	if (!T) return 0;
	ll cur = 0;
	
	if (x <= T->mn && T->mx <= y) return T->val;
	
	if (x <= T->x && T->x <= y) cur = gcd(cur, T->num);
	
	if (x <= T->x) cur = gcd(cur, get(T->L, x, y));
	if (y >= T->x) cur = gcd(cur, get(T->R, x, y));
	return cur;
}


struct node2D {
	node2D *L = NULL, *R = NULL;
	node1D *cur = NULL;
	
	void upd(int tl, int tr, int pos, int y, ll c) {
		::upd(cur, y, pos, c);
		//err("upd tl = %d, tr = %d, pos = %d, y = %d, c = %lld\n", tl, tr, pos, y, c);
		
		if (tl != tr) {
			int tm = (tl + tr) / 2;
			if (pos <= tm) {
				if (!L) L = new node2D();
				L->upd(tl, tm, pos, y, c);
			} else {
				if (!R) R = new node2D();
				R->upd(tm + 1, tr, pos, y, c);
			}
		}
	}
	
	ll get(int tl, int tr, int l, int r, int x, int y) {
		if (tl == l && tr == r) {
			//err("get tl = %d, tr = %d, x = %d, y = %d, res = %lld\n", tl, tr, x, y, cur ? ::get(cur, x, y) : 0);
			return (cur ? ::get(cur, x, y) : 0);
		}
		int tm = (tl + tr) / 2;
		if (r <= tm) return (L ? L->get(tl, tm, l, r, x, y) : 0);
		if (l > tm) return (R ? R->get(tm + 1, tr, l, r, x, y) : 0);
		return gcd(L ? L->get(tl, tm, l, tm, x, y) : 0, R ? R->get(tm + 1, tr, tm + 1, r, x, y) : 0);
	}
};

node2D *root;

void print(node1D *t) {
	if (!t) return;
	print(t->L);
	printf("(x = %d, y = %d, t = %lld), ", t->x, t->y, t->val);
	print(t->R);
}

void init(int R, int C) {
	::R = R, ::C = C;
	root = new node2D();
}

void update(int P, int Q, long long K) {	
	root->upd(0, R - 1, P, Q, K);
}

long long calculate(int P, int Q, int U, int V) {
    return root->get(0, R - 1, P, U, Q, V);
}
