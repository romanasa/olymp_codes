#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

int main() {
	int n, k;
	cin >> n >> k;
	ll last = -k;
	for (int i = 0; i < n; i++) {
		ll t;
		cin >> t;
		t = max(t, last + k);
		
		cout << t << " ";
		last = t;
	}
	
	return 0;
}