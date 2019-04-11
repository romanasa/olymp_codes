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

#define TASK "assignment"

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

const int dd = 1e4 + 7;

struct edge {
    int v, to, c, f, w, back, ind;
};

vector<vector<edge> > E;

void add(int a, int b, int c, int w, int ind) {
    int ia = E[b].size(), ib = E[a].size();

    edge cur{ a, b, c, 0,  w, ia, ind };
    edge rev{ b, a, 0, 0, -w, ib, -1 };

    E[a].push_back(cur);
    E[b].push_back(rev);
}

int n, m;
int N;

int G[dd];
int used[dd], d[dd];
pair<int, int> p[dd];

ll findflow(int s, int t) {

    ll cost = 0;
    ll flow = 0;
    
    forn(i, N)
        G[i] = inf;

    queue<int> q;

    q.push(s);
    used[s] = true;
    G[s] = 0;

    while (q.size()) {
        int v = q.front();

        used[v] = false;
        q.pop();

        forn(i, E[v].size()) {

            auto &e = E[v][i];

            if (e.f < e.c && G[e.to] > G[v] + e.w) {

                G[e.to] = G[v] + e.w;

                if (!used[e.to]) {
                    q.push(e.to);
                    used[e.to] = true;
                }
            }
        }
    }

    while (1) {

        forn(i, N)
            d[i] = inf, p[i] = { -1, -1 }, used[i] = 0;

        d[s] = 0;

        while (1) {
            int v = -1;
            forn(i, N) {
                if (!used[i] && d[i] != inf && (v == -1 || d[i] < d[v]))
                    v = i;
            }
            if (v == -1)
                break;
            used[v] = 1;

            forn(i, E[v].size()) {

                auto &e = E[v][i];

                if (e.f < e.c && d[e.to] > d[v] + e.w + G[v] - G[e.to]) {
                    p[e.to] = mp(v, i);
                    d[e.to] = d[v] + e.w + G[v] - G[e.to];
                }
            }

        }

        if (p[t].first == -1) {
            break;
        }

        int add = inf;

        for (int i = t; p[i].first != -1; i = p[i].first) {
            add = min(add, E[p[i].first][p[i].second].c - E[p[i].first][p[i].second].f);
        }

        for (int i = t; p[i].first != -1; i = p[i].first) {
            auto &e = E[p[i].first][p[i].second];

            cost += 1ll * add * e.w;

            e.f += add;
            E[e.to][e.back].f -= add;
        }

        flow += add;

        if (add == 0)
            break;

        forn(i, N)
            G[i] += d[i];
    }

    return cost;
}

/** Interface */

inline int readChar();
template <class T = int> inline T readInt();
template <class T> inline void writeInt(T x, char end = 0);
inline void writeChar(int x);
inline void writeWord(const char *s);

int solve() {
    n = readInt();

    N = n + n + 7;

    E.resize(N);

    forn(i, n) {
        forn(j, n) {
            int t = readInt();

            add(i, j + n, 1, t, (i * n + j));
        }
    }

    forn(i, n) {
        add(n + n, i, 1, 0, -1);
        add(n + i, n + n + 1, 1, 0, -1);
    }

    ll ans = findflow(n + n, n + n + 1);

    writeInt(ans, '\n');

    vector<int> res;

    forn(v, n) {
        for (auto &e : E[v]) {
            if (e.f > 0) {
                int i = e.ind / n, j = e.ind % n;
                writeInt(i + 1, ' ');
                writeInt(j + 1, '\n');
            }
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
