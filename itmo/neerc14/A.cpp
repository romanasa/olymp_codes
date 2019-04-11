#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

#define TASK "alter"

int main() {
#ifndef HOME
	freopen(TASK".in", "r", stdin), freopen(TASK".out", "w", stdout);
#endif
	int n, m;
	
	cin >> n >> m;
	
	int cnt = n / 2 + m / 2;
	
	cout << cnt << "\n";
	for (int i = 2; i <= n; i += 2) cout << i << " " << 1 << " " << i << " " << m << "\n";
	for (int j = 2; j <= m; j += 2) cout << 1 << " " << j << " " << n << " " << j << "\n";
	return 0;
}