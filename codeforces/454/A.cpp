#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

int can[31];

int main() {
	int n;
	cin >> n;
	
	for (int i = 0; i < 26; i++) can[i] = 1;
	
	int found = 0;
	int ans = 0;
	
	string a, b;
	for (int i = 0; i < n; i++) {
		cin >> a >> b;
		
		if (a == "!") {
			if (found) ans++;
			set<char> cur;
			for (char c : b) cur.insert(c - 'a');	
			for (int c = 0; c < 26; c++) if (!cur.count(c))
				can[c] = 0;
		} else if (a == ".") {
			set<char> cur;
			for (char c : b) cur.insert(c - 'a');	
			for (int c = 0; c < 26; c++) if (cur.count(c))
				can[c] = 0;
		} else {
			if (i + 1 < n) { can[b[0] - 'a'] = 0; if (found) ans++; }
			else {
				for (int c = 0; c < 26; c++) if (c != b[0] - 'a')
					can[c] = 0;
			}
		}

		int cnt = 0;
		for (int c = 0; c < 26; c++) if (can[c]) {
			cnt++;
		}	
		assert(cnt);
		
		if (cnt == 1) found = 1;
	}
	cout << ans << "\n";
	return 0;
}