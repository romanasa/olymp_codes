#define _CRT_SECURE_NO_WARNINGS
#pragma comment(linker, "/STACK:66777216")
#include <iostream>
#include <cstdio>
#include <cmath>
#include <vector>
#include <ctime>
#include <map>
#include <set>
#include <string>
#include <queue>
#include <deque>
#include <cassert>
#include <cstdlib>
#include <bitset>
#include <algorithm>
#include <string>
#include <list>
#include <fstream>
#include <cstring>
#include <sstream>
#include <numeric>
#include <complex>

using namespace std;

typedef unsigned long long ull;
typedef long long ll;
typedef long double ld;

#define forn(i, n) for (int i = 0; i < (int)n; i++)
#define fornn(i, q, n) for (ll i = q; i < (ll)n; i++)
#define mp make_pair
#define pk push_back
#define all(v) v.begin(), v.end()
#define times clock() * 1.0 / CLOCKS_PER_SEC

#define TASK "robots"

const double eps = 1e-7;
const double pi = acos(-1.0);

const ll INF = (ll)2e9 + 1;
const ll LINF = (ll)8e18;
const ll inf = (ll)2e9 + 1;
const ll linf = (ll)8e18;
const ll MM = (ll)1e9 + 7;

int solve();
void gen();

int main()
{
#ifdef HOME
    freopen("input.txt", "r", stdin), freopen("output.txt", "w", stdout);
#else
    freopen(TASK".in", "r", stdin), freopen(TASK".out", "w", stdout);
    //freopen("input.txt", "r", stdin), freopen("output.txt", "w", stdout), freopen("test.txt", "w", stderr);
#endif
    solve();
    return 0;
}

const int dd = 1e5 + 7;

struct cmpl {
    double a, b;
    cmpl() {}
    cmpl(double a, double b) : a(a), b(b) {}
    inline cmpl operator + (cmpl t) {
        return cmpl(a + t.a, b + t.b);
    }
    inline cmpl operator - (cmpl t) {
        return cmpl(a - t.a, b - t.b);
    }
    inline cmpl operator * (cmpl t) {
        return cmpl(a * t.a - b * t.b, a * t.b + b * t.a);
    }
    inline cmpl operator / (double t) {
        return cmpl(a / t, b / t);
    }
};

const int LOG = 20;

int R[1 << LOG];
double sinphi[LOG], cosphi[LOG];
cmpl wp[1 << (LOG - 1)];

inline void FFT(cmpl *a, int k, bool rev) {
    int N = 1 << k;
    forn(i, N) {
        int j = R[i];
        if (i < j)
            swap(a[i], a[j]);
    }

    for (int L = 1, lg = 0; L < N; L <<= 1, lg++) {
        cmpl wn(cosphi[lg], sinphi[lg] * (rev ? -1 : 1));

        wp[0] = cmpl(1, 0);

        for (int l = 1; l < L; l++)
            wp[l] = wp[l - 1] * wn;

        for (int i = 0; i < N; i += 2 * L) {
            for (int j = 0; j < L; j++) {
                cmpl u = a[i + j];
                cmpl v = a[i + j + L] * wp[j];

                a[i + j] = u + v;
                a[i + j + L] = u - v;
            }
        }
    }
    if (rev) {
        forn(i, N)
            a[i].a /= N;
    }
}

cmpl A[1 << LOG], B[1 << LOG], C[1 << LOG];

const int MAX_MEM = 1e8;
int mpos = 0;
char mem[MAX_MEM];
inline void * operator new (size_t n){
    char *res = mem + mpos;
    mpos += n;
    return (void *)res;
}
inline void operator delete (void *) { }

/** Interface */

inline int readChar();
template <class T = int> inline T readInt();
template <class T> inline void writeInt(T x, char end = 0);
inline void writeChar(int x);
inline void writeWord(const char *s);

int solve() {


    int n = readInt();

    int N = 1 << LOG;

    for (int i = 1, j = 0; i < N; i++) {
        int bit = N >> 1;
        for (; j >= bit; bit >>= 1)
            j -= bit;
        j += bit;	
        R[i] = j;
    }

    for (int L = 1, i = 0; L < N; L <<= 1, i++) {
        sinphi[i] = sin(pi / L);
        cosphi[i] = cos(pi / L);
    }


    const char * name = "ACGT";

    forn(i, n) {
        char c = readChar();
        int t = strchr(name, c) - name;
        A[(i << 2) + t] = A[(i << 2) + t + (n << 2)] = cmpl(1, 0);
    }

    forn(i, n) {
        char c = readChar();
        int t = strchr(name, c) - name;
        B[(n << 2) - (i << 2) - 1 - t] = cmpl(1, 0);
    }

    forn(i, N) {
        C[i].a = A[i].a;
        C[i].b = B[i].a;
    }

    FFT(C, LOG, false);

    fornn(i, 1, N) {
        cmpl X = C[N - i];
        cmpl Y(C[i].a, -C[i].b);

        A[N - i] = (X + Y) / 2;
        B[N - i] = (X - Y) / 2;
        swap(B[N - i].a, B[N - i].b);
        B[N - i].b *= -1;
    }

    A[0] = (C[0] + cmpl(C[0].a, -C[0].b)) / 2;
    B[0] = (C[0] - cmpl(C[0].a, -C[0].b)) / 2;
    swap(B[0].a, B[0].b);
    B[0].b *= -1;

    forn(i, N)
        A[i] = A[i] * B[i];
    FFT(A, LOG, true);

    int ans = -1, pos = 0;

    for (int i = 4 * n - 1; i < 8 * n; i += 4) {
        if (round(A[i].a) > ans) {
            ans = round(A[i].a);
            pos = (i - 4 * n + 1) / 4;
        }
    }

    writeInt(ans, ' ');
    writeInt(pos, '\n');
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