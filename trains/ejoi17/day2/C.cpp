#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

const int dd = (int)1e5 + 1;
pair<int, int> G[dd];

int main() {
	int n, k;
	cin >> n >> k;
	
	vector<int> A(n), C(n);
	for (int i = 0; i < n; i++) cin >> A[i];
	
	for (int i = 0; i < n; i++) G[i] = { A[i], i };
	sort(G, G + n);
	for (int i = 0; i < n; i++) C[G[i].second] = i;
	
	//for (int i = 0; i < n; i++) err("%d, ", A[G[C[i]].second]); err("\n");
	
	for (int it = 0; it < k; it++) {
		int p;
		cin >> p;
		
		ll ans = 0;

		vector<int> cnt(n);
		
		for (int i = 0; i < n; i++) {
			
		}
		
		printf("%lld\n", ans);
	}
	
	return 0;
}