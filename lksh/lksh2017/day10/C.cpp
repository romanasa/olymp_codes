#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

const int dd = (int)1e3 + 7;

int n, m, k;
char A[dd][dd];

struct ev { int i1, j1, i2, j2, ind; };
int ans[dd * dd];

void dfs(int l, int r, vector<ev> &E) {
	vector<ev> A, B;
	
	int m = (l + r) / 2;
	
	
	

}

int main() {
	scanf("%d %d %d\n", &n, &m, &k);
	
	for (int i = 0; i < n; i++) scanf("%s", A[i]);
	
	vector<ev> E;
	
	for (int i = 0; i < k; i++) {
		int i1, j1, i2, j2;
		scanf("%d %d %d %d", &i1, &j1, &i2, &j2);
		i1--, j1--, i2--, j2--;
		E.push_back({ i1, j1, i2, j2 });
	}
	
	dfs(0, n - 1);
	
	return 0;
}