#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

const int dd = (int)1e5 + 1;

int go1[dd][31];
int go2[dd][31];
int term1[dd], term2[dd];
int A[dd];

unordered_map<int, int> used[dd];
int ok = 1;

void dfs(int v1, int v2) {
	if (used[v1][v2]) return;
	
	used[v1][v2] = 1;
	
	if (A[v1] != -1 && A[v1] != v2) {
		ok = 0;
		return;
	}
	A[v1] = v2;
	
	if (term1[v1] ^ term2[v2]) {
		ok = 0;
		return;
	}
	
	for (int i = 0; i < 26; i++) {
		dfs(go1[v1][i], go2[v2][i]);
		if (!ok) return;
	}
}

#define TASK "isomorphism"

int main() {
#ifndef HOME
	freopen(TASK".in", "r", stdin), freopen(TASK".out", "w", stdout);
#endif

	int n1, m1, k1;
	scanf("%d %d %d", &n1, &m1, &k1);
	
	for (int i = 0; i < k1; i++) {
		int v;
		scanf("%d", &v);
		term1[v - 1] = 1;
	}
	
	for (int i = 0; i < m1; i++) {
		int a, b;
		char c;
		scanf("%d %d %c", &a, &b, &c);
		go1[a - 1][c - 'a'] = b - 1;
	}
	
	for (int i = 0; i < n1; i++) {
		for (int j = 0; j < 26; j++) {
			if (go1[i][j] == -1) go1[i][j] = n1;
		}
	}
	for (int j = 0; j < 26; j++) go1[n1][j] = n1;
	n1++;
	
	fill(A, A + n1, -1);
	
	int n2, m2, k2;
	scanf("%d %d %d", &n2, &m2, &k2);
	
	for (int i = 0; i < k2; i++) {
		int v;
		scanf("%d", &v);
		term2[v - 1] = 1;
	}
	
	for (int i = 0; i < m2; i++) {
		int a, b;
		char c;
		scanf("%d %d %c", &a, &b, &c);
		go2[a - 1][c - 'a'] = b - 1;
	}
	for (int i = 0; i < n2; i++) {
		for (int j = 0; j < 26; j++) if (go2[i][j] == -1)
			go2[i][j] = n2;
	}
	for (int j = 0; j < 26; j++) go2[n2][j] = n2;
	n2++;
	
	dfs(0, 0);
	
	if (n1 != n2 || m1 != m2 || k1 != k2 || !ok) return 0 * puts("NO");
	puts("YES");
	return 0;
}