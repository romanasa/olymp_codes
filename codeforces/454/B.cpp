#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;


vector<int> p41 = { 2, 4, 1, 3 };
vector<int> p42 = { 3, 1, 4, 2 };

vector<int> p51 = { 2, 4, 1, 3, 5 };
vector<int> p52 = { 5, 2, 4, 1, 3 };

vector<int> p61 = { 6, 2, 4, 1, 3, 5 };
vector<int> p62 = { 5, 3, 1, 4, 2, 6 };

vector<int> p71 = { 6, 2, 4, 1, 3, 5, 7 };
vector<int> p72 = { 7, 4, 2, 6, 1, 3, 5 };

int n, m;
	
bool check(vector<vector<int> > &A, vector<vector<int> > &B) {

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
	
	if (n == 1 && m == 1) {
		cout << "YES\n";
		cout << "1\n";
		return 0;
	}
	
	if (n == 3 && m == 3) {
		cout << "YES\n";
		cout << "1 3 4\n";
		cout << "5 7 6\n";
		cout << "9 2 8\n";
		return 0;
	}
	
	if (max(n, m) <= 3) return 0 * puts("NO");

	vector<vector<int> > A(n, vector<int>(m));
	auto B = A;
	
	int cnt = 1;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			A[i][j] = cnt++;
		}
	}
	
	cout << "YES\n";
	if (m >= 4) {
		for (int i = 0; i < n; i++) {
			int j = 0;
			for (j = 0; j + 8 <= m; j += 4) {
				for (int t = 0; t < 4; t++) {
					B[i][j + t] = A[i][j + (i % 2 ? p42 : p41)[t]  - 1];
				}
			}
			if (j + 4 == m) for (int t = 0; t < 4; t++) B[i][j + t] = A[i][j + (i % 2 ? p42 : p41)[t] - 1];
			else if (j + 5 == m) for (int t = 0; t < 5; t++) B[i][j + t] = A[i][j + (i % 2 ? p52 : p51)[t] - 1];
			else if (j + 6 == m) for (int t = 0; t < 6; t++) B[i][j + t] = A[i][j + (i % 2 ? p62 : p61)[t] - 1];
			else if (j + 7 == m) for (int t = 0; t < 7; t++) B[i][j + t] = A[i][j + (i % 2 ? p72 : p71)[t] - 1];
			else assert(0);
		}
		
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				cout << B[i][j] << " ";
			}
			cout << "\n";
		}
	} else {
		for (int j = 0; j < m; j++) {
			int i = 0;
			for (i = 0; i + 8 <= n; i += 4) {
				for (int t = 0; t < 4; t++) {
					B[i + t][j] = A[i + (j % 2 ? p42 : p41)[t] - 1][j];
				}
			}
			if (i + 4 == n) for (int t = 0; t < 4; t++) B[i + t][j] = A[i + (j % 2 ? p42 : p41)[t] - 1][j];
			else if (i + 5 == n) for (int t = 0; t < 5; t++) B[i + t][j] = A[i + (j % 2 ? p52 : p51)[t] - 1][j];
			else if (i + 6 == n) for (int t = 0; t < 6; t++) B[i + t][j] = A[i + (j % 2 ? p62 : p61)[t] - 1][j];
			else if (i + 7 == n) for (int t = 0; t < 7; t++) B[i + t][j] = A[i + (j % 2 ? p72 : p71)[t] - 1][j];
			else assert(0);
		}
		
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				cout << B[i][j] << " ";
			}
			cout << "\n";
		}
	}

	assert(check(A, B));
	
	return 0;
}