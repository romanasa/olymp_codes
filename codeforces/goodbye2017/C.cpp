#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

int main() {
	int n, r;
	cin >> n >> r;
	
	vector<int> x(n);
	vector<double> y(n);
	for (int i = 0; i < n; i++) cin >> x[i];
	
	for (int i = 0; i < n; i++) {
		y[i] = r;
		for (int j = 0; j < i; j++) {
			if (abs(x[i] - x[j]) > 2 * r) continue;
			double cur = y[j] + sqrt(4 * r * r - abs(x[i] - x[j]) * abs(x[i] - x[j]));
			y[i] = max(y[i], cur);
		}
	}
	cout.precision(10);
	cout << fixed;
	for (int i = 0; i < n; i++) cout << y[i] << " ";
	return 0;
}