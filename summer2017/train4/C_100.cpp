#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)
 
typedef long long ll;
 
using namespace std;
 
const int dd = (int)3e6 + 7;
const int maxC = (int)1e5 + 1;
 
struct pt {
    int x, y, ind;
} P[dd];
 
int n;
int U[dd], L[dd], R[dd], D[dd];
 
bool check(int x1, int y1, int x2, int y2) {
    for (int i = 0; i < n; i++)
        if (x1 <= P[i].x && P[i].x <= x2 &&
            y1 <= P[i].y && P[i].y <= y2)
            return true;
    return false;
}
 
void no() {
    exit(0 * puts("Unsafe"));
}
 
struct ev {
    int tp, y1, y2, ind;
};
 
vector<ev> E[dd];
vector<int> Q[dd];
int sum[dd], T[dd];
 
int get(int pos) {
    int res = 0;
    for (int i = pos + 1; i; i -= (i&-i)) res += T[i];
    return res;
}
 
void upd(int pos, int val) {
    for (int i = pos + 1; i < dd; i += (i&-i)) T[i] += val;
}
 
int get(int l, int r) {
    return get(r) - get(l - 1);
}
 
int main() {
    scanf("%d", &n);
 
    int old = n;
 
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &P[i].x, &P[i].y);
        P[i].ind = i;
        Q[P[i].x].push_back(P[i].y);
    }
 
    P[n] = { 0, maxC, n }; n++;//n - 2
    P[n] = { maxC, 0, n }; n++;//n - 1
 
    for (int i = 0; i < n; i++) {
        U[i] = L[i] = n - 2;
        D[i] = R[i] = n - 1;
    }
 
 
    sort(P, P + n, [](pt a, pt b) { return a.x == b.x ? a.y < b.y : a.x < b.x; });
    for (int i = 0; i + 1 < n; i++) {
        if (P[i].x == P[i + 1].x) {
            U[P[i].ind] = P[i + 1].ind;
            D[P[i + 1].ind] = P[i].ind;
        }
    }
 
    sort(P, P + n, [](pt a, pt b) { return a.y == b.y ? a.x < b.x : a.y < b.y; });
    for (int i = 0; i + 1 < n; i++) {
        if (P[i].y == P[i + 1].y) {
            R[P[i].ind] = P[i + 1].ind;
            L[P[i + 1].ind] = P[i].ind;
        }
    }
 
    //for (int i = 0; i < n; i++) {
    //    err("P[%d] = (%d, %d), ind = %d\n", i, P[i].x, P[i].y, P[i].ind);
    //    err("L = %d, R = %d, U = %d, D = %d\n", L[i], R[i], U[i], D[i]);
    //}
    sort(P, P + n, [](pt a, pt b) { return a.ind < b.ind; });
 
    for (int i = 0; i < n; i++) {
        if (P[i].ind >= old) continue;
        //err("\n\nind = %d\n", P[i].ind);
        {
            int x1 = P[i].x + 1, y1 = P[i].y + 1;
            int x2 = P[R[i]].x - 1, y2 = P[U[i]].y - 1;
            //err("ask1 %d, %d, %d, %d\n", x1, y1, x2, y2);
            if (x1 <= x2 && y1 <= y2) {
                E[x1].push_back({ 1, y1, y2, 4 * i });
                E[x2].push_back({ -1, y1, y2, 4 * i });
            }
        }
 
        {
            int x1 = P[L[i]].x + 1, y1 = P[i].y + 1;
            int x2 = P[i].x - 1, y2 = P[U[i]].y - 1;
            //err("ask2 %d, %d, %d, %d\n", x1, y1, x2, y2);
            if (x1 <= x2 && y1 <= y2) {
                E[x1].push_back({ 1, y1, y2, 4 * i + 1 });
                E[x2].push_back({ -1, y1, y2, 4 * i + 1 });
            }
        }
 
        {
            int x1 = P[L[i]].x + 1, y1 = P[D[i]].y + 1;
            int x2 = P[i].x - 1, y2 = P[i].y - 1;
            //err("ask3 %d, %d, %d, %d\n", x1, y1, x2, y2);
            if (x1 <= x2 && y1 <= y2) {
                E[x1].push_back({ 1, y1, y2, 4 * i + 2 });
                E[x2].push_back({ -1, y1, y2, 4 * i + 2 });
            }
        }
        {
            int x1 = P[i].x + 1, y1 = P[D[i]].y + 1;
            int x2 = P[R[i]].x - 1, y2 = P[i].y - 1;
            //err("ask4 %d, %d, %d, %d\n", x1, y1, x2, y2);
            //err("ask4 %d, %d, %d, %d\n", x1, y1, x2, y2);
            if (x1 <= x2 && y1 <= y2) {
                E[x1].push_back({ 1, y1, y2, 4 * i + 3 });
                E[x2].push_back({ -1, y1, y2, 4 * i + 3 });
            }
        }
    }
 
    for (int i = 0; i < dd; i++) {
        for (auto c : E[i]) {
            if (c.tp == 1) sum[c.ind] -= get(c.y1, c.y2);
        }
        for (int y : Q[i]) upd(y, 1);
        for (auto c : E[i]) {
            if (c.tp == -1 && sum[c.ind] + get(c.y1, c.y2) > 0) no();
        }
    }
 
    puts("Ok");
    return 0;
}