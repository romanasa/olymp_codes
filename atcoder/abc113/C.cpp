#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int n; cin >> n >> n;
	
	vector<pair<int, int>> A(n);
	vector<int> P(n);
	
	for (int i = 0; i < n; i++) cin >> A[i].first >> A[i].second;
	for (int i = 0; i < n; i++) P[i] = i;
	
	sort(P.begin(), P.end(), [&](int a, int b) { return A[a] < A[b]; });
	
	for (int i = 0; i < n; ) {
		int j = i;
		while (j < n && A[P[j]].first == A[P[i]].first) j++;
		for (int t = i; t < j; t++) {
			A[P[t]].second = t - i + 1;
		}
		i = j;
	}
	
	for (int i = 0; i < n; i++) printf("%06d%06d\n", A[i].first, A[i].second);
	return 0;
}