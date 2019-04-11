#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

#define TASK "a"

int main() {
#ifndef HOME
	freopen(TASK".in", "r", stdin), freopen(TASK".out", "w", stdout);
#endif
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	
	int n, m;
	cin >> n >> m;
	
	vector<int> a(n);
	vector<deque<int> > T(m);
	
	for (int i = 0; i < n; i++) cin >> a[i];
	
	
	set<pair<int, int> > s;
	for (int i = 0; i < m; i++) s.insert({ -1, i });
	
	for (int qq = 0; qq < n; qq++) {
		int x = a[qq];
		auto it = s.lower_bound({ x, m });
		
		assert(it != s.begin());
		
		--it;
		T[it->second].push_back(x);
		cout << it->second + 1 << " ";
		
		s.insert({ x, it->second });
		s.erase(it);
	}
	cout << "\n";
	
	
	s.clear();
	for (int i = 0; i < m; i++) if (T[i].size()) s.insert({ T[i].front(), i });
	
	for (int it = 0; it < n; it++) {
		int ind = s.begin()->second;
		s.erase(s.begin());
		cout << ind + 1 << " ";
		T[ind].pop_front();
		if (T[ind].size()) s.insert({ T[ind].front(), ind }); 
	}
	return 0;
}