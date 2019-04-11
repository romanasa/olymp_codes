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

#define TASK "stars"

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

const int dd = 130;

/** Interface */

inline int readChar();
template <class T = int> inline T readInt();
template <class T> inline void writeInt(T x, char end = 0);
inline void writeChar(int x);
inline void writeWord(const char *s);

int T[dd][dd][dd];

struct fen {


    int f(int x) {
        return (x&-x);
    }

    void upd(int x, int y, int z, int val) {
        for (int i = x + 1; i < dd; i += f(i))
            for (int j = y + 1; j < dd; j += f(j))
                for (int k = z + 1; k < dd; k += f(k))
                    T[i][j][k] += val;
    }

    int get(int x, int y, int z) {
        int res = 0;
        for (int i = x + 1; i; i -= f(i))
            for (int j = y + 1; j; j -= f(j))
                for (int k = z + 1; k; k -= f(k))
                    res += T[i][j][k];
        return res;
    }
} F;



int solve() {
    int n;
    cin >> n;

    while (1) {
        int tp = readInt();

        if (tp == 3)
            break;

        if (tp == 1) {
            int x = readInt(), y = readInt(), z = readInt(), k = readInt();
            F.upd(x, y, z, k);
        }
        if (tp == 2) {
            int x1 = readInt(), y1 = readInt(), z1 = readInt(), x2 = readInt(), y2 = readInt(), z2 = readInt();

            int res1 = F.get(x2, y2, z2) - F.get(x2, y2, z1 - 1);
            int res2 = F.get(x1 - 1, y2, z2) - F.get(x1 - 1, y2, z1 - 1);
            int res3 = F.get(x2, y1 - 1, z2) - F.get(x2, y1 - 1, z1 - 1);
            int res4 = F.get(x1 - 1, y1 - 1, z2) - F.get(x1 - 1, y1 - 1, z1 - 1);

            int ans = res1 - res2 - res3 + res4;

            writeInt(ans, '\n');


        }
    }

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