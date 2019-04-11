#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

int main() {
	int x, a, b;
	cin >> x >> a >> b;
	puts(abs(x - a) < abs(x - b) ? "A" : "B");
	return 0;
}