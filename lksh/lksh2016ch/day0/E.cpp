#include <bits/stdc++.h>

using namespace std;

int main() {
	string s;
	cin >> s;
	
	string ans;
	for (char c : s) {
		if (c == '#') {
			if (ans.size())
				ans.pop_back();
		} else if (c == '@')
			ans.clear();
		else
			ans += c;
	}
	cout << ans;
	return 0;
}
