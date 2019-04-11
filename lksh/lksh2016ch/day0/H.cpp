#include <bits/stdc++.h>

using namespace std;

int main() {
	int h, w;
	scanf("%d %d", &h, &w);
	
	long long ans = 0;
	for (int i = 0; i < h; i++)
		for (int j = 0; j < w; j++) {
			ans += 1ll * (h - i) * (w - j);
		}
	printf("%lld", ans);
	return 0;
}
