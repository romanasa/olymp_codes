#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <set>
#include <map>
#include <bitset>
#include <string>
#include <fstream>
#include <vector>
#include <cstring>
#include <cassert>
#include <random>

using namespace std;

typedef long long ll;
typedef double ld;

int solve();

#define TASK "fuel"
#define err(...) //fprintf(stdout, __VA_ARGS__), fflush(stdout)

int main() {
#ifdef HOME
	freopen("input.txt", "r", stdin), freopen("output.txt", "w", stdout);
#else
	//freopen(TASK".in", "r", stdin), freopen(TASK".out", "w", stdout);
#endif
	solve();
}

const int dd = (int)5e5 + 7;
int A[dd];

typedef struct node * pnode;

mt19937 rnd(1488);

struct node {
	pnode L, R;
	int key, prior;
	int cnt, maxk;
};

node mem[4 * dd];
int nv;

void upd(pnode T) {
	if (T) {
		T->cnt = (T->L ? T->L->cnt : 0) + 1 + (T->R ? T->R->cnt : 0);
		T->maxk = T->key;
		if (T->L && T->L->maxk > T->maxk) T->maxk = T->L->maxk;
		if (T->R && T->R->maxk > T->maxk) T->maxk = T->R->maxk;
	}
}

pnode newnode() {
	return &mem[nv++];
}

pnode Q[107], W[107], E[107];
int tp[107];
int ind;

pnode merge(pnode L, pnode R) {
	
	ind = 0;

	while (1) {
	
		Q[ind] = L;
		W[ind] = R;

		if (!L) { E[ind++] = R; break; }
		if (!R) { E[ind++] = L; break; }

		if (L->prior > R->prior) {
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

pnode T[4 * dd];
int G[4 * dd];

void build(int v, int tl, int tr) {
	if (tl == tr) {
		T[v] = newnode();
		T[v]->L = T[v]->R = NULL;
		T[v]->key = T[v]->maxk = A[tl];
		T[v]->cnt = 1;
		T[v]->prior = rnd();
	} else {
		int tm = (tl + tr) / 2;
		build(v * 2, tl, tm);
		build(v * 2 + 1, tm + 1, tr);

		T[v] = T[v * 2];

		int t = T[v]->maxk;

		auto c = split(T[v * 2 + 1], t);

		T[v] = merge(T[v], c.second);
		G[v] = t;

		T[v * 2] = NULL;
		T[v * 2 + 1] = c.first;

	}
}

void upd(int v, int tl, int tr, int pos, int val) {
	if (tl == tr) {
		T[v]->L = T[v]->R = NULL;
		T[v]->key = T[v]->maxk = val;
		T[v]->cnt = 1;
		T[v]->prior = rnd();
	} else {

		auto c = split(T[v], G[v]);

		T[v] = NULL;
		T[v * 2] = c.first;
		T[v * 2 + 1] = merge(T[v * 2 + 1], c.second);

		int tm = (tl + tr) / 2;
		if (pos <= tm) {
			upd(v * 2, tl, tm, pos, val);
		} else {
			upd(v * 2 + 1, tm + 1, tr, pos, val);
		}

		T[v] = T[v * 2];

		int t = T[v]->maxk;

		c = split(T[v * 2 + 1], t);

		T[v] = merge(T[v], c.second);
		G[v] = t;

		T[v * 2] = NULL;
		T[v * 2 + 1] = c.first;
	}
}

int getk(pnode T, int k) {

	while (1) { 
		
		if (T->L && T->L->cnt >= k) {
			T = T->L;
		} else {
			k -= (T->L ? T->L->cnt : 0);
			if (k == 1) return T->key;
			k--;
			T = T->R;
		}
	}
}


/** Interface */

inline int readChar();
template <class T = int> inline T readInt();
template <class T> inline void writeInt(T x, char end = 0);
inline void writeChar(int x);
inline void writeWord(const char *s);

int solve() {
	int n = readInt(), q = readInt();
	for (int i = 0; i < n; i++) {
		A[i] = readInt();
	}
	build(1, 0, n - 1);
	while (q--) {
		int tp = readInt();

		if (tp == 1) {
			int p = readInt(), x = readInt();
			p--;

			upd(1, 0, n - 1, p, x);
			A[p] = x;
		} else {
			int k = readInt();
			if (T[1]->cnt < k) {
				writeWord("-1\n");
			} else {
				writeInt(getk(T[1], k), '\n');
			}
		}
	}
	return 0;
}

/** Read */

static const int buf_size = 4096;

inline int getChar() {
	static char buf[buf_size];
	static int len = 0, pos = 0;
	if (pos == len)
		pos = 0, len = fread(buf, 1, buf_size, stdin);
	if (pos == len)
		return -1;
	return buf[pos++];
}

inline int readChar() {
	int c = getChar();
	while (c <= 32)
		c = getChar();
	return c;
}

template <class T>
inline T readInt() {
	int s = 1, c = readChar();
	T x = 0;
	if (c == '-')
		s = -1, c = getChar();
	while ('0' <= c && c <= '9')
		x = x * 10 + c - '0', c = getChar();
	return s == 1 ? x : -x;
}

/** Write */

static int write_pos = 0;
static char write_buf[buf_size];

inline void writeChar(int x) {
	if (write_pos == buf_size)
		fwrite(write_buf, 1, buf_size, stdout), write_pos = 0;
	write_buf[write_pos++] = x;
}

template <class T>
inline void writeInt(T x, char end) {
	if (x < 0)
		writeChar('-'), x = -x;

	char s[24];
	int n = 0;
	while (x || !n)
		s[n++] = '0' + x % 10, x /= 10;
	while (n--)
		writeChar(s[n]);
	if (end)
		writeChar(end);
}

inline void writeWord(const char *s) {
	while (*s)
		writeChar(*s++);
}

struct Flusher {
	~Flusher() {
		if (write_pos)
			fwrite(write_buf, 1, write_pos, stdout), write_pos = 0;
	}
} flusher;