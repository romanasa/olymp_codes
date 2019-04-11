#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)
 
typedef long long ll;
 
using namespace std;
 
const int dd = (int)2e5 + 7;
 
char C[dd];
int A[dd], B[dd];
int G[2 * dd], iG;
 
struct SegmentTree {
    int mn[8 * dd], mx[8 * dd];
 
    SegmentTree() {
        fill(mx, mx + 8 * dd, -1e9 - 1), fill(mn, mn + 8 * dd, 1e9 + 1);
    }
 
    void upd(int v, int tl, int tr, int pos, int val) {
        if (tl == tr) {
            mn[v] = mx[v] = val;
        } else {
            int tm = (tl + tr) / 2;
            if (pos <= tm) upd(v * 2, tl, tm, pos, val);
            else upd(v * 2 + 1, tm + 1, tr, pos, val);
            mn[v] = min(mn[v * 2], mn[v * 2 + 1]);
            mx[v] = max(mx[v * 2], mx[v * 2 + 1]);
        }
    }
 
    pair<int, int> get(int v, int tl, int tr, int pos, int x) {
        if (tl == tr) return { G[tl], G[mn[v]] };
        pair<int, int> cur(-1, -1);
        int tm = (tl + tr) / 2;
 
        if (pos <= tm && mx[v * 2] >= x)
            cur = get(v * 2, tl, tm, pos, x);
 
        if (cur.first != -1) return cur;
 
        if (mx[v * 2 + 1] >= x)
            cur = get(v * 2 + 1, tm + 1, tr, pos, x);
        return cur;
    }
 
    pair<int, int> get2(int v, int tl, int tr, int pos, int x) {
        if (tl == tr) return { G[tl], G[mn[v]] };
        pair<int, int> cur(-1, -1);
        int tm = (tl + tr) / 2;
 
        if (pos >= tm + 1 && mn[v * 2 + 1] <= x)
            cur = get2(v * 2 + 1, tm + 1, tr, pos, x);
 
        if (cur.first != -1) return cur;
 
        if (mn[v * 2] <= x)
            cur = get2(v * 2, tl, tm, pos, x);
        return cur;
    }
 
} F;
 
void add(int x, int y) {
    x = lower_bound(G, G + iG, x) - G, y = lower_bound(G, G + iG, y) - G;
    F.upd(1, 0, iG, x, y);
}
 
pair<int, int> get(int x, int y) {
    x = lower_bound(G, G + iG, x) - G, y = lower_bound(G, G + iG, y) - G;
    return F.get(1, 0, iG, x, y);
}
 
pair<int, int> get2(int x, int y) {
    x = lower_bound(G, G + iG, x) - G, y = lower_bound(G, G + iG, y) - G;
    return F.get2(1, 0, iG, x, y);
}
 
set<int> S1, S2;
 
void check3(int a, int b) {
    int na = *S1.lower_bound(a);
    int nb = *S2.lower_bound(b);
 
    auto c = get(a, b);
 
    if (c.first == -1) {
        puts("NE");
        return;
    }
 
    puts((c.first <= na && c.second <= nb) ? "DA" : "NE");
}
 
void check4(int a, int b) {
    int pa = *(--S2.upper_bound(a - 1)) + 1;
    int pb = *(--S1.upper_bound(b - 1)) + 1;
 
    //err("pa = %d, a = %d, pb = %d, b = %d\n", pa, a, pb, b);
 
    auto c = get2(a, b);
 
    if (c.first == -1) {
        puts("NE");
        return;
    }
    puts((c.first >= pa && c.second >= pb) ? "DA" : "NE");
}
 
int main() {
    int n, m;
    scanf("%d %d", &n, &m);
 
    S1.insert(-1);
    S1.insert(n);
 
    S2.insert(n - 1);
    S2.insert(n + n);
 
    G[iG++] = 0, G[iG++] = n;
    G[iG++] = n + n;
 
    for (int i = 0; i < m; i++) {
        scanf("\n%c %d %d", &C[i], &A[i], &B[i]);
        A[i]--, B[i]--;
 
        G[iG++] = A[i];//, G[iG++] = A[i] + 1;
        G[iG++] = B[i];//, G[iG++] = B[i] + 1;
    }
 
    sort(G, G + iG);
    iG = unique(G, G + iG) - G;
 
 
    for (int i = 0; i < m; i++) {
        char c = C[i];
        int a = A[i], b = B[i];
 
        if (c == 'A') {
            add(a, b);
            add(b, a);
        }
 
        if (c == 'Q') {
 
            if (a == b) {
                puts("DA");
                continue;
            }
 
            if (a < n && b >= n) {
                check3(a, b);
            }
            if (a >= n && b < n) {
                check4(a, b);
            }
 
            if (a < n && b < n) {
                if (a < b) {
                    int na = *S1.lower_bound(a);
                    puts(b <= na ? "DA" : "NE");
                } else {
                    auto c = get(a, n);
                    int na = *S1.lower_bound(a);
                    if (c.first == -1 || c.first > na) puts("NE");
                    else check4(c.second, b);
                }
            }
 
            if (a >= n && b >= n) {
                if (a < b) {
                    int pa = *(--S2.upper_bound(a - 1)) + 1;
                    auto c = get2(a, n - 1);
                    if (c.first == -1 || c.first < pa) puts("NE");
                    else check3(c.second, b);
                } else {
                    int pa = *(--S2.upper_bound(a - 1)) + 1;
                    puts(b >= pa ? "DA" : "NE");
                }
            }
        }
 
        if (c == 'B') {
            if (a > b) swap(a, b);
 
            if (b < n) S1.insert(a);
            else S2.insert(a);
        }
    }
 
    return 0;
}