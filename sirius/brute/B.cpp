#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

const int dd = (int)5e3 + 7;
int G[dd];

int grundy(int n) {
	if (G[n] != -1) return G[n];

	vector<int> cur;
	for (int i = 1; i <= n; i++) {
		int l = i - 1;
		int r = n - i;
		if (l == 1) l = 0;
		if (r == 1) r = 0;
		cur.push_back(grundy(l) ^ grundy(r));
	}
	
	sort(cur.begin(), cur.end());
	if (cur.empty() || cur[0] > 0) return G[n] = 0;
	
	for (int i = 1; i < (int)cur.size(); i++) {
		if (cur[i - 1] + 1 < cur[i])
			return G[n] = cur[i - 1] + 1;
	}
	return G[n] = cur.back() + 1;
}

int main() {
	fill(G, G + dd, -1);
	
	int n;
	scanf("%d", &n);
	
	if (!grundy(n)) return 0 * puts("Mueller");
	
	puts("Schtirlitz");
	
	for (int i = 1; i <= n; i++) {
		int l = i - 1;
		int r = n - i;
		if (l == 1) l = 0;
		if (r == 1) r = 0;
		if ((grundy(l) ^ grundy(r)) == 0) printf("%d\n", i);
	}
	
	return 0;
}