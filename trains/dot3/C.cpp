#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)
 
using namespace std;
 
typedef long long ll;
 
const int dd = (int)1e5 + 1;
pair<int, int> P[dd];
 
#define x first
#define y second
 
const int maxL = (int)4e5 + 1;
 
const int MAX_MEM = (int)1e8;
char MEM[MAX_MEM];
int mpos;
 
inline void* operator new(size_t n) {
    char *res = MEM + mpos;
    mpos += n;
    return (void*)res;
}
 
inline void operator delete(void*) {}
 
struct magic {
    int T[4 * maxL], P[4 * maxL];
 
    void upd(int v, int tl, int tr, int l, int r, int val) {
        if (tl == l && tr == r) {
            P[v] += val;
            T[v] += val;
        } else {
            int tm = (tl + tr) / 2;
 
            if (r <= tm) upd(v * 2, tl, tm, l, r, val);
            else if (l > tm) upd(v * 2 + 1, tm + 1, tr, l, r, val);
            else upd(v * 2, tl, tm, l, tm, val), upd(v * 2 + 1, tm + 1, tr, tm + 1, r, val);
 
            T[v] = min(T[v * 2], T[v * 2 + 1]);
            T[v] += P[v];
        }
    }
 
    void clear() {
        memset(T, 0, sizeof(T));
        memset(P, 0, sizeof(P));
    }
 
    int get() {
        return T[1];
    }
} T;
 
int n, L, W, H;
 
struct ev {
    int tp, y1, y2;
};
 
vector<ev> E[maxL];
 
int Gx[maxL], Gy[maxL];
int ix, iy;
 
const int BN = 16;
const int maxC = 1 << BN;
int cnt[maxC + 1];
int tmp[maxL];
 
void mysort(int *a, int n) {
    for (int t = 0; t < 2; t++) {
        #define GET(i) ((a[i] >> (t * BN)) & (maxC - 1))
        memset(cnt, 0, sizeof(cnt));
        for (int i = 0; i < n; i++)
          cnt[GET(i) + 1]++;
        for (int i = 0; i + 1 < maxC; i++)
          cnt[i + 1] += cnt[i];
        for (int i = 0; i < n; i++)
          tmp[cnt[GET(i)]++] = a[i];
        for (int i = 0; i < n; i++)
          a[i] = tmp[i];
    }
}
 
bool check(int m) {
    //err("check %d\n", m);
    for (int i = 0; i < maxL; i++) E[i].clear();
 
    ix = 0, iy = 0;
 
    Gx[ix++] = (0), Gx[ix++] = (L - W);
    Gy[iy++] = (0), Gy[iy++] = (L - H);
 
    for (int i = 0; i < m; i++) {
        int x1 = max(P[i].x - W + 1, 0);
        int y1 = max(P[i].y - H + 1, 0);
        int x2 = min(P[i].x - 1, L - W);
        int y2 = min(P[i].y - 1, L - H);
 
        if (x1 <= x2 && y1 <= y2) {
            if (x1 > 0) Gx[ix++] = (x1 - 1);
            Gx[ix++] = (x1), Gx[ix++] = (x2);
            //if (x2 < L - W) Gx[ix++] = (x2 + 1);
 
            if (y1 > 0) Gy[iy++] = (y1 - 1);
            Gy[iy++] = (y1), Gy[iy++] = (y2);
            //if (y2 < L - H) Gy[iy++] = (y2 + 1);
        }
    }
 
 
    mysort(Gx, ix), mysort(Gy, iy);
    ix = (unique(Gx, Gx + ix) - Gx);
    iy = (unique(Gy, Gy + iy) - Gy);
 
    //err("Gx = {"); for (int x : Gx) err(" %d,", x); err(" }\n");
    //err("Gy = {"); for (int x : Gy) err(" %d,", x); err(" }\n");
 
    for (int i = 0; i < m; i++) {
        int x1 = max(P[i].x - W + 1, 0);
        int y1 = max(P[i].y - H + 1, 0);
        int x2 = min(P[i].x - 1, L - W);
        int y2 = min(P[i].y - 1, L - H);
 
        if (x1 <= x2 && y1 <= y2) {
 
 
            //err("(%d, %d, %d, %d), ", x1, y1, x2, y2);
 
            x1 = lower_bound(Gx, Gx + ix, x1) - Gx;
            x2 = lower_bound(Gx, Gx + ix, x2) - Gx;
 
            y1 = lower_bound(Gy, Gy + iy, y1) - Gy;
            y2 = lower_bound(Gy, Gy + iy, y2) - Gy;
 
            //err("(%d, %d, %d, %d)\n", x1, y1, x2, y2);
 
            E[x1].push_back({ 0, y1, y2 });
            E[x2].push_back({ 1, y1, y2 });
        }
    }
 
    int N = (int)iy - 1;
 
    T.clear();
    for (int i = 0; i < ix; i++) {
        //err("i = %d\n", i);
 
        for (auto c : E[i]) if (c.tp == 0) {
            //err("1, 0, %d, %d, %d, 1\n", L - H, c.y1, c.y2, 1);
            T.upd(1, 0, N, c.y1, c.y2, 1);
        }
 
        if (T.get() == 0) return false;
        //err("ok2\n");
        for (auto c : E[i]) if (c.tp == 1) {
            T.upd(1, 0, N, c.y1, c.y2, -1);
        }
    }
    //err("ok\n");
    return true;
}
 
/** Interface */

inline int readChar();
template <class T = int> inline T readInt(); 
template <class T> inline void writeInt( T x, char end = 0 );
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


int main() {
    //scanf("%d %d %d %d", &n, &L, &W, &H);
    n = readInt(), L = readInt(), W = readInt(), H = readInt();
 
    for (int i = 0; i < n; i++) {
        //scanf("%d %d", &P[i].x, &P[i].y);
        P[i].x = readInt(), P[i].y = readInt();
    }
    int l = 0, r = n + 1;
    while (r - l > 1) {
        int m = (l + r) / 2;
        if (check(m))
            r = m;
        else
            l = m;
    }
    printf("%d\n", (r == n + 1 ? -1 : r));
    return 0;
}