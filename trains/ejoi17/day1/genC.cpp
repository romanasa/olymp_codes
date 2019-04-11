#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

int main() {
	int n = (int)2000;
	int l = (int)1e9;
	int k = 100;
	
	cout << n << " " << l << " " << k << "\n";
	
	for (int i = 0; i < n; i++) {
		cout << i + 1 << " " << i + 1 << "\n";
	}
	for (int i = 0; i < n; i++) {
		cout << i + 1 << " " << i + 1 << "\n";
	}
	
	return 0;
}