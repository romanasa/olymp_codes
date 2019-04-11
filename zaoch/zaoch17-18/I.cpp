#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;
using namespace __gnu_pbds;

typedef long long ll;
typedef tree<pair<ll, int>, null_type, less<pair<ll, int> >, rb_tree_tag, tree_order_statistics_node_update> megaset;

megaset good, bad;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int n, m, q, k;
	cin >> n >> m >> q >> k;
	
	vector<int> s(m);
	for (int i = 0; i < m; i++) cin >> s[i];
	
	vector<vector<int> > score(n);
	vector<ll> goodS(n), badS(n);
	
	for (int i = 0; i < n; i++) {
		score[i].resize(m);
		for (int j = 0; j < m; j++) {
			cin >> score[i][j];
			if (score[i][j] < k - s[j]) goodS[i] += score[i][j], badS[i] += score[i][j];
			else goodS[i] += k, badS[i] += score[i][j];
		}
		good.insert({ goodS[i], i });
		bad.insert({ badS[i], i });
	}
	
	for (int i = 0; i < q; i++) {
		int tp;
		cin >> tp;
		
		if (tp == 1) {
			int i;
			cin >> i;
			i--;
			
			int mn = bad.size() - bad.order_of_key(make_pair(goodS[i] + 1, -1)) + 1;// количество (>goodS) в bad
			int mx = good.size() - good.order_of_key(make_pair(badS[i] + 1, -1)) + 1;
			
			if (goodS[i] > badS[i]) mx--;
			
			cout << mn << " " << mx << "\n";
		} else {
			int i, j, c;
			cin >> i >> j >> c;
			i--, j--;
			
			good.erase({ goodS[i], i }), bad.erase({ badS[i], i });
			
			if (score[i][j] < k - s[j]) goodS[i] -= score[i][j], badS[i] -= score[i][j];
			else goodS[i] -= k, badS[i] -= score[i][j];
			
			score[i][j] = c;
			goodS[i] += score[i][j], badS[i] += score[i][j];
			
			good.insert({ goodS[i], i }), bad.insert({ badS[i], i });
		}
	}
	return 0;
}