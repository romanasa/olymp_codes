#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;
using namespace __gnu_pbds;

typedef long long ll;
typedef tree<int, null_type, greater<int>, rb_tree_tag, tree_order_statistics_node_update> megaset;

megaset T;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int q;
	cin >> q;
	
	while (q--) {
		int c, x;
		cin >> c >> x;
		
		if (c == 1) {
			T.insert(x);
		} else if (c == -1) {
			T.erase(x);
		} else {
			cout << *T.find_by_order(x - 1) << "\n";
		}
	}
	return 0;
}