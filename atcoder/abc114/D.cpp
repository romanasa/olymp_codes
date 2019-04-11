#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

int cnt[123];

void make(int x) {
	for (int i = 2; i * i <= x; i++) {
		while (x % i == 0) {
			x /= i;
			cnt[i]++;
		}
	}
	if (x > 1) cnt[x]++;
}

bool check(vector<int> A, vector<int> B) {
	int ok = 1;
	for (int i = 0; i < (int)A.size(); i++)
		ok &= cnt[A[i]] >= B[i];
	return ok;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int n; cin >> n;
	
	for (int i = 2; i <= n; i++) make(i);
	
	int ans = 0;
	
	for (int i = 0; i <= n; i++) ans += check({ i }, { 74 });
	
	for (int i = 0; i <= n; i++) for (int j = 0; j <= n; j++) if (i != j) 
		ans += check({ i, j }, { 14, 4 }) + check({ i, j }, { 24, 2 });
		
	for (int i = 0; i <= n; i++) for (int j = 0; j <= n; j++) for (int k = 0; k < j; k++)
		if (i != j && i != k && j != k) ans += check({ i, j, k }, { 2, 4, 4 });
		
	cout << ans << "\n";
	return 0;
}