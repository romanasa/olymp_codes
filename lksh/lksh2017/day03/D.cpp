#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

int main() {
	int n, t;
	scanf("%d %d", &n, &t);
	
	vector<int> d(n), s(n);
	
	for (int i = 0; i < n; i++) {
		cin >> d[i] >> s[i];
	}
	
	double l = -(ll)1e18;
	double r = (ll)1e18;
	
	for (int it = 0; it < 200; it++) {
		double m = (l + r) / 2;
		
		double cur = 0;
		
		int ok = 1;
		
		for (int i = 0; i < n; i++) {
			if (s[i] + m <= 0) { ok = 0; break; }
			cur += d[i] / (s[i] + m);
		}
		
		if (!ok) {
			l = m;
			continue;
		}
		
		if (cur >= t) l = m;
		else r = m;
	}
	printf("%.10f\n", l);
	
	return 0;
}