#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

#ifdef HOME
	const int dd = (int)1e3 + 1;
#else
	const int dd = (int)1e6 + 1;
#endif

int P[dd], R[dd], A[dd];
int h[dd], last[dd];
int sum[dd];

int get(int v) {
	return v == P[v] ? v : P[v] = get(P[v]);
}

void un(int a, int b) {
	a = get(a), b = get(b);
	if (a != b) {
		if (R[b] > R[a]) swap(a, b);
		P[b] = a, R[a] += R[b];
		if (h[A[b]] < h[A[a]]) A[a] = A[b];
	}
}

int headE[dd], tailE[dd];
int nxtE[2 * dd], toE[2 * dd];
int nvE;

void addE(int a, int b) {
	toE[tailE[a]] = b;
	nxtE[tailE[a]] = nvE++;
	tailE[a] = nxtE[tailE[a]];	
}

int col[dd];

void dfs(int v, int pr = -1) {
	h[v] = (pr == -1 ? 0 : h[pr] + 1);
	if (last[col[v]] != -1) sum[A[get(last[col[v]])]]--;
	last[col[v]] = v;
	
	/*for (int ind = headG[v]; ind != tailG[v]; ind = nxtG[ind]) {
		int c = toG[ind];
		if (used[c]) sum[A[get(c)]]--;
	}*/
	for (int ind = headE[v]; ind != tailE[v]; ind = nxtE[ind]) {
		dfs(toE[ind], v);	
		un(v, toE[ind]);
		sum[v] += sum[toE[ind]];
	}
}

/** Fast input-output */

template <class T = int> inline T readInt();						
inline double readDouble();
inline int readUInt();					 
inline int readChar(); // first non-blank character
inline void readWord( char *s ); 
inline bool readLine( char *s ); // do not save '\n'
inline bool isEof();
inline int getChar(); 
inline int peekChar();
inline bool seekEof();
inline void skipBlanks();

template <class T> inline void writeInt( T x, char end = 0, int len = -1 );
inline void writeChar( int x ); 
inline void writeWord( const char *s );
inline void writeDouble( double x, int len = 0 );
inline void flush();

static struct buffer_flusher_t {
	~buffer_flusher_t() {
		flush();
	}
} buffer_flusher;

int main() {
	int n = readInt();
	int root = -1;
	
	for (int i = 0; i < n; i++) headE[i] = tailE[i] = i;
	nvE = n;
	
	for (int i = 0; i < n; i++) {
		int p = readInt();
		col[i] = readInt() - 1;
		sum[i] = 1;
		if (p == 0) root = i;
		else addE(p - 1, i);
	}
	
	fill(last, last + n, -1);
	for (int i = 0; i < n; i++) P[i] = A[i] = i, R[i] = 1;
	dfs(root);
	
	for (int i = 0; i < n; i++) writeInt(sum[i], '\n');
	return 0;
}

/** Read */

static const int buf_size = 4096;

static unsigned char buf[buf_size];
static int buf_len = 0, buf_pos = 0;

inline bool isEof() {
	if (buf_pos == buf_len) {
		buf_pos = 0, buf_len = fread(buf, 1, buf_size, stdin);
		if (buf_pos == buf_len)
			return 1;
	}
	return 0;
}

inline int getChar() { 
	return isEof() ? -1 : buf[buf_pos++];
}

inline int peekChar() { 
	return isEof() ? -1 : buf[buf_pos];
}

inline bool seekEof() { 
	int c;
	while ((c = peekChar()) != -1 && c <= 32)
		buf_pos++;
	return c == -1;
}

inline void skipBlanks() {
	while (!isEof() && buf[buf_pos] <= 32U)
		buf_pos++;
}

inline int readChar() {
	int c = getChar();
	while (c != -1 && c <= 32)
		c = getChar();
	return c;
}

inline int readUInt() {
	int c = readChar(), x = 0;
	while ('0' <= c && c <= '9')
		x = x * 10 + c - '0', c = getChar();
	return x;
}

template <class T>
inline T readInt() {
	int s = 1, c = readChar();
	T x = 0;
	if (c == '-')
		s = -1, c = getChar();
	else if (c == '+')
		c = getChar();
	while ('0' <= c && c <= '9')
		x = x * 10 + c - '0', c = getChar();
	return s == 1 ? x : -x;
}

inline double readDouble() {
	int s = 1, c = readChar();
	double x = 0;
	if (c == '-')
		s = -1, c = getChar();
	while ('0' <= c && c <= '9')
		x = x * 10 + c - '0', c = getChar();
	if (c == '.') {
		c = getChar();
		double coef = 1;
		while ('0' <= c && c <= '9')
			x += (c - '0') * (coef *= 1e-1), c = getChar();
	}
	return s == 1 ? x : -x;
}

inline void readWord( char *s ) { 
	int c = readChar();
	while (c > 32)
		*s++ = c, c = getChar();
	*s = 0;
}

inline bool readLine( char *s ) { 
	int c = getChar();
	while (c != '\n' && c != -1)
		*s++ = c, c = getChar();
	*s = 0;
	return c != -1;
}

/** Write */

static int write_buf_pos = 0;
static char write_buf[buf_size];

inline void writeChar( int x ) {
	if (write_buf_pos == buf_size)
		fwrite(write_buf, 1, buf_size, stdout), write_buf_pos = 0;
	write_buf[write_buf_pos++] = x;
}

inline void flush() {
	if (write_buf_pos) {
		fwrite(write_buf, 1, write_buf_pos, stdout), write_buf_pos = 0;
		fflush(stdout);
	}
}

template <class T> 
inline void writeInt( T x, char end, int output_len ) {
	if (x < 0)
		writeChar('-'), x = -x;

	char s[24];
	int n = 0;
	while (x || !n)
		s[n++] = '0' + x % 10, x /= 10;
	while (n < output_len)
		s[n++] = '0';
	while (n--)
		writeChar(s[n]);
	if (end)
		writeChar(end);
}

inline void writeWord( const char *s ) {
	while (*s)
		writeChar(*s++);
}

inline void writeDouble( double x, int output_len ) {
	if (x < 0)
		writeChar('-'), x = -x;
	int t = (int)x;
	writeInt(t), x -= t;
	writeChar('.');
	for (int i = output_len - 1; i > 0; i--) {
		x *= 10;
		t = std::min(9, (int)x);
		writeChar('0' + t), x -= t;
	}
	x *= 10;
	t = std::min(9, (int)(x + 0.5));
	writeChar('0' + t);
}
