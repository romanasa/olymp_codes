#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

int main() {
	int l = 1, r = 1e6;
	while (l < r) {
		int m = (l + r) / 2;
		cout << "? " << m << endl;
		char c; cin >> c;
		
		if (c == '=') l = r = m;
		if (c == '<') r = m - 1;
		if (c == '>') l = m + 1;
	}
	cout << "! " << l << endl;
	return 0;
}