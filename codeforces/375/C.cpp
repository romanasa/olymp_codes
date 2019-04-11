#include <bits/stdc++.h>
#define ll long long
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)
using namespace std;

const int dd = 5007;

int A[dd], B[dd];

int main() {
	int n, k;
	scanf("%d %d", &n, &k);
	
	for (int i = 0; i < n; i++) {	
		int t;
		scanf("%d", &t);
		A[i] = t;
	}
	
	int cur = n / k;
	
	multiset<int> S;
	
	for (int i = 1; i <= k; i++)
		for (int j = 0; j < cur; j++)
			S.insert(i);
	
	int ans = 0;
	for (int i = 0; i < n; i++) {
		auto it = S.find(A[i]);
		if (it != S.end()) {
			B[i] = 1;
			S.erase(it);
		}
	}

	for (int i = 0; i < n; i++) {
		if (!B[i] && S.size()) {
			A[i] = *S.begin();
			S.erase(S.begin());
			ans++;
		}
	}
	cout << cur << " " << ans << "\n";
	for (int i = 0; i < n; i++)
		cout << A[i] << " ";
	
	return 0;
}