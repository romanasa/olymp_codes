#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

int main() {
	int n, k;
	scanf("%d %d", &n, &k);
	
	vector<pair<int, int> > E;
	
	for (int i = 0; i < n; i++) {
		int l, r;
		scanf("%d %d", &l, &r);
		E.push_back({ l, -1 });
		E.push_back({ r, 1 });		
	}
	
	sort(E.begin(), E.end());
	
	int bal = 0, last = -1;
	int ans = 0;
	for (auto c : E) {
		if (bal >= k) ans += (c.first - last);
		
		if (c.second == -1) bal++;
		if (c.second == 1) bal--;
		if (c.second == -1 && bal == k) ans++;
		last = c.first;
	}
	printf("%d\n", ans);
	return 0;
}