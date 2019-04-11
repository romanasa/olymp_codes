#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

mt19937 rnd(1);

const int maxN = (int)6e5 + 1;

struct node {
	node *L, *R, *P;
	int cnt, pr, key;
	int w1, w2, w3;
	int s1, s2, s3;
	int mn;
} mem[maxN];

int nv;

node* newnode(int x, int w1, int w2, int w3) {
	int cur = nv++;
	mem[cur].L = mem[cur].R = NULL;
	mem[cur].cnt = 1;
	mem[cur].key = x;
	mem[cur].pr = rnd();
	mem[cur].w1 = mem[cur].s1 = w1;
	mem[cur].w2 = mem[cur].s2 = w2;
	mem[cur].w3 = mem[cur].s3 = w3;
	mem[cur].mn = w2;
	return &mem[cur];
}

void upd(node *T) {
	if (!T) return;
	T->cnt = 1, T->s1 = T->w1, T->s3 = T->w3;
	T->s2 = T->w2;
	T->mn = (T->L ? T->L->s2 : 0) + T->w2;
	
	if (T->L) {
		T->L->P = T;
		T->cnt += T->L->cnt;
		T->s1 += T->L->s1, T->s2 += T->L->s2, T->s3 += T->L->s3;
		T->mn = min(T->mn, T->L->mn);
	}
	if (T->R) {
		T->R->P = T;
		T->cnt += T->R->cnt;
		T->s1 += T->R->s1, T->s2 += T->R->s2, T->s3 += T->R->s3;
		T->mn = min(T->mn, (T->L ? T->L->s2 : 0) + T->w2 + T->R->mn);
	}
}


node* merge(node *L, node *R) {
	if (!L || !R) return L ? L : R;
	if (L->pr > R->pr) {
		L->R = merge(L->R, R);
		upd(L);
		return L;
	} else {
		R->L = merge(L, R->L);
		upd(R);
		return R;
	}
}

pair<node*, node*> split(node *T, int key, int add = 0) {
	if (!T) return { NULL, NULL };
	int cur = (T->L ? T->L->cnt : 0) + add;	
	if (key <= cur) {
		auto c = split(T->L, key, add);
		T->L = c.second;
		upd(c.first), upd(T);
		
		if (c.first) c.first->P = NULL;
		if (T) T->P = NULL;
		return { c.first, T };
	} else {
		auto c = split(T->R, key, cur + 1);
		T->R = c.first;
		upd(T), upd(c.second);
		
		if (T) T->P = NULL;
		if (c.second) c.second->P = NULL;
		return { T, c.second };
	}
}

int getnum(node* T) {
	int cur = (T->L ? T->L->cnt : 0);
	while (T->P) {
		if (T->P->R == T) cur += (T->P->L ? T->P->L->cnt : 0) + 1;
		T = T->P;
	}
	return cur + 1;
}

node* get(node *T, int k) {
	if (T->L && T->L->mn == k) return get(T->L, k);
	if ((T->L ? T->L->s2 : 0) + T->w2 == k) return T;
	k -= (T->L ? T->L->s2 : 0) + T->w2;
	return get(T->R, k);	
}

void print(node *T) {
	if (!T) return;
	print(T->L);
	err("(key = %d, w1 = %d, w3 = %d), ", T->key, T->w1, T->w3);
	print(T->R);
}

#define TASK "treenum"

int main() {
#ifndef HOME
	freopen(TASK".in", "r", stdin), freopen(TASK".out", "w", stdout);
#endif
	int q;
	scanf("%d", &q);
	
	vector<node*> in, out;
	vector<int> h;
	
	in.push_back(newnode(0, 0, 0, 0));
	out.push_back(newnode(0, 0, 0, 0));
	h.push_back(0);
	
	int cur = 1;
	
	node *T = merge(in.back(), out.back());
	
	while (q--) {
		char w;
		int x, y;
		scanf("\n%c", &w);	
		if (w == 'l' || w == 'r') {
			scanf("%d", &x);
			
			auto c = (w == 'l' ? split(T, getnum(in[x])) : split(T, getnum(out[x]) - 1));
			
			in.push_back(newnode(cur, 0, 1, 1));
			out.push_back(newnode(cur, 1, -1, 0));
			h.push_back(h[x] + 1);
			
			c.first = merge(c.first, in[cur]);
			c.first = merge(c.first, out[cur]);
			T = merge(c.first, c.second);
			
			cur++;
		}
		
		if (w == 'a') {
			scanf("%d %d", &x, &y);
			auto c = split(T, getnum(out[y]));
			
			in.push_back(newnode(cur, 0, 1, 1));
			out.push_back(newnode(cur, 1, -1, 0));
			h.push_back(h[x] + 1);

			c.first = merge(c.first, in[cur]);
			c.first = merge(c.first, out[cur]);
			T = merge(c.first, c.second);	
			cur++;
		}
		
		if (w == 'd') {
			scanf("%d", &x);
			auto c = split(T, getnum(out[x]));
			auto d = split(c.first, getnum(in[x]) - 1);
			T = merge(d.first, c.second);
		}
		
		if (w == 'p') {
			scanf("%d %d", &x, &y);
			if (getnum(in[y]) < getnum(in[x])) swap(x, y);
			
			auto c = split(T, getnum(in[y]));
			auto d = split(c.first, getnum(in[x]));
			
			if (d.second) {
				int curh = h[x] + d.second->mn;
				printf("%d\n", h[x] - curh + h[y] - curh + 1);
			} else puts("1");
			c.first = merge(d.first, d.second);
			T = merge(c.first, c.second);
		}
		
		if (w == 'q') {
			scanf("%d %d", &x, &y);
			if (getnum(in[y]) < getnum(in[x])) swap(x, y);
			
			auto c = split(T, getnum(in[y]));
			auto d = split(c.first, getnum(in[x]));
			
			if (d.second) {
				node *lca = get(d.second, d.second->mn);
				
				auto e = split(d.second, getnum(lca));

				int cur = (e.first ? e.first->s3 : 0) + (e.second ? e.second->s1 : 0);
				printf("%d\n", cur);
				
				d.second = merge(e.first, e.second);
			} else puts("0");
			c.first = merge(d.first, d.second);
			T = merge(c.first, c.second);
		}
	}
	return 0;
} 