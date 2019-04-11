#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

int main() {
	string s;
	cin >> s;
	
	for (char c = 'a'; c <= 'z'; c++) {
		if ((int)s.find(c) == -1) return 0 * printf("%c\n", c);
	}
	puts("None");
	return 0;
}