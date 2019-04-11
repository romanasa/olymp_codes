#include <bits/stdc++.h>
#define ll long long
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

inline int readChar();
template <class T = int> inline T readInt();
template <class T> inline void writeInt( T x, char end = 0 );
inline void writeChar( int x );
inline void writeWord( const char *s );

const int dd = (int)3e6 + 7;

ll A[dd], B[dd];
ll ans = (ll)2e18 + 1;
ll a, b;

int n;

__int128 get(ll x) {

	for (int i = 0; i < n; i++)
		A[i] = B[i] - i * x;

	nth_element(A, A + n / 2, A + n);

	__int128 cur = 0;

	for (int i = 0; i < n; i++) {
		cur += A[n / 2] > A[i] ? A[n / 2] - A[i] : A[i] - A[n / 2];
	}

	if (ans > cur) {
		ans = cur;
		a = A[n / 2];
		b = x;
	}

	return cur;
}

int main() {
	n = readInt();

	for (int i = 0; i < n; i++) {
		int x = readInt();
		B[i] = x;
	}

	ll l = -(ll)2e9 + 1, r = (ll)2e9 + 1;


	while (r - l > 1) {
		ll m = (l + r) / 2;
		__int128 t1 = get(m), t2 = get(m + 1);
		if (t1 > t2) {
			l = m;
		} else {
			r = m;
		}
	}

	writeInt(a, ' ');
	writeInt(b, '\n');

    //err("\nTIME = %.3f\n", clock() * 1.0 / CLOCKS_PER_SEC);

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
