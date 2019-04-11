#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

#define TASK "solitaire"

int main() {
#ifndef HOME
	freopen(TASK".in", "r", stdin), freopen(TASK".out", "w", stdout);
#endif
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int t;
	cin >> t;
	
	while (t--) {
		int n, f, k;
		cin >> n >> f >> k;
		
		if (n > 50) puts("YES");
		else {
			ll p = 1;
			for (int i = 0; i < n - 1; i++) p *= 2;
			p *= (f + 1);
			if (p >= k - 1) puts("YES");
			else puts("NO");
		}
	}

	return 0;
}