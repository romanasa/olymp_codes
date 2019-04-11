#include "web.h"
#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)
 
using namespace std;
 
typedef long long ll;
 
const int dd = (int)2e5 + 1;
int A[dd], R[dd];
int n, m;
const int maxC = 1296000;
 
const int LOG = 17;
 
int sA[LOG][dd];
int sR[LOG][dd];
int lg[dd];
 
int mmax(int a, int b) { return a > b ? a : b; }
int mmin(int a, int b) { return a < b ? a : b; }
 
void init(int c, int *r, int l, int *a) {
    copy(a, a + l, A);
    copy(r, r + c, R);
 
    n = c, m = l;
 
    for (int i = 0; i < m; i++)
        A[i + m] = A[i] + maxC;
 
    for (int i = 2; i < dd; i++) lg[i] = lg[i >> 1] + 1;
 
    for (int it = 0; it < LOG; it++) {
        if (it == 0) {
            for (int i = 0; i < n; i++) sR[0][i] = R[i + 1] - R[i];
            for (int i = 0; i < 2 * m; i++) sA[0][i] = A[i + 1] - A[i];
        } else {
            int len = (1 << (it - 1));
            for (int i = 0; i + (1 << it) <= n; i++)
                sR[it][i] = mmax(sR[it - 1][i], sR[it - 1][i + len]);
            for (int i = 0; i + (1 << it) <= 2 * m; i++)
                sA[it][i] = mmax(sA[it - 1][i], sA[it - 1][i + len]);
        }
    }
}
 
int getA(int i, int j) {
    int t = lg[j - i + 1];
    return mmax(sA[t][i], sA[t][j - (1 << t) + 1]);
}
 
 
int get(int i, int j) {
    if (i == j) return 0;
    return mmin(getA(i, j - 1), getA(j, m + i - 1));
}
 
int getd(int i, int j) {
    if (i >= j) return 0;
    int t = lg[j - i];
    return mmax(sR[t][i], sR[t][j - (1 << t)]);
}
 
void solve(int q, int *x1, int *y1, int *x2, int *y2, long long *res) {
 
    for (int i = 0; i < q; i++) {
        if (x1[i] > x2[i]) swap(x1[i], x2[i]);
        if (y1[i] > y2[i]) swap(y1[i], y2[i]);
 
        int alpha = get(y1[i], y2[i]);
 
        int l = 0, r = x1[i];
 
        if (r > 1 && 1ll * getd(1, x1[i]) * maxC <= 1ll * R[1] * alpha)
            r = 1;
 
        if (l + 1 < x1[i] &&
            1ll * getd(x1[i] - 1, x1[i]) * maxC > 1ll * R[x1[i] - 1] * alpha)
            l = x1[i] - 1;
 
 
        while (r - l > 1) {
            int M = (l + r) / 2;
            if (1ll * getd(M, x1[i]) * maxC <= 1ll * R[M] * alpha)
                r = M;
            else
                l = M;
        }
 
        int j = r;
        if (j && 1ll * (R[j] - R[j - 1]) * maxC < 1ll * R[j] * alpha)
            j--;
 
        ll t1 = 1ll * getd(j, x2[i]) * maxC;
        ll t2 = 1ll * R[j] * alpha;
 
        res[i] = (t1 > t2 ? t1 : t2);
    }
}