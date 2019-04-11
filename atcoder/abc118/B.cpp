#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int n, m;
	cin >> n >> m;
	
	set<int> cur;
	for (int i = 1; i <= m; i++) cur.insert(i);
	
	for (int i = 0; i < n; i++) {
		int x; cin >> x;
		
		set<int> S;
		for (int j = 0; j < x; j++) {
			int t; cin >> t;
			if (cur.count(t)) S.insert(t);
		}
		cur = S;
	}
	cout << (int)cur.size() << "\n";
	return 0;
}