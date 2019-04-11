#include <bits/stdc++.h>

using namespace std;

int main() {
	int n;
	scanf("%d", &n);
	
	int minx = 11, maxx = -1, s = 0;
	for (int i = 0; i < n; i++) {
		int t;
		scanf("%d", &t);
		s += t;
		minx = min(minx, t);
		maxx = max(maxx, t);
		break;
	}
	printf("%.10f", 1.0 * (s - minx - maxx) / (n - 2));
	return 0;
}
