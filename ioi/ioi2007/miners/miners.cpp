#include <bits/stdc++.h>
#define ll long long

using namespace std;

const char* types = "MFB*";

int get(char c) {
	return strchr(types, c) - types;
}

int get(char a, char b, char c) {
	if (a == '*') {
		if (b == '*') return 1;
		return 1 + (b != c);
	}
	if (a != b && a != c && b != c) return 3;
	if (a != b || a != c || b != c) return 2;
	return 1;
}

int num(char a, char b) {
	return get(a) * 4 + get(b);
}

int dp1[21][21], dp2[21][21];

const int inf = (int)1e9 + 1;

void upd(int &a, int b) { if (a < b) a = b; }

int main() {
	
	int n;
	cin >> n;
	
	string s;
	cin >> s;
	
	
	for (int i = 0; i < 21; i++) {
		for (int j = 0; j < 21; j++) {
			dp1[i][j] = dp2[i][j] = -inf;
		}
	}
	
	dp1[num('*', '*')][num('*', '*')] = 0;
	
	for (int i = 0; i < n; i++) {
		for (int a = 0; a < 21; a++) {
			for (int b = 0; b < 21; b++) {
				if (dp1[a][b] == -inf) continue;
				
				char c1 = types[a / 4], c2 = types[a % 4];
				
				upd(dp2[num(c2, s[i])][b], dp1[a][b] + get(c1, c2, s[i]));
				
				char d1 = types[b / 4], d2 = types[b % 4];
				
				upd(dp2[a][num(d2, s[i])], dp1[a][b] + get(d1, d2, s[i]));
				
			}
		}
		
		for (int a = 0; a < 21; a++) {
			for (int b = 0; b < 21; b++) {
				dp1[a][b] = dp2[a][b];
				dp2[a][b] = -inf;
			}
		}
	}
	
	int ans = 0;
	for (int a = 0; a < 21; a++) {
		for (int b = 0; b < 21; b++) {
			upd(ans, dp1[a][b]);
		}
	}
	cout << ans;
	return 0;
}