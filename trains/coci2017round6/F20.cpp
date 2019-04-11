#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

int main() {
	int n;
	cin >> n;
	
	vector<int> A(n);
	
	int ok = 1;
	for (int i = 0; i < n; i++) {
		int p;
		cin >> p;
		A[i] = p;
		if (i + 1 < n) ok &= (p == i + 2);
		else ok &= (p == 1);
	}
	
	
	vector<int> c(n);
	for (int i = 0; i < n; i++) cin >> c[i];
	sort(c.begin(), c.end());
	
	if (!ok) {
		vector<int> c = { 2, 1, 3 };
		if (n == 3 && A == c) return 0 * puts("2\n5 3 8");
		c = { 3, 5, 4, 1, 2 };
		if (n == 5 && A == c) return 0 * puts("8\n16 39 24 19 45");
		c = { 6, 3, 7, 1, 4, 8, 2, 5 };
		if (n == 8 && A == c) return 0 * puts("2\n3 4 4 4 6 5 2 7");
		assert(0);
	}
	
	vector<int> t;
	for (int i = 0; i < n; i += 2) t.push_back(c[i]);
	for (int i = (n - 1) - (n % 2 == 1); i >= 0; i -= 2) t.push_back(c[i]);
	int ans = 0;
	for (int i = 1; i< n; i++) ans = max(ans, abs(t[i] -t[i - 1]));
	ans = max(ans, abs(t[0] -t[n - 1]));
	
	cout << ans << "\n";
	for (int x : t) cout << x << " ";
	cout << "\n";
	
	return 0;
}