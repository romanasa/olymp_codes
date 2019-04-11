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

#define TASK "centroid"

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

/** Interface */

inline int readChar();
template <class T = int> inline T readInt();
template <class T> inline void writeInt(T x, char end = 0);
inline void writeChar(int x);
inline void writeWord(const char *s);

vector<vector<int> > e;

int level[dd], p[dd], color[dd];
int D[20][dd];

map<int, pair<int, int> > T[dd];

int find(int v, int &center, int size, int pr) {
    int sz = 1;

    for (int to : e[v]) {
        if (to != pr && level[to] == -1) {
            sz += find(to, center, size, v);
        }
    }

    if (center == -1 && (sz * 2 >= size || pr == -1))
        center = v;

    return sz;
}

void upd(int v, int key, pair<int, int> val) {
    
    auto it = T[v].find(key);

    if (it != T[v].end()) {
        T[v][key] = min(it->second, val);
    } else {
        T[v][key] = val;
    }
}


void calc(int v, int pr, int d, int root, int h) {
    upd(root, color[v], { d, v });
    D[h][v] = d;

    for (int to : e[v]) {
        if (to != pr && level[to] == -1) {
            calc(to, v, d + 1, root, h);
        }
    }
}

void build(int v, int h, int size, int pr) {
    int center = -1;
    find(v, center, size, -1);

    level[center] = h;
    p[center] = pr;

    calc(center, -1, 0, center, h);

    for (int to : e[center]) {
        if (to != pr && level[to] == -1)
            build(to, h + 1, size / 2, center);
    }
}

int solve() {
    int n;
    cin >> n;
    
    e.resize(n);

    fornn(i, 1, n) {
        int t = readInt();
        e[t].push_back(i);
        e[i].push_back(t);
    }

    forn(i, n) {
        level[i] = -1, p[i] = -1;
    }


    forn(i, n) {
        color[i] = readInt();
    }

    build(0, 1, n, -1);

    int m = readInt();

    while (m--) {
        int v, q;
        v = readInt(), q = readInt();

        int x = v;

        auto cur = mp((int)inf, (int)inf);

        while (x != -1) {
            if (T[x].count(q))
                cur = min(cur, mp(T[x][q].first + D[level[x]][v], T[x][q].second));
            x = p[x] ;
        }

        if (cur.first == inf)
            writeInt(-1, ' ');
        else
            writeInt(cur.first, ' ');
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