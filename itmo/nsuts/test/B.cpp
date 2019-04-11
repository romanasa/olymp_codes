#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

int main() {
#ifndef HOME
	freopen("input.txt", "r", stdin), freopen("output.txt", "w", stdout);
#endif
	vector<int> ans = { 0, 1, 0, 0, 0, 0, 1 };
	int n; cin >> n; n--;
	cout << ans[n] << "\n";
	return 0;
}