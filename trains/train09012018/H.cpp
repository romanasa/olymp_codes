#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

#define TASK "painting"

int main() {
#ifndef HOME
	freopen(TASK".in", "r", stdin), freopen(TASK".out", "w", stdout);
#endif
	int n, m, q;
	cin >> n >> m >> q;
	
	ll a0 = n, a1 = 0, a2 = 0;
	ll b0 = m, b1 = 0, b2 = 0;
	
	set<int> A, B;
	
	while (q--) {
		char c;
		int x;
		cin >> c;
		
		if (c != '?') cin >> x;
		
		if (c == 'h' && !A.count(x)) {
			
			if (x > 0) {
			if (A.count(x - 1)) a1--, a2++;
			else a0--, a1++;
			}
			
			if (x < n) {
			if (A.count(x + 1)) a1--, a2++;
			else a0--, a1++;
			}
			
			A.insert(x);
		}
		
		if (c == 'v' && !B.count(x)) {
			
			if (x > 0) {
			if (B.count(x - 1)) b1--, b2++;
			else b0--, b1++;
			}
			
			if (x < m) {
			if (B.count(x + 1)) b1--, b2++;
			else b0--, b1++;
			}
			
			B.insert(x);
		}
		
		if (c == '?')
			cout << a0 * b0 << " " << a1 * b0 + a0 * b1 << " " << a2 * b0 + a1 * b1 + a0 * b2 << " " << a2 * b1 + a1 * b2 << " " << a2 * b2 << "\n";
	}
	
	return 0;
}