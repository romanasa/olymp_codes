#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

void ne() { cout << "NE\n"; exit(0); }

int used[31], G[31][31];
char ans[31];
int pos = 25;

void dfs(int v) {
	used[v] = 1;
	
	for (int j = 0; j < 31; j++) if (G[v][j]) {
		if (used[j] == 1) ne();
		if (used[j] == 0) dfs(j);
	}
	
	used[v] = 2;
	ans[v] = (char)('a' + pos--);
}

int main() {
	int n;
	cin >> n;
	
	vector<string> A(n), P;
	for (int i = 0; i < n; i++) cin >> A[i];
	
	for (int it = 0; it < n; it++) {
		int pos;
		cin >> pos;
		P.push_back(A[pos - 1]);
	}
	
	for (int i = 0; i + 1 < n; i++) {
		for (int j = 0; j < (int)P[i].size(); j++) {
			if ((int)P[i + 1].size() == j) ne();
			if (P[i][j] != P[i + 1][j]) {
				G[P[i][j] - 'a'][P[i + 1][j] - 'a'] = 1;
				break;
			} 
		}
	}
	for (int i = 0; i < 26; i++) if (!used[i]) dfs(i);
	
	
	cout << "DA\n";
	for (int i = 0; i < 26; i++) cout << ans[i]; cout << "\n";
	
	return 0;
}