#include <bits/stdc++.h>

using namespace std;

const int dd = (int)5e4 + 7;

char s[dd], t[dd];

int main() {
	freopen("search.in", "r", stdin);
	freopen("search.out", "w", stdout);

	scanf("%s", s);
	scanf("%s", t);

	int n = strlen(s), m = strlen(t);
	
	for (int i = 0; i + m - 1 < n; i++) {
		bool ok = true;
		for (int j = 0; j < m; j++) {
			if (s[i + j] != t[j]) {
				ok = false;
				break;
			}
		}
		if (ok)
			printf("%d ", i);
	}
 		
	return 0;
}
