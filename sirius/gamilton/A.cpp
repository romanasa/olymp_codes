#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

int main() {
	int n, m;
	cin >> n >> m;
	swap(n, m);
	for (int i = n; i >= 1; i--) {
		if (i & 1) for (int j = 1; j <= m; j++) {
			cout << j << " " << i << "\n";
		} else for (int j = m; j >= 1; j--) {
			cout << j << " " << i << "\n";
		}
	}
	return 0;
}