#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

typedef complex<double> cmpl;

const int LOG = 3;
const int maxN = (1 << LOG) + 1;
const double pi = atan2(1, 1) * 4;

int rev[maxN];
cmpl A[maxN];

void fft(cmpl *a, bool inv, int n) {
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

int main() {
	for (int i = 0; i < maxN; i++) {
		for (int j = 0; j < LOG; j++) if ((i >> j) & 1)
			rev[i] ^= 1 << (LOG - j - 1);
	}
	
	srand(time(0));
	int n = 8;
	for (int i = 0; i < n; i++) {
		A[i] = rand() % n;
	}
	
	
	for (int i = 0; i < n; i++) cout << A[i].real() << ", "; cout << "\n";
	
	fft(A, false, n);
	for (int i = 0; i < n; i++) A[i] *= sqrt(n);
	
	double res = 0;
	for (int i = 0; i < n; i++) res += (A[i].real() * A[i].real() + A[i].imag() + A[i].imag());	
	printf("%.10f\n", res);
	
	fft(A, false, n);
	for (int i = 0; i < n; i++) A[i] *= sqrt(n);

	for (int i = 0; i < n; i++) cout << A[i].real() / (n * n) << ", ";
	
	return 0;
}