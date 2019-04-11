#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <algorithm>
#include <string>
#include <cmath>
#include <cstdio>
#include <iomanip>
#include <fstream>
#include <cstring>
#include <unordered_set>
#include <unordered_map>
#include <ctime>
using namespace std;

typedef long long ll;

#ifdef DEBUG
        const int MAXN = 10;
#else
        const int MAXN = 2e6;
#endif

int n;
int color[MAXN];
vector<int> g[MAXN];
int tin[MAXN];
int tout[MAXN];
int eul[MAXN];
int eulsz;
int val[MAXN];
int dp[MAXN];
int last[MAXN];
int ans[MAXN];

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


inline void init() {
        for (int i = 0; i < MAXN; i++) {
                g[i].clear();
        }
        eulsz = 0;
        memset(dp, -1, sizeof(dp));
        memset(last, -1, sizeof(last));
}

void dfs(int v, int p = -1) {
        eul[eulsz++] = v;
        tin[v] = eulsz - 1;
        for (auto to : g[v]) {
                if (to == p)
                        continue;
                dfs(to, v);
                eul[eulsz++] = v;
        }
        tout[v] = eulsz - 1;
}

struct Q {
        int l, r, id;
        Q() {}
        Q(int a, int b, int c) {
                l = a, r = b, id = c;
        }
};

int f[MAXN];

void upd(int a, int x) {
        for (int i = a; i < MAXN; i = i | (i + 1)) {
                f[i] += x;
        }
}

int get(int a) {
        int ans = 0;
        for (int i = a; i >= 0; i = (i & (i + 1)) - 1) {
                ans += f[i];
        }
        return ans;
}

inline void solve() {
        init();
        int root = -1;
        for (int i = 0; i < n; i++) {
                int a, b;
                a = readInt(), b = readInt();
                a--, b--;
                if (a < 0)
                        root = i;
                else
                        g[a].push_back(i);
                color[i] = b;
        }
        dfs(root);
        vector<Q> query(n);
        int queryNum = 0;
        for (int i = 0; i < eulsz; i++) {
                int it = eul[i];
                if (i == tin[it]) {
                        query[queryNum++]  = Q(tin[it], tout[it], it);
                }
                val[i] = color[it];
        }
        int pnt = 0;
        for (int i = eulsz - 1; i >= 0; i--) {
                dp[i] = last[val[i]];
                last[val[i]] = i;
        }
        for (int i = 0; i < n; i++) {
                if (last[i] != -1)
                        upd(last[i], 1);
        }
        for (int i = 0; i < eulsz; i++) {
                while (pnt < n && query[pnt].l == i) {
                        ans[query[pnt].id] = get(query[pnt].r);
                        pnt++;
                }
                upd(i, -1);
                if (dp[i] != -1)
                        upd(dp[i], 1);
        }
        for (int i = 0; i < n; i++) {
            writeInt(ans[i], '\n');
        }
}

signed main() {
        n = readInt();
        solve();
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
