#include<bits/stdc++.h>
using namespace std;
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
    //Author: Sergey Kopeliovich (Burunduk30@gmail.com)
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

#define ff first
#define ss second
//vector<pair<int, int>> hist_sz;
int n, m, cnt;
const long long N = 4e5;
pair<int, int> z[N];
vector<pair<int, int>> hist;
int p[N];
int sz[N];
int it = 1;
map<long long, int> mp;
int to[N];
int get(int v)
{
	for (; v != p[v]; v = p[v]);
    return v;
}
void un(int a, int b)
{
    a = get(a);
    b = get(b);
    if(a == b)
        return;
    if(sz[a] < sz[b])
        swap(a, b);
    hist.push_back({a, sz[a]});
    hist.push_back({b, b});
    //hist.push_back({cnt, cnt});
    sz[a] += sz[b];
    p[b] = a;
    cnt--;
    return;
}
void dvdc(const int &l, const int &r)
{
    if(l == r)
    {
        if(z[l].ff == 0)
        {
            writeInt(cnt);
            writeChar('\n');
            //cout << cnt << '\n';
            return;
        }
        else
            return;
    }
    int mid = (l + r) >> 1;
    int beg = hist.size();
    for(int i = mid + 1; i <= r; ++i)
    {
        if(z[i].ff == 0)
            continue;
        if(to[i] < l)
        {
            un(z[i].ff, z[i].ss);
        }
    }
    dvdc(l, mid);
    while(hist.size() > beg)
    {
        p[hist.back().ff] = hist.back().ss;
        hist.pop_back();
        sz[hist.back().ff] = hist.back().ss;
        hist.pop_back();
        cnt++;
    }
    for(int i = l; i <= mid; ++i)
    {
        if(z[i].ff == 0)
            continue;
        if(to[i] > r)
        {
            un(z[i].ff, z[i].ss);
        }
    }
    dvdc(mid + 1, r);
    while(hist.size() > beg)
    {
        p[hist.back().ff] = hist.back().ss;
        hist.pop_back();
        sz[hist.back().ff] = hist.back().ss;
        hist.pop_back();
        cnt++;
    }
    return;
}
int main()
{
	n = readInt();
    m = readInt();
    //z.resize(m);
   // cin >> n >> m;
   //hist.reserve((int)5e6);
    for(int i = 1; i <= n; i++)
    {
        p[i] = i;
        sz[i] = 1;
    }
    if(m == 0)
        return 0;
    cnt = n;
    int x, y, e;
    char c;
    for(int i = 1; i <= m; i++)
    {
        c = readChar();
        if(c == '+')
        {
            //cin >> x >> y;
            x = readInt();
            y = readInt();
            if(x < y)
                swap(x, y);
            mp[x * N + y] = i - 1;
            to[i - 1] = N;
            z[i - 1] = {x, y};
        }
        if(c == '-')
        {
            //int x, y;
            //cin >> x >> y;
            x = readInt();;
            y = readInt();;
            if(x < y)
                swap(x, y);
            e = mp[x * N + y];
            to[e] = i - 1;
            to[i - 1] = e;
            z[i - 1] = {x, y};
        }
        if(c == '?')
        {
            z[i - 1] = {0, 0};
        }
    }
    dvdc(0, m - 1);
    return 0;
}