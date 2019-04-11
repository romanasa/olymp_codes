#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

const int dd = (int)1e5 + 1;
char s[dd];

#define TASK "triangles"

int main() {
#ifndef HOME
	freopen(TASK".in", "r", stdin), freopen(TASK".out", "w", stdout);
#endif
	int n, m;
	scanf("%d %d", &n, &m);
	scanf("%s", s);
	
	while (m--) {
		int pos;
		scanf("%d", &pos);
		pos--;
		s[pos] = 'B' + 'W' - s[pos];
		
		int ans = 0;
		for (int i = 0; i < n; i++) {
			for (int j = 1; j < (n + 1) / 2; j++) {
				int a = i - j;
				if (a < 0) a += n;
				int b = i;
				int c = i + j;
				if (c >= n) c -= n;
				if (s[a] == s[b] && s[b] == s[c]) ans++;
			}
		}
		if (n % 3 == 0) {
			for (int i = 0; i < n / 3; i++) {
				int a = i, b = i + n / 3, c = i + 2 * n / 3;
				if (b >= n) b -= n; if (c >= n) c -= n;
				if (s[a] == s[b] && s[b] == s[c]) ans -= 2;
			}	
		}
		printf("%d\n", ans);
	}
	return 0;
}