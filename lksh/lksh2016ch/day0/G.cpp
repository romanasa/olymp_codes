#include <bits/stdc++.h>

using namespace std;

int main() {
	long long x;
	long long ans = 1;
	
	scanf("%lld", &x);
	
	for (int t = 2; t <= 1000; t++) {
		int j = 1;
		
		while (x % t == 0)
			x /= t, j++;
		ans *= j;
	}
	printf("%lld", ans);
	return 0;
}
