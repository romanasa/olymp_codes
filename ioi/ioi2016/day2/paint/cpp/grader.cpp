#include <bits/stdc++.h>
#define ll long long
#include "paint.h"
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)
using namespace std;

char A[1001][1001];

int main() {

	int n, m;
	scanf("%d %d\n", &n, &m);
	
	vector<vector<int> > R(n), C(m);
	
	for (int i = 0; i < n; i++) {
		string s;
		getline(cin, s);
		istringstream in(s);
		int t;
		while (in >> t) {
			R[i].push_back(t);	
		}
	}
	
	for (int i = 0; i < m; i++) {
		string s;
		getline(cin, s);
		istringstream in(s);
		
		int t;
		while (in >> t) {
			C[i].push_back(t);
		}
	}
	
	for (int i = 0; i < n; i++)
		fill(A[i], A[i] + m, '.');
	int ok = 1;
	while (ok) {
		ok = 0;
		for (int i = 0; i < n; i++) {
			string s;
			for (int j = 0; j < m; j++)
				s += A[i][j];
			string gs = solve_puzzle(s, R[i]);
			
			if (s != gs) {
			
				ok = 1;
				for (int j = 0; j < m; j++)
					A[i][j] = gs[j];
			}
		}
		
		
		for (int j = 0; j < m; j++) {
			string s;
			for (int i = 0; i < n; i++)
				s += A[i][j];
			string gs = solve_puzzle(s, C[j]);
			
			if (s != gs) {
				ok = 1;
				for (int i = 0; i < n; i++)
					A[i][j] = gs[i];
			}
		}
	}
	
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			printf("%c%c", A[i][j], A[i][j]);
		}
		printf("\n");
	}
	
	return 0;
}
