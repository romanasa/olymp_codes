#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

const int dd = (int)1e5 + 7;
int cnt[dd], tmm[dd];
set<int> T[dd];

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int n, m;
	cin >> n >> m;
	
	int ls = 0;
	
	for (int i = 0; i < m; i++) {
		int a, b;
		cin >> a >> b;
		a--;
		
		if (a == 0) {
			
			T[cnt[a]].erase(a);
			for (int x : T[cnt[a]]) {
				if (tmm[x] < tmm[a]) ls--;
			}
			cnt[a]++, tmm[a] += b;
			for (int x : T[cnt[a]]) {
				if (tmm[x] >= tmm[a]) ls--;
			}
			T[cnt[a]].insert(a);
		} else {
			T[cnt[a]].erase(a);
			
			if (cnt[a] == cnt[0] && tmm[a] >= tmm[0]) ls++;
			if (cnt[a] + 1 == cnt[0] && tmm[a] + b < tmm[0]) ls++;
			
			cnt[a]++, tmm[a] += b;
			T[cnt[a]].insert(a);
		}
		cout << ls + 1 << "\n";
	}

	return 0;
}