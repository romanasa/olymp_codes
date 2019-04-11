#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

#define TASK "jump-or-increment"

int main() {
#ifndef HOME
	freopen(TASK".in", "r", stdin), freopen(TASK".out", "w", stdout);
#endif
	int n;
	cin >> n;
	if (n == 0) return 0 * puts("j");
	
	int maxlen = (int)1e9;
	int pos = -1;
	
	for (int x = 1; x <= 1000 * 1000; x++) {
		int len = x + (n - x) / x;
		if ((n - x) % x) len++;
		
		if (len < maxlen) {
			maxlen = len;
			pos = x;
		}
	}
	
	string s = string(pos, 'i') + string((n - pos) / pos, 'j');
	if ((n - pos) % pos) s.insert(s.begin() + (n - pos) % pos, 'j');
	
	cout << s;
	return 0;
}