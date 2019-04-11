#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

const int dd = (int)4e5 + 7;
int a[dd], b[dd];
long double cur[dd];

int main() {
	int n, T;
	scanf("%d %d", &n, &T);
	for (int i = 0; i < n; i++) scanf("%d", &a[i]);
	for (int i = 0; i < n; i++) scanf("%d", &b[i]);
	
	
	long double L = 0, R = 2e7;
	for (int it = 0; it < 200; it++) {
		long double m = (L + R) / 2;
		
		long double t = 0;
		for (int i = 0; i < n; i++) {
			cur[i] = min((long double)a[i], m / b[i]);
			t += cur[i] * cur[i] * b[i];
		}
		if (t <= T) L = m;
		else R = m;
	}
	
	for (int i = 0; i < n; i++) cur[i] = min((long double)a[i], L / b[i]);
	for (int i = 0; i < n; i++) printf("%.10f ", (double)cur[i]);

	return 0;
}