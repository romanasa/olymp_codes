#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

int main() {
	int x, n;
	cin >> x >> n;
	
	int cur = 0;
	
	for (int i = 0; i < n; i++) {
		cur += x;
		int t;
		cin >> t;
		cur -= t;
	}
	cur += x;
	cout << cur << "\n";
	return 0;
}