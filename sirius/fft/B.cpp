#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

typedef complex<double> cmpl;

const int LOG = 20;
const int maxN = (1 << LOG);
const double pi = atan2(1, 1) * 4;

int rev[maxN + 1];

void FFT(cmpl *a, bool inv, int n) {
	for (int i = 0; i < n; i++) if (i < rev[i]) swap(a[i], a[rev[i]]);
	
	for (int l = 1; l < n; l *= 2) {
		for (int i = 0; i < n; i += 2 * l) {
			
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
	if (inv) for (int i = 0; i < n; i++) a[i] /= n;
}

cmpl A[maxN + 1], B[maxN + 1], C[maxN + 1];
int res[maxN];

int main() {
	for (int i = 0; i < maxN; i++) {
		for (int j = 0; j < LOG; j++) if ((i >> j) & 1)
			rev[i] ^= 1 << (LOG - j - 1);
	}

	string a;
	cin >> a;
	
	int n = (int)a.size();
	
	
	
	for (int i = 0; i < n; i++) C[i] = cmpl(a[i] - '0', a[n - i - 1] - '0');
	for (int i = n; i < n + n; i++) C[i] = a[i - n] - '0';
	
	FFT(C, false, maxN);
	
	for (int i = 1; i < maxN; i++) {
		A[i] = (C[i] + C[maxN - i]) / cmpl(2, 0);
		B[i] = (C[i] - C[maxN - i]) / cmpl(0, 2);
	}
	
	A[0] = (C[0] + C[0]) / cmpl(2, 0);
	B[0] = 0;
	
	for (int i = 0; i < maxN; i++) C[i] = A[i] * B[i];
	
	FFT(C, true, maxN);
	
	for (int i = 0; i < maxN; i++) res[i] = int(C[i].real() + 0.5);
	
	for (int i = 2 * n - 2; i > n - 1; i--) res[i - 1] += res[i] / 10, res[i] %= 10;
	for (int i = n - 1; i < 2 * n - 1; i++) printf("%d", res[i]);
	
	return 0;
}