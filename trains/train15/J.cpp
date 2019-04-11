#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

int main() {
	int s, n;
	cin >> s >> n;
	for (int i = 0; i < n; i++) {
		int x;
		cin >> x;
		if (x * (n - i) == s) putchar('=');
		else if (x * (n - i) < s) putchar('<');
		else putchar('>');
		s -= x;
	}
	putchar('\n');
	return 0;
}