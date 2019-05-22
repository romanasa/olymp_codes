#include <bits/stdc++.h>
#define ll long long

using namespace std;

#define TASK "dynasties"

const int dd = (int)1e3 + 7;
const int inf = (int)1e9 + 7;

int P[dd];

int main() {
#ifndef HOME
	freopen(TASK".in", "r", stdin), freopen(TASK".out", "w", stdout);
#endif	

	int n;
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
		scanf("%d", &P[i]);
		
	int s;
	scanf("%d", &s);
	
	int ind = -1, tmsk = 0, ans = inf;
	for (int i = 0; i < s; i++) {
		int a, b, c, d;
		scanf("%d %d %d %d", &a, &b, &c, &d);
		
		for (int msk = 0; msk < (1 << n); msk++) {
			vector<int> T;
			for (int i = 0; i < n; i++)
				if ((msk >> i) & 1)
					T.push_back(2);
				else
					T.push_back(1);
					
			bool ok = true;
			
			int t = 0;
			for (int i = 0; i < (int)T.size(); i++) {
				if (i && T[i] == T[i - 1])
					t++;
					
				for (int j = i - 1; j >= 0; j--) {
					if (T[i] == T[j] && T[i] == 1) {
						if (P[i] - P[j] < a || P[i] - P[j] > b) {
							ok = false;
						}
						break;
					}
					if (T[i] == T[j] && T[i] == 2) {
						if (P[i] - P[j] < c || P[i] - P[j] > d) {
							ok = false;
						}
						break;
					}
				}
			}
			
			if (ok && t < ans) {
				ans = t, ind = i, tmsk = msk;
			}
		}
	}
	if (ind == -1)
		return 0 * puts("0");
	cout << ind + 1 << " " << ans << "\n";
	for (int i = 0; i < n; i++)
		if ((tmsk >> i) & 1)
			cout << '2';
		else
			cout << '1';
	return 0;
}