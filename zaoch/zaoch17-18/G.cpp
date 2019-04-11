#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

vector<set<pair<int, int> > > E;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n, m;
	cin >> n >> m;
	
	E.resize(n);
	
	for (int i = 0; i < m; i++) {
		int a, b, c;
		cin >> a >> b >> c;
		E[a - 1].insert({ b - 1, c });
		E[b - 1].insert({ a - 1, c });
	}
	
	int q;
	cin >> q;
	while (q--) {
		int tp, a, b;
		cin >> tp >> a >> b;
		a--, b--;
		
		if (tp == 1) {
			int c;
			cin >> c;
			E[a].insert({ b, c });
			E[b].insert({ a, c });
		} else if (tp == 2) {
			E[a].erase(E[a].lower_bound(make_pair(b, 0)));
			E[b].erase(E[b].lower_bound(make_pair(a, 0)));
		} else {
			int cost = (int)2e9 + 7;			
			
			auto it = E[a].lower_bound(make_pair(b, 0));
			if (it != E[a].end() && it->first == b) cost = it->second;
			
			auto j = E[b].begin();
			for (auto i = E[a].begin(); i != E[a].end(); ++i) {
				while (j != E[b].end() && j->first < i->first) ++j;				
				while (j != E[b].end() && j->first == i->first) {
					cost = min(cost, j->second + i->second);
					++j;
				}
			}
			if (cost == (int)2e9 + 7) cout << "-1\n";
			else cout << cost << "\n";
		}
	}
	return 0;
}