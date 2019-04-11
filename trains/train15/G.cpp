#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

int main() {
	int a, b;
	cin >> a >> b;
	
	int t = __gcd(a, b);
	
	int cnt = max(a, b) / t;
	
	if (cnt % 2) puts("Petya");
	else puts("Vasya");
	
	return 0;
}