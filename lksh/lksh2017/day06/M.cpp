#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

int cnt1[11];
int cnt2[11];

int main() {
#ifndef HOME
	freopen("input.txt", "r", stdin), freopen("output.txt", "w", stdout);
#endif
	string s;
	cin >> s;
	
	int n = (int)s.size();
	
	int j = 0;
	int ans = -1;
	int ii = -1, jj = -1;
	
	vector<int> A(n);
	for (int i = 0; i < n; i++) A[i] = s[i] - '0';
	
	for (int i = 0; i < n; i++) {

		while (j < n && (j & 1 ? cnt2 : cnt1)[A[j]] == 0) 
			(j & 1 ? cnt1 : cnt2)[A[j]]++, j++;
			
		int cur = j - i;
			
		if (cur > ans) {
			ans = cur;
			ii = i, jj = j - 1;
		}
		
		(i & 1 ? cnt1 : cnt2)[A[i]]--;
	}
	cout << ii + 1 << " " << ans << "\n";
	return 0;
}