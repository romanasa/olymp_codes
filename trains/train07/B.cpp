#include <bits/stdc++.h>
#define ll long long

using namespace std;

map<int, int> M;

vector<int> A, B, C, D, E;

#define TASK "seats"

int main() {
#ifndef HOME
	freopen(TASK".in", "r", stdin), freopen(TASK".out", "w", stdout);
#endif
	int n, k;
	scanf("%d %d", &n, &k);
	
	int l = 1;
	int r = n;
	
	for (int i = 0; i < k; i++) {
		int x, y;
		scanf("%d %d", &x, &y);
		
		while (M[l] == 3) l++;
		while (M[r] == 3) r--;
		
		E.push_back(i);
		if (x == l) {
			if (M[l]) A.push_back(i), B.push_back(i);
			if (M[l] == 0) (y == 1 ? A : B).push_back(i);
		}
		if (x == r) {
			if (M[r]) C.push_back(i), D.push_back(i);
			if (M[r] == 0) (y == 1 ? C : D).push_back(i);
		}
		if (y == 1) M[x] |= 2;
		if (y == 2) M[x] |= 1;
	}
	printf("%d ", (int)A.size()); for (int x : A) printf("%d ", x + 1); printf("\n");
	printf("%d ", (int)B.size()); for (int x : B) printf("%d ", x + 1); printf("\n");
	printf("%d ", (int)C.size()); for (int x : C) printf("%d ", x + 1); printf("\n");
	printf("%d ", (int)D.size()); for (int x : D) printf("%d ", x + 1); printf("\n");
	printf("%d ", (int)E.size()); for (int x : E) printf("%d ", x + 1); printf("\n");
	return 0;
}