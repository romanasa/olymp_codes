#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;
#define TASK "brackets"

string s;

void gen(int n, int bal) {
	//cout << s << " " << n << " " << bal << endl;
	if (n == 0) {
	if (bal == 0) cout << s << "\n";
	return;
}
	s += '('; gen(n - 1, bal + 1);
	if (bal){ s.back() = ')'; gen(n - 1, bal - 1); }
	s.pop_back();
	}
int main() {
#ifndef HOME
	freopen(TASK".in", "r", stdin), freopen(TASK".out", "w", stdout);
#endif
int n;
cin >> n;
gen(2 * n, 0);
	return 0;
}