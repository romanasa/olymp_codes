#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;
typedef complex<double> cmpl;

const int dd = (int)3e5 + 1;
const int mod = 2999;
const double pi = atan2(1, 1) * 4.0;

int N = 1, LOG;

cmpl A[dd], B[dd], C[dd], tmp[dd];
int rev[dd];

void calc() {
	for (int i = 0; i < N; i++) rev[i] = (rev[i >> 1] >> 1) + ((i & 1) << (LOG - 1));
}

void upd(int len) {
	if (N > len) return;
	while ((1 << LOG) <= len) LOG++;
	N = (1 << LOG);
	calc();
}

void FFT(cmpl *a, bool inv) {
	for (int i = 0; i < N; i++) if (i < rev[i]) swap(a[i], a[rev[i]]);
	
	for (int l = 1; l < N; l *= 2) {
		for (int i = 0; i < N; i += 2 * l) {
			
			double ang = pi / l * (inv ? -1 : 1);
			cmpl wn(cos(ang), sin(ang)), w = 1;
			
			for (int j = 0; j < l; j++) {
				cmpl u = a[i + j], v = a[i + j + l] * w;
				a[i + j] = u + v;
				a[i + j + l] = u - v;
				w *= wn;
			}
		}
	}
	if (inv) for (int i = 0; i < N; i++) a[i] /= N;
}

void mul(cmpl *A, cmpl *B) {
	if (1ll * N * N <= 500 * 500) {
		fill(C, C + N, 0);
		for (int i = 0; i < N; i++) 
			for (int j = 0; i + j < N; j++)
				C[i + j] += A[i] * B[j];
	} else {
    	FFT(A, false);
    	FFT(B, false);
    	for (int i = 0; i < N; i++) C[i] = A[i] * B[i];
    	FFT(C, true);
	}
	for (int i = 0; i < N; i++) A[i] = ((ll)(C[i].real() + 0.5)) % mod;
}

void sq(cmpl *A) {
	if (1ll * N * N <= 500 * 500) {
		fill(tmp, tmp + N, 0);
		for (int i = 0; i < N; i++) 
			for (int j = 0; i + j < N; j++)
				tmp[i + j] += A[i] * A[j];
		copy(tmp, tmp + N, A);
	} else {
    	FFT(A, false);
    	for (int i = 0; i < N; i++) A[i] = A[i] * A[i];
    	FFT(A, true);
	}
	for (int i = 0; i < N; i++) A[i] = ((ll)(A[i].real() + 0.5)) % mod;
}

#define TASK "chimichangas"

int main() {
#ifndef HOME
	freopen(TASK".in", "r", stdin), freopen(TASK".out", "w", stdout);
#endif
	int n, k;
	scanf("%d %d", &n, &k);
	
	int C = 0;
	for (int i = 0; i < n; i++) {
		int t;
		scanf("%d", &t);
		A[t] = 1;
		C = max(C, t);
	}
	upd(C + 1);
	
	copy(A, A + N, B);
	
	int lenA = C + 1;
	int lenB = C + 1;
	
	k--;
	for (; k; k >>= 1) {
		if (k & 1) {
			copy(A, A + N, tmp);
			upd(lenA + lenB);
			mul(B, tmp);
			lenB += lenA;
		}
		upd(lenA + lenA);
		sq(A);
		lenA += lenA;
	}
	
	int q;
	scanf("%d", &q);
	while (q--) {
		int x;
		scanf("%d", &x);
		if (x >= N) printf("0\n");
		else printf("%d\n", (int)B[x].real());
	}
	return 0;
}