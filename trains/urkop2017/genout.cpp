#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

int R() { return (rand() << 16) | rand(); }

int main() {
	int n = (int)5e5;
	cout << n << "\n";
	for (int i = 0; i < n; i++) printf("%d ", R());
	return 0;
}