#include <bits/stdc++.h>
#define ll long long

using namespace std;

bool is(char c) {
	return ('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z');
}

int main() {
	int n;
	string s;
	cin >> n >> s;
	
	int br = 0;

	int a = 0, b = 0;
	
	int len = 0;
	
	char p = '!';
	for (char c : s) {

		if (is(c))
			len++;
		else
			len = 0;

		if (!br)
			a = max(a, len);	
	
		if (c == '(') {
			br = 1;
		}
		if (c == ')') {
			b += is(p);
			br = 0;
		}
		
		if (c == '_' && br == 1) {
			b += is(p);
		}
		p = c;
	}
	cout << a << " " << b;
	return 0;
}