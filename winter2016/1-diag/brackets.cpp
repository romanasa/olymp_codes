#include <bits/stdc++.h>
#define ll long long
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

const int dd = (int)1e5 + 1;

string s, ans;
int F[31][dd];


void go(int l, int r) {
	if (l > r) return;
	
	int pos = F[s[l] - 'a'][r];
	
	if (pos < l || pos > r) exit(0 * puts("-1"));
	
	ans += '(';
	go(l + 1, pos - 1);
	ans += ')';
	go(pos + 1, r);
}

int main() {
	cin >> s;

	int n = (int)s.size();

	for (int i = 0; i < n; i++) {
		for (int c = 0; c < 31; c++) {
			if (c == s[i] - 'a') {
				F[c][i] = i;
			} else {
			
				if (i > 0) {
					int cur = F[s[i] - 'a'][i - 1];
					F[c][i] = (cur > 0 ? F[c][cur - 1] : -1);
				} else {
					F[c][i] = -1;
				}
			
			}
		}
	}	
	
	go(0, n - 1);
	cout << ans;
	return 0;
}