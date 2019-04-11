#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

int main() {
	int n, m;
	cin >> n >> m;
	
	if (m == 0) return 0 * puts("NO");
	if (m == 1) return 0 * puts("NO");
	//if (n == 2) return 0 * puts("NO");
	if (m >= n * (n - 1) / 2 - 1) return 0 * puts("NO");
	puts("YES");
	return 0;
}