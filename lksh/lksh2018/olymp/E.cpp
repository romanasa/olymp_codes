#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

const int MAXMEM = (int)2e8;
char MEM[MAXMEM];
int mpos;

inline void* operator new(size_t n) {
	char *res = MEM + mpos;
	mpos += n;
	return (void*) res;
}

inline void operator delete(void*) {}

const int dd = (int)1e5 + 7;
vector<pair<int, int> > T[dd];
ll cost[dd];

set<pair<ll, int> > S;

void add(int ind, int x) {
	S.erase({ -cost[ind], ind });
	if (T[ind].size() && T[ind].back().first == x) {
		cost[ind] -= 1ll * T[ind].back().second * T[ind].back().second;
		T[ind].back().second++;
	} else T[ind].push_back({ x, 1 });
	cost[ind] += 1ll * T[ind].back().second * T[ind].back().second;
	S.insert({ -cost[ind], ind });
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int n, q;
	cin >> n >> q;
	
	for (int i = 0; i < n; i++) S.insert({ -cost[i], i });
	
	while (q--) {
		int tp; cin >> tp;
		
		if (tp == 1) {
			int x, k;
			cin >> x >> k;
			x--;
			for (int i = 0; i < k; i++) {
				int t; cin >> t;
				add(x, t);
			}
		} else {
		
			int ind = S.begin()->second;
			S.erase(S.begin());
			cout << ind + 1 << "\n";
			cost[ind] = 0;
			T[ind].clear();
			S.insert({ -cost[ind], ind });
		}
	}
	
	return 0;
}