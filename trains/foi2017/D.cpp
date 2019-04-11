#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

int main() {
	ll x;
	cin >> x;
	
	if (x % 3 == 0) return 0 * puts("0");
	
	vector<int> op;
	while (x > 1) {
		if (x == 4) op.push_back(2), x -= 3;
		else if (x % 2 == 0) op.push_back(1), x /= 2;
		else op.push_back(2), x -= 3;
	}
	
	cout << (int)op.size() + 1 << "\n";
	reverse(op.begin(), op.end());
	for (int x : op) puts(x == 1 ? "MUL" : "ADD");
	puts("END");
	return 0;
}