#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

int main() {
	string s;
	cin >> s;
	
	int ans = 0;
	for (char c : s) {
		if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u') ans++;
		if (c == '1' || c == '3' || c == '5' || c == '7' || c == '9') ans++;
	}
	cout << ans;
	return 0;
}