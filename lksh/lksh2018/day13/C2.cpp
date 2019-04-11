#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

const int dd = (int)1e6 + 1;
int a[dd], b[dd], P[dd];

int main() {
	int n, k;
	cin >> n >> k;
	
	for (int i = 0; i < n; i++) cin >> a[i] >> b[i];
	for (int i = 0; i < n; i++) P[i] = i;
	
	sort(P, P + n, [](int i, int j) {
		return 1ll * a[i] * b[j] > 1ll * a[j] * b[i];
	});
	for (int i = 0; i < k; i++) cout << P[i] + 1 << " ";
	return 0;
}