#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

int main() {
	int n, m;
	cin >> n >> m;
	
	vector<int> A(m);
	for (int i = 0; i < m; i++) cin >> A[i];
	
	sort(A.begin(), A.end());
	
	int sum = 0;
	int cnt = 0;
	for (int x : A) {
		if (sum + x <= n) sum += x, cnt++;
	}
	cout << cnt << "\n";
	return 0;
}