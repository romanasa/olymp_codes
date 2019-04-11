#include <bits/stdtr1c++.h>

#define MAXN 200010
#define MAXQ 200010
#define MAXV 1000010
#define clr(ar) memset(ar, 0, sizeof(ar))
#define read() freopen("lol.txt", "r", stdin)

using namespace std;

const int block_size = 633;

long long res, out[MAXQ];
int n, q, ar[MAXN], val[MAXN], freq[MAXV];

struct query{
    int l, r, d, i;

    inline query() {}
    inline query(int a, int b, int c){
        i = c;
        l = a, r = b, d = l / block_size;
    }

    inline bool operator < (const query& other) const{
        if (d != other.d) return (d < other.d);
        return ((d & 1) ? (r < other.r) : (r > other.r));
    }
} Q[MAXQ];

void compress(int n, int* in, int* out){
    unordered_map <int, int> mp;
    for (int i = 0; i < n; i++) out[i] = mp.emplace(in[i], mp.size()).first->second;
}

inline void insert(int i){
    res += (long long)val[i] * (1 + 2 * freq[ar[i]]++);
}

inline void erase(int i){
    res -= (long long)val[i] * (1 + 2 * --freq[ar[i]]);
}


/** Interface */

inline int readChar();
template <class T = int> inline T readInt(); 
template <class T> inline void writeInt( T x, char end = 0 );
inline void writeChar( int x ); 
inline void writeWord( const char *s );


inline void run(){
    sort(Q, Q + q);
    int i, l, r, a = 0, b = 0;

    for (res = 0, i = 0; i < q; i++){
        l = Q[i].l, r = Q[i].r;
        while (a > l) insert(--a);
        while (b <= r) insert(b++);
        while (a < l) erase(a++);
        while (b > (r + 1)) erase(--b);
        out[Q[i].i] = res;
    }
    for (i = 0; i < q; i++) writeInt(out[i], '\n');
}

int main(){
    int n, i, j, k, a, b;

    n = readInt();
    q = readInt();
    for (i = 0; i < n; i++) val[i] = readInt();
    compress(n, val, ar);

    for (i = 0; i < q; i++){
        a = readInt();
        b = readInt();
        Q[i] = query(a - 1, b - 1, i);
    }

    run();
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
