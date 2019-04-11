#include <bits/stdc++.h>

using namespace std;

int main() {
	string s, t;
	cin >> t >> s;
	
	int j = 0;
	
	for (int i = 0; i < (int)s.size(); i++) {
		if (j < (int)t.size() && s[i] == t[j]) {
			j++;
		}
	}
	if (j == (int)t.size()) 
		puts("YES");
	else
		puts("NO");
	return 0;
}
