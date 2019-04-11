#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

int main() {
	int n;
	cin >> n;
	
	int t = -1;
	string name;
	int ss = 0;
	
	for (int i = 0; i < n; i++) {
		string s;
		cin >> s;
		
		int x, k;
		cin >> x >> k;
		
		int c = 0;
		while (k >= x) {
			k -= x;
			k += 2;
			c++;
		}
		
		if (c > t) {
			t = c;
			name = s;
		}
		ss += c;
	}
	cout << ss << "\n" << name << "\n";
	return 0;
}