#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

int A[123][123];
int B[123][123];

int n, m;

bool check() {

	set<pair<int, int> > S;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			
			if (i > 0) S.insert({ A[i][j], A[i - 1][j] });
			if (i + 1 < n) S.insert({ A[i][j], A[i + 1][j] });
			if (j > 0) S.insert({ A[i][j], A[i][j - 1] });
			if (j + 1 < m) S.insert({ A[i][j], A[i][j + 1] });
		}
	}
	
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (i > 0 && S.count({ B[i][j], B[i - 1][j] })) return 0;
			if (i + 1 < n && S.count({ B[i][j], B[i + 1][j] })) return 0;
			if (j > 0 && S.count({ B[i][j], B[i][j - 1] })) return 0;
			if (j + 1 < m && S.count({ B[i][j], B[i][j + 1] })) return 0;
		}
	}
	return 1;
}

int main() {
	
	cin >> n >> m;
	
	vector<int> P;
	for (int i = 0; i < n * m; i++) P.push_back(i + 1);
	
	
	int cnt = 1;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			A[i][j] = cnt++;
	
	do {
		int ind = 0;
		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++)
				B[i][j] = P[ind++];
				
		if (check()) {
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < m; j++) {
					cout << B[i][j] << " ";
				}
				cout << "\n";
			}
			return 0;	
		}
	
	} while (next_permutation(P.begin(), P.end()));
	return 0;
}