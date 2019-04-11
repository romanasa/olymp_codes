#include <bits/stdc++.h>
 
using namespace std;
 
typedef long long ll;
typedef unsigned long long ull;
 
const int LOG = 17;
const int N = 1 << LOG;
 
const int maxC = (int)5e4 + 7;
int rev[N + 1];
ll sum[maxC + 7];
 
typedef complex<long double> cmpl;
 
struct polynom {
    cmpl A[N + 1];
} p, Q, res, tmp;
 
const int mod = 786433;
const long double pi = atan2(1, 1) * 4.0;
 
void calc() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < LOG; j++) if ((i >> j) & 1)
            rev[i] |= (1 << (LOG - j - 1));
    }
}
 
long double sinQ[N + 1], cosQ[N + 1];
 
void fft(polynom &A, bool inv = false) {
    for (int i = 0; i < N; i++) if (i < rev[i]) swap(A.A[i], A.A[rev[i]]);
    for (int l = 2; l <= N; l *= 2) {
        int t = l / 2;
 
        cmpl wn(cosQ[l], inv ? -sinQ[l] : sinQ[l]);
 
        for (int i = 0; i < N; i += l) {
            cmpl w = 1;
            for (int j = 0; j < t; j++) {
                cmpl u = A.A[i + j];
                cmpl v = A.A[i + j + t] * w;
                A.A[i + j] = u + v;
                A.A[i + j + t] = u - v;
                w *= wn;
            }
        }
    }
    if (inv) for (int i = 0; i < N; i++) A.A[i] /= N;
}
 
void mul(polynom &A, polynom &B) {
    tmp = B;
    fft(A);
    fft(tmp);
 
    for (int i = 0; i < N; i++) A.A[i] *= tmp.A[i];
    fft(A, true);
   
 	for (int i = maxC; i < N; i++) A.A[i] = 0;
    for (int i = 0; i < maxC; i++) A.A[i] = (ll)(A.A[i].real() + 0.5) % mod;
}
 
int main() {
#ifdef WIN
    freopen("01", "r", stdin);
#endif // WIN
    ios_base::sync_with_stdio(0);
    cin.tie(0);
 
    calc();
 
    int n, k, q;
    cin >> n >> k >> q;
 
    for (int i = 0; i < n; i++) {
        int t;
        cin >> t;
        Q.A[t] += 1;
    }
 
    p = Q;
    res = Q;
 
    k--;
 
    int it = 0;
    while (k) {
        if (k & 1) mul(res, p);
        mul(p, p);
        k /= 2;
    }
    
    for (int i = 0; i + 1 < maxC; i++) {
        sum[i + 1] = sum[i] + (ll)(res.A[i].real() + 0.5) % mod;
        if (sum[i + 1] >= mod) sum[i + 1] -= mod;
    }
 
    while (q--) {
        int l, r;
        cin >> l >> r;
        cout << (sum[r + 1] - sum[l] + mod) % mod << "\n";
    }
 
    return 0;
}