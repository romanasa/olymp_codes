#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

const int dd = 257;

bitset<dd> G1[dd], G2[dd], cur;

int main() {
	int n, k;
	cin >> n >> k;
	
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++) {
			int t;
			cin >> t;
			
			if (t == 1) G1[i][j] = 1;
			if (t == 2) G2[i][j] = 1;
		}
		
	for (int i = 0; i < n; i++) G1[i][i] = 1;
	for (int i = 0; i < n; i++) G2[i][i] = 1;
	
	vector<int> P(n);
	for (int i = 0; i < n; i++) P[i] = i;
	
	while (1) {
		random_shuffle(P.begin(), P.end());
		cur.reset();
		for (int it = 0; it < min(k, n); it++) {
			cur |= G1[P[it]];
		}
		
		if (cur.count() == n) {
			cout << "1\n" << k << "\n";
			for (int it = 0; it < min(k, n); it++) cout << P[it] + 1 << " ";
			cout << "\n";
			return 0;
		}
		
		cur.reset();
		for (int it = 0; it < min(n, k); it++) cur |= G2[P[it]];
		if (cur.count() == n) {
			cout << "2\n" << k << "\n";
			for (int it = 0; it < min(k, n); it++) cout << P[it] + 1 << " ";
			cout << "\n";
			return 0;
		}
	} 
 	return 0;
}