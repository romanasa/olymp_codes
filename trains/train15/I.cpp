#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

int main() {
	int n;
	cin >> n;
	vector<int> a(n);
	for (int i = 0; i < n; i++) cin >> a[i];
	for (int i = 0; i + 3 < n; i++) if (a[i] == a[i + 1] && a[i] == a[i + 2]) return 0 * puts("YES");
	puts("NO");
	return 0;
}