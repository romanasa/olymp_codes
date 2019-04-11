#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

#define TASK "c"

int main() {
#ifndef HOME
	freopen(TASK".in", "r", stdin), freopen(TASK".out", "w", stdout);
#endif
	
	int n, x;
	cin >> n >> x;
	
	vector<int> t(n), p(n + 1);
	for (int i = 0; i < n; i++) cin >> t[i];
	for (int i = 0; i < n; i++) p[i + 1] = p[i] ^ t[i];
	
	
	int a = -1, b = -1;
	for (int len = 0; len < n; len++) {
		int ok = -1;
		for (int i = 0; i + len < n; i++) {
			int j = i + len;
			int cur = p[j + 1] ^ p[i];
			
			if (cur >= x) {
				ok = i;
				break;
			}
		}
		if (ok != -1) {
			a = len + 1, b = ok + 1;
		}
	}
	cout << b << " " << a << "\n";

	return 0;
}