#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

typedef long long ll;

using namespace std;
int n;

#define TASK "cpr"

int main() {
#ifndef HOME
	freopen(TASK".in", "r", stdin), freopen(TASK".out", "w", stdout);
#endif
	scanf("%d", &n);
	
	if (n == 1) return 0 * puts("0");
	if (n == 2) return 0 * puts("1\n1 1 2");
	if (n == 3) return 0 * puts("2\n1 2 3\n2 2 3");
	
	printf("%d\n", n / 2 + 1);
	
	printf("%d %d %d\n", 1 + (n & 1), (n + 1) / 2, n);
	for (int a = n, b = 1 + (n & 1), c = 0; a > b; c = a, a--, b++) {
		printf("%d %d %d\n", a, b, c);
	}
	return 0;
}