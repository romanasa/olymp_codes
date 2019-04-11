#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

int main() {
	int n;
	cin >> n;
	
	vector<int> go(n), deg(n);
	set<pair<int, int> > E;
	for (int i = 0; i < n; i++) {
		cin >> go[i]; go[i]--;
		E.insert({ min(i, go[i]), max(i, go[i]) });
	}

	ll c1 = 0;	
	for (int i = 0; i < n; i++) 
		if (go[go[go[i]]] == i) c1++;
	c1 /= 3;
	
	ll c2 = 0;
	for (auto c : E) {
		c2 += n - 2 - deg[c.first] - deg[c.second];
		deg[c.first]++, deg[c.second]++;
	}	
	
	cout << 1ll * n * (n - 1) * (n - 2) / 6 - c2 - c1 << "\n";
	return 0;
}