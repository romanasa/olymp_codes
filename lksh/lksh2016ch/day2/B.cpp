#include <bits/stdc++.h>

#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

const int dd = (int)1e5 + 7;

vector<int> E[dd];
int used[dd];

int main() {
#ifndef HOME
	freopen("jenny.in", "r", stdin);
	freopen("jenny.out", "w", stdout);
#endif
	int n;
	scanf("%d", &n);
	
	vector<int> T(n), J(n);
	
	for (int i = 0; i < n; i++) {
		scanf("%d %d", &T[i], &J[i]);
		used[T[i]] = 1;
		E[T[i]].push_back(T[i] - J[i]);
	}
	
	int k = 0;
	
	multiset<int> S;
	
	for (int i = dd - 1; i >= 1; i--) {
	
		for (auto c : E[i])
			S.insert(c);
		
		if (!used[i] && S.size() && *S.rbegin() <= i) {
			S.erase(--S.end());
			k++;
		}
		
		if (k == n) {
			printf("%d\n", i);
			return 0;
		}
	}
	printf("Impossible\n");
	return 0;
}
