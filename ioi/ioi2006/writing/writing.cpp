#include <bits/stdc++.h>
#define ll long long
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)
using namespace std;

int cntS[61];
int cnt[61];

int get(char c) {
	if ('A' <= c && c <= 'Z') return c - 'A';
	return c - 'a' + 26;
}

int main() {
	int n, m;
	cin >> n >> m;
	string s, t;
	cin >> s >> t;
	
	for (char c : s)
		cntS[get(c)]++;
	
		
	int ans = 0;
	for (int i = 0; i < m; i++) {
		cnt[get(t[i])]++;
		
		int s = 0;
		for (int j = 0; j < 52; j++) {
			s += abs(cnt[j] - cntS[j]);
		}
		ans += (s == 0);
		
		if (i - n + 1 >= 0) {
			cnt[get(t[i - n + 1])]--;
		}
	}
	cout << ans;
	return 0;
}