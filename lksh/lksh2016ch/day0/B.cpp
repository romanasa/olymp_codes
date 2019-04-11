#include <bits/stdc++.h>

using namespace std;

int ok(int x) {
	int t = x, s = 0;
	while (x) {
		s += x % 10;
		x /= 10;
	}
	return t % s == 0;
}

int main() {
	int n;
	scanf("%d", &n);
	
	for (int t = 1; ; t++) {
		if (ok(t))
			n--;
		if (n == 0) {
			printf("%d", t);
			break;
		}
	}
	return 0;
}
