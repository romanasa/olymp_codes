#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

bool check(ll x) {
	ll old = x;
	while (x) {
		if (x % 10 == 0) return false;
		if (old % (x % 10)) return false;
		x /= 10;
	}
	return true;
}

char c[13];

int main() {
#ifndef HOME
	freopen("input.txt", "r", stdin), freopen("output.txt", "w", stdout);
#endif
	ll x = 1, t;

	int ind = 0;
	
	t = x;
	while (t) c[ind++] = t % 10, t /= 10;
	reverse(c, c + 13);
	
	//for (int i = 0; i < 13; i++) cout << c[i] << ", ";
	
	ll p = 0;
	
	while (x < (ll)1e10) {
		
		int ok = 1;
		int was = 0;
		for (int i = 0; i < 13; i++) {
			was |= c[i];
			if (!c[i] && was || (c[i] && x % c[i])) {
				ok = 0;
				break;
			}
		}
		
		if (ok) { 
			if (x - p > (ll)1e6) {
				printf("%I64d ", x);
			}
			p = x;
		}
			
		x++;
		
		c[12]++;
		for (int i = 12; c[i] > 9; i--)
			c[i - 1]++, c[i] -= 10;

		was = 0;	
		for (int i = 0; i < 13; i++) {
			was |= c[i];
			if (was && !c[i]) {
				fill(c + i, c + 13, 1);
				
				x = 0;
				for (int i = 0; i < 13; i++) x = x * 10 + c[i];
				break;
			}
		}
	}
	
	return 0;
}