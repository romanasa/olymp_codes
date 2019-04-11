#pragma GCC optimize("Ofast,unroll-loops")
#pragma GCC target("sse,sse2,sse3,popcnt,tune=native")
#include <bits/stdc++.h>
using namespace std;

/**
 * Author: Sergey Kopeliovich (Burunduk30@gmail.com)
 */

#define VERSION "0.1.5"

#include <cassert>
#include <cstdio>
#include <algorithm>

/** Fast allocation */

#ifdef FAST_ALLOCATOR_MEMORY
        int allocator_pos = 0;
        char allocator_memory[(int)FAST_ALLOCATOR_MEMORY];
        inline void * operator new ( size_t n ) {
                char *res = allocator_memory + allocator_pos;
                allocator_pos += n;
                assert(allocator_pos <= (int)FAST_ALLOCATOR_MEMORY);
                return (void *)res;
        }
        inline void operator delete ( void * ) noexcept { }
        //inline void * operator new [] ( size_t ) { assert(0); }
        //inline void operator delete [] ( void * ) { assert(0); }
#endif

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


typedef long long ll;

ll sz = 1;
vector<vector<ll> >t;
ll n;

inline void build(ll v, ll tl, ll tr, vector<ll> &A)
{
    if (tl == tr)
    {
        if (tl < n)
            t[v].push_back(A[tl]);
        return;
    }
    ll tm = (tl + tr) / 2;
    build(v * 2, tl, tm, A);
    build(v * 2 + 1, tm + 1, tr, A);
    merge(t[v * 2].begin(), t[v * 2].end(), t[v * 2 + 1].begin(), t[v * 2 + 1].end(), back_inserter(t[v]));
}

inline ll km(vector<ll> &a, ll x)
{
    auto it = lower_bound(a.begin(), a.end(), x);
    if (it != a.end() && *it <= x)
        it--;
    ll ans = it - a.begin();
    if (ans < 0)
    {
        assert(false);
    }
    return it - a.begin();
}

inline ll kb(vector<ll> &a, ll x)
{
    return a.end() - upper_bound(a.begin(), a.end(), x);
}

vector<ll> A;

inline ll kolm(ll x, ll L, ll R)
{
    L += sz;
    R += sz;
    ll ans = 0;
    while (L <= R)
    {
        if (L % 2 != 0)
        {
            ans += km(t[L], x);
            L++;
        }
        if (R % 2 == 0)
        {
            ans += km(t[R], x);
            R--;
        }
        L /= 2;
        R /= 2;
    }
    return ans;
}

inline ll kolb(ll x, ll L, ll R)
{
    L += sz;
    R += sz;
    //cout << "L = " << L << "  R = " << R << "  x = " << x << endl;
    ll ans = 0;
    while (L <= R)
    {
        //cout << "L = " << L << "  R = " << R << endl;
        if (L % 2 != 0)
        {
            ans += kb(t[L], x);
            L++;
        }
        if (R % 2 == 0)
        {
            ans += kb(t[R], x);
            R--;
        }
        L /= 2;
        R /= 2;
    }
    return ans;
}

ll t1;

ll G = 0;

bool comp(pair<pair<int, int>, int> a, pair<pair<int, int>, int> b)
{
    if (a.first.first / t1 < b.first.first / t1)
        return true;
    if (a.first.first / t1 > b.first.first / t1)
        return false;
    if (a.first.second < b.first.second)
    {
        if (G == 1)
        {
            G ^= 1;
            return true;
        }
        G ^= 1;
        return false;
    }
    if (G == 0)
    {
        G ^= 1;
        return true;
    }
    G ^= 1;
    return false;
}

ll L = 0, R = 0, a = 0;

inline void l_r()
{
    ll x = kolm(A[L], L + 1, R);
    a -= x;
    L++;
}

inline void l_l()
{
    ll x = kolm(A[L - 1], L, R);
    a += x;
    L--;
}

inline void rr()
{
    ll x = kolb(A[R + 1], L, R);
    a += x;
    R++;
}

inline void rl()
{
    ll x = kolb(A[R], L, R - 1);
    a -= x;
    R--;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    n = readInt();
    A.resize(n);
    while (sz < n)
        sz *= 2;
    t.resize(sz * 2);
    for (int i = 0; i < A.size(); i++)
    {
        A[i] = readInt();
        A[i]--;
    }

    build(1, 0, sz - 1, A);

    ll m = readInt();
    t1 = sqrt(n * n / m) * 1.5;

    vector<pair<pair<int, int>, int> > z(m);
    for (int i = 0; i < m; i++)
    {
        z[i].first.first = readInt();
        z[i].first.second = readInt();
        z[i].first.first--;
        z[i].first.second--;
        z[i].second = i;
    }

    stable_sort(z.begin(), z.end(), &comp);

    vector<int> ans(m);

    for (int i = 0; i < z.size(); i++)
    {
        int l1 = z[i].first.first;
        int r1 = z[i].first.second;
        int nu = z[i].second;
        
        if (R > r1) {
        	R = L - 1;
        	a = 0;	
        	
        }
        
        while (L < l1)
        {
            l_r();
        }
        while (L > l1)
        {
            l_l();
        }
        while (R < r1)
        {
            rr();
        }
        ans[nu] = a;
    }
    for (int i = 0; i < ans.size(); i++)
    {
        writeInt(ans[i], ' ');
    }
}