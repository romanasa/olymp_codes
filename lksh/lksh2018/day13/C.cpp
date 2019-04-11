#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

const int dd = (int)1e6 + 7;
int a[dd], b[dd];

double cur[dd];
pair<double, int> curA[dd];

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int n, k;
	cin >> n >> k;
	for (int i = 0; i < n; i++) cin >> a[i] >> b[i];
	double l = 0, r = 1e7;
	for (int it = 0; it < 100; it++) {
		double m = (l + r) / 2;
		for (int i = 0; i < n; i++) cur[i] = a[i] - m * b[i];
		nth_element(cur, cur + n - k, cur + n);
		if (accumulate(cur + n - k, cur + n, 0.0) >= 0) l = m;
		else r = m;
	}
	for (int i = 0; i < n; i++) curA[i] = { a[i] - l * b[i], i };
	nth_element(curA, curA + n - k, curA + n);
	for (int i = n - k; i < n; i++) cout << curA[i].second + 1 << " ";
	return 0;
}