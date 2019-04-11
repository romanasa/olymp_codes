#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

int main() {
	vector<int> A;
	multiset<int> B, C;
	
	int n;
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		int a, b;
		scanf("%d %d", &a, &b);
		for (int j = 0; j < b; j++) A.push_back(a);
	}
	sort(A.begin(), A.end());
	
	int m;
	scanf("%d", &m);
	for (int i = 0; i < m; i++) {
		int a, b;
		scanf("%d %d", &a, &b);
		for (int j = 0; j < b; j++) B.insert(a);
	}
	
	while (A.size()) {
		int x = A.back();
		A.pop_back();
		for (int it = 0; it < x; it++) {
			if (B.empty()) return 0 * puts("0");
			int y = *B.rbegin();
			B.erase(--B.end());
			if (y > 1) C.insert(y - 1);
		}
		for (auto y : C) B.insert(y);
		C.clear();
	}
	puts("1");
	return 0;
}