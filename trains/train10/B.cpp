#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;
 
typedef long long ll;
 
struct frac {
    ll a, b;
     
    frac() {}
    frac(ll a): a(a), b(1) {}
    frac(ll a, ll b): a(a), b(b) {}
     
    friend frac operator + (frac X, frac Y) {
        frac cur(X.a * Y.b + Y.a * X.b, X.b * Y.b);
        cur.norm();
        return cur;
    }
     
    friend frac operator - (frac X, frac Y) {
        frac cur(X.a * Y.b - Y.a * X.b, X.b * Y.b);
        cur.norm();
        return cur;
    }
     
    friend frac operator * (frac X, ll c) {
        frac cur(X.a * c, X.b);
        cur.norm();
        return cur;
    }
     
    friend frac operator / (frac X, ll c) {
        frac cur(X.a, X.b * c);
        cur.norm();
        return cur;
    }
     
    friend bool operator == (frac X, frac Y) {
        return X.a * Y.b == Y.a * X.b;
    }
     
    friend bool operator != (frac X, frac Y) {
        return X.a * Y.b != Y.a * X.b;
    }
     
    void norm() {
        ll t = __gcd(a, b);
        a /= t, b /= t;
        if (a < 0 && b < 0) a = -a, b = -a;
        else if (b < 0) a = -a, b = -b;
    }
     
    void out() { err("%I64d / %I64d", a, b); }
};
 
void no() {
    puts("No solution.");
    exit(0);
}
 
const int dd = 123;
frac A[dd][dd], B[dd][dd];
frac NONE(123456, 1);
 
int n, m;
int cnt;
 
bool check() {
    for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) if (A[i][j] == NONE) return false;
    for (int i = 0; i < n; i++) {
        if (m == 1) continue;
        frac cur = A[i][1] - A[i][0];
        int ok = 1;
        for (int j = 2; j < m; j++) ok &= (A[i][j] - A[i][j - 1] == cur);
        if (!ok) return false;
    }   
    for (int j = 0; j < m; j++) {
        if (n == 1) continue;
        frac cur = A[1][j] - A[0][j];
        int ok = 1;
        for (int i = 2; i < n; i++) ok &= (A[i][j] - A[i - 1][j] == cur);
        if (!ok) return false;
    }
    return true;
}
 
void out() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("%I64d", A[i][j].a);
            if (A[i][j].b > 1) printf("/%I64d", A[i][j].b);
            printf("%c", " \n"[j == m - 1]);
        }
    }
}
 
void finish() {
    if (!check()) no();
    out();
    exit(0);
}
 
void make1(int i) {
    int pos1 = -1, pos2 = -1;
    for (int j = 0; j < m; j++) if (A[i][j] != NONE) {
        if (pos1 == -1) pos1 = j;
        else pos2 = j;
    }
    if (pos1 == -1 || pos2 == -1) return;
     
    frac step = (A[i][pos2] - A[i][pos1]) / (pos2 - pos1);
    frac st = A[i][pos1] - step * pos1;
     
    for (int j = 0; j < m; j++) {
        if (A[i][j] == NONE) A[i][j] = st + step * j;
    }
}
 
void make2(int j) {
    int pos1 = -1, pos2 = -1;
    for (int i = 0; i < n; i++) if (A[i][j] != NONE) {
        if (pos1 == -1) pos1 = i;
        else pos2 = i;
    }
    if (pos1 == -1 || pos2 == -1) return;
     
    frac step = (A[pos2][j] - A[pos1][j]) / (pos2 - pos1);
    frac st = A[pos1][j] - step * pos1;
     
    for (int i = 0; i < n; i++) {
        if (A[i][j] == NONE) A[i][j] = st + step * i;
    }
}
 
