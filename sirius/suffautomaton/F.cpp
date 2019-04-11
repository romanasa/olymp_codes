#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

int main() {
	string s;
	
	int n;
	cin >> n;
	
	while (n--) {
		char tp;
		cin >> tp;
		if (tp == '+') {
			string t;
			cin >> t;
			s += t;
		} else {
			string t;
			cin >> t;
			int ok = 1;
			for (int i = 0; i < (int)t.size(); i++) {
				if (t[i] != s[(int)s.size() - t.size() + i]) {
					ok = 0;
				}
			}
			puts(ok ? "YES" : "NO");
		}
	}
	return 0;
}