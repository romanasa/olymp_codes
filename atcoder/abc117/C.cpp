#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int k, n;
	cin >> k >> n;
	
	vector<int> x(n);
	for (int i = 0; i < n; i++) cin >> x[i];
	sort(x.begin(), x.end());
	
	vector<int> t(n - 1);
	for (int i = 0; i + 1 < n; i++) t[i] = x[i + 1] - x[i];
	
	int res = 0;
	sort(t.begin(), t.end());
	for (int i = 0; i + k < n; i++) res += t[i];
	cout << res << "\n";
	return 0;
}