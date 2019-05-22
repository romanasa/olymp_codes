#include <bits/stdc++.h>
#define ll long long
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)
using namespace std;
 
const int dd = (int)1e6 + 7;
 
struct ev {
    int x, tp, b, c;
    bool operator < (ev b) const {
        return x < b.x;
    }
} E[dd];
 
ll T[4 * dd], S[4 * dd];
 
void upd(int v, int tl, int tr, int pos, int val) {
    if (tl == tr) {
        T[v] += val, S[v] += 1ll * val * pos;
    } else {
        int tm = (tl + tr) / 2;
        if (pos <= tm)
            upd(v * 2, tl, tm, pos, val);
        else
            upd(v * 2 + 1, tm + 1, tr, pos, val);
        T[v] = T[v * 2] + T[v * 2 + 1];
        S[v] = S[v * 2] + S[v * 2 + 1];
    }
}
 
ll cur = 0, res = 0;
 
int get(int v, int tl, int tr, ll k) {
    if (tl == tr) {
        cur += T[v], res += S[v];
        return tl;
    }
    int tm = (tl + tr) / 2;
    if (T[v * 2 + 1] > k) 
        return get(v * 2 + 1, tm + 1, tr, k);
    cur += T[v * 2 + 1], res += S[v * 2 + 1];
    return get(v * 2, tl, tm, k - T[v * 2 + 1]);
}
 
ll getT(int v, int tl, int tr, int l, int r) {
    if (l == tl && r == tr)
        return T[v];
    int tm = (tl + tr) / 2;
    if (r <= tm)
        return getT(v * 2, tl, tm, l, r);
    if (l > tm)
        return getT(v * 2 + 1, tm + 1, tr, l, r);
    return getT(v * 2, tl, tm, l, tm) + getT(v * 2 + 1, tm + 1, tr, tm + 1, r);
}
 
ll getS(int v, int tl, int tr, int l, int r) {
    if (l == tl && r == tr)
        return S[v];
    int tm = (tl + tr) / 2;
    if (r <= tm)
        return getS(v * 2, tl, tm, l, r);
    if (l > tm)
        return getS(v * 2 + 1, tm + 1, tr, l, r);
    return getS(v * 2, tl, tm, l, tm) + getS(v * 2 + 1, tm + 1, tr, tm + 1, r);
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
 
 
#define TASK "fisher"
 
int main() {
#ifndef HOME
    freopen(TASK".in", "r", stdin), freopen(TASK".out", "w", stdout);
#endif
 
    int n, m, p;
    n = readInt(), m = readInt(), p = readInt();
    //scanf("%d %d %d", &n, &m, &p);
     
    int iE = 0;
    for (int i = 0; i < n; i++) {
        int x, a;
        //scanf("%d %d", &x, &a);
        x = readInt(), a = readInt();
        E[iE++] = { x, 0, a };  
    }
    for (int i = 0; i < m; i++) {
        int x, b, c;
        //scanf("%d %d %d", &x, &b, &c);
        x = readInt(), b = readInt(), c = readInt();
        E[iE++] = { x, 1, b, c };
    }
    sort(E, E + iE);
     
    ll t = 0, ans = 0;
    for (int i = 0; i < iE; i++) {
        if (E[i].tp == 0) {
            t += E[i].b;
        } else {
            upd(1, 0, dd, E[i].c, E[i].b);
        }
        cur = 0, res = 0;
        int j = get(1, 0, dd, t);
        res -= (cur - t) * j;       
        ans = max(ans, res - 1ll * E[i].x * p);
    }
    printf("%I64d\n", ans);
     
    return 0;
}