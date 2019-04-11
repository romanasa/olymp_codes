#include <bits/stdc++.h>
#define ll long long
#define err(...) //fprintf(stderr, __VA_ARGS__), fflush(stderr)
using namespace std;

const int dd = (int)2e5 + 7;
struct node {
	int l, r;
	int push, maxh, bal;
} T[4 * dd];

const int inf = (int)1e9 + 7;
int nv = 2;

int newnode() {
	int cur = nv++;
	T[cur].l = -1, T[cur].r = -1;
	T[cur].push = inf, T[cur].maxh = 0, T[cur].bal = 0;
	return cur;
}

struct SegmentTree {
	
	void push(int v, int tl, int tr) {
		if (T[v].push != inf) {
			T[v].maxh = T[v].bal = (tr - tl + 1) * T[v].push;
			
			if (T[v].l == -1) T[v].l = newnode();
			T[T[v].l].push = T[v].push;
			
			if (T[v].r == -1) T[v].r = newnode(); 
			T[T[v].r].push = T[v].push;
			
			T[v].push = inf;
		}
	}
	
	void upd(int v, int tl, int tr, int l, int r, int val) {
		
		if (l == tl && r == tr) {
			T[v].push = val;
		} else {
			int tm = (tl + tr) / 2;
			
			if (r <= tm) {
				if (T[v].l == -1) T[v].l = newnode();
				push(v, tl, tr);
				
				upd(T[v].l, tl, tm, l, r, val);
			} else if (l > tm) {
				if (T[v].r == -1) T[v].r = newnode();
				push(v, tl, tr);
				
				upd(T[v].r, tm + 1, tr, l, r, val);
			} else {
				if (T[v].l == -1) T[v].l = newnode();
				if (T[v].r == -1) T[v].r = newnode();
				push(v, tl, tr);
				
				upd(T[v].l, tl, tm, l, tm, val);
				upd(T[v].r, tm + 1, tr, tm + 1, r, val);
			}
			
			if (T[v].l != -1) push(T[v].l, tl, tm);
			if (T[v].r != -1) push(T[v].r, tm + 1, tr);
			
			T[v].maxh = (T[v].l == -1 ? 0 : T[T[v].l].maxh);
			T[v].maxh = max(T[v].maxh, (T[v].l == -1 ? 0 : T[T[v].l].bal) + (T[v].r == -1 ? 0 : T[T[v].r].maxh));
			
			T[v].bal = (T[v].l == -1 ? 0 : T[T[v].l].bal) + (T[v].r == -1 ? 0 : T[T[v].r].bal);			
		}
	}
	
	int get(int v, int tl, int tr, int k, int add = 0) {

		
		err("\n================\nout tree\n");
		//out(v, tl, tr);
		err("=====end\n");
			
		err("%d, [%d, %d], k = %d\n", v, tl, tr, k);
		
		if (tl == tr) {
			if (T[v].push != inf)
				T[v].maxh = T[v].bal = T[v].push;
			T[v].push = inf;
			
			return (T[v].maxh > k ? tl : tl + 1);
		}
		
		push(v, tl, tr);
		
		int tm = (tl + tr) / 2;
		
		if (T[v].l != -1) push(T[v].l, tl, tm);
		if (T[v].r != -1) push(T[v].r, tm + 1, tr);
		
		int t = (T[v].l == -1 ? 0 : T[T[v].l].maxh) + add;
		
		if (t > k) {
			if (T[v].l == -1) T[v].l = newnode();
			
			err("go left\n");
			return get(T[v].l, tl, tm, k);
		}
			
		err("go right\n");
		
		if (T[v].r == -1) T[v].r = newnode();
		
		return get(T[v].r, tm + 1, tr, k, add + (T[v].l == -1 ? 0 : T[T[v].l].bal)); 
	}

	void out(int i, int tl, int tr) {
		
		err("%d: tl = %d, tr = %d, push = %d, maxh = %d, bal = %d\n", i, tl, tr, T[i].push, T[i].maxh, T[i].bal);
		
		if (tl != tr) {
			int tm = (tl + tr) / 2;
			if (T[i].l != -1)
				out(T[i].l, tl, tm);
			if (T[i].r != -1)
				out(T[i].r, tm + 1, tr);
		}
	}
} F;

int main() {
	int n;
	scanf("%d", &n);
	
	int root = newnode();
	
	char tp;
	while (scanf("\n%c", &tp) == 1) {
		if (tp == 'E') {
			break;
		}
		
		if (tp == 'Q') {
			int h;
			scanf("%d", &h);
			
			F.push(root, 0, n - 1);
			if (T[root].maxh < h) {
				printf("%d\n", n);
				continue;
			}
			
			printf("%d\n", F.get(root, 0, n - 1, h));
		}
		if (tp == 'I') {
			int l, r, d;
			scanf("%d %d %d", &l, &r, &d);
			F.upd(root, 0, n - 1, l - 1, r - 1, d);
			
			//err("\n================\nout tree\n");
			//F.out(root, 0, n - 1);
			//err("=====end\n");
		}
		
		
	}
	
	return 0;
}