#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__)
 
#include <ext/pb_ds/assoc_container.hpp>
 
using namespace std;
using namespace __gnu_pbds;
typedef long long ll;
 
 
typedef tree<ll, null_type, less<ll>, rb_tree_tag, tree_order_statistics_node_update> megaset;
 
const int MAX_MEM = 2e8;
char MEM[MAX_MEM];
int mpos = 0;
 
inline void* operator new (size_t n) {
    char *res = MEM + mpos;
    mpos += n;
    return (void*)res;
}
 
inline void operator delete (void*) {}
 
const int dd = (int)3e5 + 7;
pair<int, int> A[dd];
int col[dd], h[dd], tin[dd], tout[dd], p[dd];
megaset H[dd];
int tmm =  1;
 
int G[2 * dd], iG = 0;
int head[2 * dd], tail[2 * dd];
int to[2 * dd], nxt[2 * dd];
int nv = dd;
 
void add(int a, int b) {
    to[tail[a]] = b;
    nxt[tail[a]] = nv++;
    tail[a] = nxt[tail[a]];
}
 
void calc(int v, int pr) {
    p[v] = pr;
    tin[v] = tmm++;
    h[v] = (pr == -1 ? 0 : h[pr] + 1);
 
 
    for (int i = head[v]; i != tail[v]; i = nxt[i]) {
        calc(to[i], v);
    }
 
    tout[v] = tmm++;
}
 
inline int readChar() {
    int c = getchar();
    while (c <= 32)
        c = getchar();
    return c;
}
 
inline int readInt() {
    int c = readChar();
    int res = 0;
    while ('0' <= c && c <= '9')
        res = res * 10 + c - '0', c = getchar();
    return res;
}
 
char buf[10];
 
inline void writeInt(int x) {
    int pos = 0;
    while (x)
        buf[pos++] = '0' + x % 10, x /= 10;
    if (!pos) buf[pos++] = '0';
    while (pos--) putchar(buf[pos]);
}
 
int main() {
    int n, m, k;
    n = readInt(), m = readInt(), k = readInt();
 
    int C = 2 * n;
 
    for (int i = 0; i < n; i++)
        head[i] = tail[i] = i;
 
    for (int i = 0; i < n; i++) {
        col[i] = readInt();
    }
 
    add(0, 1);
    for (int i = 0; i < n - 2; i++) {
        int t = readInt();
        add(t - 1, i + 2);
    }
 
    for (int i = 0; i < m; i++) {
        A[i].first = readInt(), A[i].second = readInt();
    }
 
    for (int i = 0; i < n; i++) {
        G[iG++] = (col[i]);
    }
    for (int i = 0; i < m; i++) {
        G[iG++] = (A[i].second);
    }
 
    sort(G, G + iG);
 
    iG = unique(G, G + iG) - G;
 
    for (int i = 0; i < n; i++) {
        col[i] = lower_bound(G, G + iG, col[i]) - G;
    }
    for (int i = 0; i < m; i++) {
        A[i].second = lower_bound(G, G + iG, A[i].second) - G;
    }
 
    calc(0, -1);
    for (int i = 0; i < n; i++) {
        H[h[i]].insert( 1ll * col[i] * C + tin[i] );
    }
 
    int ans = 0;
    for (int v = 0; v < n; v++) {
        if (p[v] != -1)
            ans += (col[v] == col[p[v]]);
        int it1 = H[h[v] + 1].order_of_key(1ll * col[v] * C + tin[v]);
        int it2 = H[h[v] + 1].order_of_key(1ll * col[v] * C +  tout[v]);
        ans += (it2 - it1);
    }
 
    ans /= 2;
 
    for (int i = 0; i < m; i++) {
        int v = A[i].first - 1;
 
        if (col[v] == A[i].second) {
            writeInt(ans);
            putchar('\n');
            continue;
        }
 
        if (p[v] != -1)
            ans -= (col[v] == col[p[v]]);
 
        ll cc = 1ll * col[v] * C;
 
        int it1 = H[h[v] + 1].order_of_key(cc + tin[v]);
        int it2 = H[h[v] + 1].order_of_key(cc + tout[v]);
 
        ans -= (it2 - it1);
 
        H[h[v]].erase(cc + tin[v]);
        col[v] = A[i].second;
        cc = 1ll * col[v] * C;
        H[h[v]].insert(cc + tin[v]);
 
 
        if (p[v] != -1)
            ans += (col[v] == col[p[v]]);
        it1 = H[h[v] + 1].order_of_key(cc + tin[v]);
        it2 = H[h[v] + 1].order_of_key(cc + tout[v]);
 
        ans += (it2 - it1);
        writeInt(ans);
        putchar('\n');
    }
    return 0;
}