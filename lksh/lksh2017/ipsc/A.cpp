#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

int main() {
	int t;
	cin >> t;
	while (t--) {
		int r, c;
		cin >> r >> c;
		cout << r << "\n";
		for (int i = 0; i < r; i++) cout << i << " " << i << "\n";
	}
	return 0;
}