int main() {
    scanf("%d %d", &n, &m);
     
    frac val(0);
     
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            char s[4];
            scanf("%s", s);
            if (s[0] == '.') A[i][j] = NONE;
            else val = A[i][j] = frac(atoi(s)), cnt++;
        }       
    }
 
    if (cnt <= 1) {
        for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) A[i][j] = val;
        out();
        return 0;
    }
     
    for (int i = 0; i < n; i++) make1(i);
    for (int j = 0; j < m; j++) make2(j);
     
    for (int i = 0; i < n; i++) make1(i);
    for (int j = 0; j < m; j++) make2(j);
     
    int fi = -1, li = -1;
    int fj = -1, lj = -1;
     
    cnt = 0;
    for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) if (A[i][j] != NONE) {
        cnt++;
        if (fi == -1) fi = i;
        li = i;
    }
     
    for (int j = 0; j < m; j++) for (int i = 0; i < n; i++) if (A[i][j] != NONE) {
        if (fj == -1) fj = j;
        lj = j;
    }
     
    if (cnt == n * m) finish();
     
    if (fi == li) {
        make1(fi);
        for (int i = 0; i < n; i++) if (li != i)
            for (int j = 0; j < m; j++) A[i][j] = A[li][j];
        finish();
    }
     
    if (fj == lj) {
        make2(fj);
        for (int j = 0; j < m; j++) if (lj != j)
             for (int i = 0; i < n; i++) A[i][j] = A[i][lj];
        finish();
    }
     
    if (n == 2) {
        frac val1(0), val2(0);
        for (int j = 0; j < m; j++) if (A[0][j] != NONE) val1 = A[0][j];
        for (int j = 0; j < m; j++) if (A[1][j] != NONE) val2 = A[1][j];
         
         
        for (int j = 0; j < m; j++) if (A[0][j] == NONE) A[0][j] = val1;
        for (int j = 0; j < m; j++) if (A[1][j] == NONE) A[1][j] = val2;
        finish();
    }
     
    if (m == 2) {
        frac val1(0), val2(0);
        for (int j = 0; j < n; j++) if (A[j][0] != NONE) val1 = A[j][0];
        for (int j = 0; j < n; j++) if (A[j][1] != NONE) val2 = A[j][1];
         
         
        for (int j = 0; j < n; j++) if (A[j][0] == NONE) A[j][0] = val1;
        for (int j = 0; j < n; j++) if (A[j][1] == NONE) A[j][1] = val2;
        finish();
    }
     
     
     
    for (int i = 0; i < n; i++) copy(A[i], A[i] + m, B[i]);
 
    int ti = 0, tj = 0;
     
     
    while (1) {
        int ok = 1;
         
        if (A[ti][tj] != NONE || ti == 0 || tj == 0) ok = 0;
        int oki = 0, okj = 0;
        for (int j = 0; j < m; j++) oki |= (A[ti][j] != NONE);
        for (int i = 0; i < n; i++) okj |= (A[i][tj] != NONE);
        ok &= oki;
        ok &= okj;
         
        if (ok) break;
        tj++;
        if (tj == m) ti++, tj = 0;
    }
     
    assert(ti != -1 && tj != -1);
    err("ti = %d, tj = %d\n", ti, tj);
     
    for (int a = 0; a <= 100; a++) {
        for (int b = -100; b <= 100; b++) {
         
            if (b == 0) b++;
            if (__gcd(a, b) > 1) continue;
             
            A[ti][tj] = frac(a, b);
            A[ti][tj].norm();
             
            //err("A[%d][%d] = %d\n", fi, fj, a);
 
            for (int i = 0; i < n; i++) make1(i);
            for (int j = 0; j < m; j++) make2(j);
             
            for (int i = 0; i < n; i++) make1(i);
            for (int j = 0; j < m; j++) make2(j);
             
            int ok = 1;
            for (int i = 0; i < n && ok; i++) for (int j = 0; j < m && ok; j++) ok &= (A[i][j] != NONE);
            if (ok && check()) finish();
             
            for (int i = 0; i < n; i++) copy(B[i], B[i] + m, A[i]);
        }
    }
     
    no();
    return 0;
}