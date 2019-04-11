#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

int main() {
	int n;
	cin >> n;
	
	int c = 0;
	for (int i = 0; i < n; i++) {
		int t;
		cin >> t;
		c += (t % 2);
	}
	puts(c % 2 ? "NO" : "YES");
	return 0;
}