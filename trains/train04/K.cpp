#define _CRT_SECURE_NO_WARNINGS
#pragma comment(linker, "/STACK:256000000")
#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <bitset>
#include <sstream>
#include <fstream>
#include <ctime>
#include <cstring>
#include <numeric>
#include <queue>
#include <cassert>
#include <unordered_map>
#include <ext/pb_ds/assoc_container.hpp>

using namespace __gnu_pbds;
using namespace std;

typedef long long ll;
typedef long double ld;

#define TASK "sea"

int solve();

int main() {
#ifdef HOME
	//freopen("input.txt", "r", stdin), freopen("output.txt", "w", stdout);
#else
	//freopen(TASK".in", "r", stdin), freopen(TASK".out", "w", stdout);
#endif
	solve();
}

const int dd = (int)2e5 + 7;

tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> T[4 * dd];

/** Begin fast allocation */
const int MAX_MEM = 2e8;
int mpos = 0;
char mem[MAX_MEM];
inline void * operator new ( size_t n ) {
	char *res = mem + mpos;
	mpos += n;
	assert(mpos <= MAX_MEM);
	return (void *)res;
}
inline void operator delete ( void * ) { } // обязательно!

void upd(int v, int tl, int tr, int x, int y) {
	if (tl != tr) {
		int tm = (tl + tr) / 2;
		if (x <= tm)
			upd(v * 2, tl, tm, x, y);
		else
			upd(v * 2 + 1, tm + 1, tr, x, y);
	}
	T[v].insert(y);
}

int get(int v, int tl, int tr, int x, int y, int a, int b) {
	if (x > y)
		return 0;
	
	if (tl == x && tr == y) {
		return T[v].order_of_key(b + 1) - T[v].order_of_key(a);
	}
	int tm = (tl + tr) / 2;	
	return get(v * 2, tl, tm, x, min(y, tm), a, b) +
		get(v * 2 + 1, tm + 1, tr, max(tm + 1, x), y, a, b);
}

inline int readChar();
template <class T = int> inline T readInt(); 
template <class T = ll> inline void writeInt( T x, char end = 0 );
inline void writeChar( int x ); 
inline void writeWord( const char *s );

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

inline void writeChar( int x ) {
	if (write_pos == buf_size)
		fwrite(write_buf, 1, buf_size, stdout), write_pos = 0;
	write_buf[write_pos++] = x;
}

template <class T> 
inline void writeInt( T x, char end ) {
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

inline void writeWord( const char *s ) {
	while (*s)
		writeChar(*s++);
}

struct Flusher {
	~Flusher() {
		if (write_pos)
			fwrite(write_buf, 1, write_pos, stdout), write_pos = 0;
	}
} flusher;

struct st {
	int a, b, c;
	inline bool operator < (st m) const {
		return a < m.a;
	}
} A[dd];

int solve() {
	tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> S1, S2;
    int n = readInt();
	for (int i = 0; i < n; ++i) {
		A[i].a = readInt(), A[i].b = readInt(), A[i].c = readInt(); 
	}
	sort(A, A + n);
	ll ans = 0;
	for (int i = n - 1; i >= 0; --i) {
		ans += S1.order_of_key(A[i].b);
		ans += S2.order_of_key(A[i].c);
		ans -= get(1, 0, n, 0, A[i].b - 1, 0, A[i].c - 1);
		S1.insert(A[i].b);
		S2.insert(A[i].c);
		upd(1, 0, n, A[i].b, A[i].c);
	}
	writeInt(ans, '\n');
	return 0;
}