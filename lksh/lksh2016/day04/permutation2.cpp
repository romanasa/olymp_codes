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

#include <ext/pb_ds/assoc_container.hpp>

using namespace __gnu_pbds;
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

#define TASK "permutation2"

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

const int MAX_MEM = 2e8;
int mpos = 0;
char mem[MAX_MEM];
inline void * operator new (size_t n){
    char *res = mem + mpos;
    mpos += n;
    assert(mpos <= MAX_MEM);
    return (void *)res;
}
inline void operator delete (void *) { }

struct node {
    tree<pair<int, int>, null_type, less<pair<int, int> >, rb_tree_tag, tree_order_statistics_node_update> S;

    int get(int x, int y) {
        return  S.order_of_key({ y + 1, -1 }) - S.order_of_key({ x, -1 });
    }
} T[4 * dd];

void build(int v, int tl, int tr, vector<int> &a) {

    if (tl == tr) {
        T[v].S.insert({ a[tl], tl });
    }
    else {
        int tm = (tl + tr) / 2;

        build(v * 2, tl, tm, a);
        build(v * 2 + 1, tm + 1, tr, a);

        for (auto x : T[v * 2].S) {
            T[v].S.insert(x);
        }
        for (auto x : T[v * 2 + 1].S) {
            T[v].S.insert(x);
        }
    }
}

void upd(int v, int tl, int tr, int pos, int old, int val) {
    if (tl != tr) {
        int tm = (tl + tr) / 2;

        if (pos <= tm)
            upd(v * 2, tl, tm, pos, old, val);
        else
            upd(v * 2 + 1, tm + 1, tr, pos, old, val);
    }

    T[v].S.erase({ old, pos });
    T[v].S.insert({ val, pos });
}

int get(int v, int tl, int tr, int l, int r, int x, int y) {
    if (l == tl && tr == r) {
        return T[v].get(x, y);
    }
    int tm = (tl + tr) / 2;
    if (r <= tm)
        return get(v * 2, tl, tm, l, r, x, y);
    if (l > tm)
        return get(v * 2 + 1, tm + 1, tr, l, r, x, y);

    return get(v * 2, tl, tm, l, tm, x, y) + get(v * 2 + 1, tm + 1, tr, tm + 1, r, x, y);
}

/** Interface */

inline int readChar();
template <class T = int> inline T readInt();
template <class T> inline void writeInt(T x, char end = 0);
inline void writeChar(int x);
inline void writeWord(const char *s);

int solve() {
    int n, k;
    n = readInt(), k = readInt();

    vector<int> G(n);

    forn(i, n) {
        G[i] = readInt();
    }

    build(1, 0, n - 1, G);

    while (k--) {
        string s;
        int x, y, l, r;

        char c = readChar();
        while (c != ' ') {
            s += c;
            c = readChar();
        }


        if (s == "GET") {
            l = readInt(), r = readInt(), x = readInt(), y = readInt();
            writeInt(get(1, 0, n - 1, l - 1, r - 1, x, y), '\n');
        }
        else {
            int a, b;
            a = readInt(), b = readInt();
            upd(1, 0, n - 1, a - 1, G[a - 1], b);
            G[a - 1] = b;
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
    while (c <= 32 && c != ' ')
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