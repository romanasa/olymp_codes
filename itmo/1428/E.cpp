#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

void solve(int n) {
	vector<int> A(2 * n), B(2 * n);
	for (int i = 0; i < 2 * n; i++) A[i] = B[i] = i;
	
	vector<vector<int>> E(2 * n);
	vector<vector<int>> G(2 * n, vector<int>(2 * n));
	
	for (int i = 0; i <= n; i++) {
		if (i > 0) E[i].push_back(i - 1);
		if (i < n) E[i].push_back(i + 1);
		if (i > 0 && i < n) E[i].push_back(i + n), E[i + n].push_back(i);
	}
	
	for (int v = 0; v < 2 * n; v++) for (int to : E[v])
		G[v][to] = 1;
		
		
	auto check = [&](vector<int> &A, vector<int> &B) {
		int ok = 1;
		for (int v = 0; v < 2 * n; v++) for (int to : E[v]) 
			if (G[A[v]][A[to]]++) ok = 0;
		
		for (int v = 0; v < 2 * n; v++) for (int to : E[v])
			if (G[B[v]][B[to]]++) ok = 0;
			
		for (int v = 0; v < 2 * n; v++) for (int to : E[v])
			G[A[v]][A[to]]--, G[B[v]][B[to]]--;
		return ok;
	};
		
	mt19937 rnd(1);
		
	
	if (n > 6) {
		while (!check(A, B)) {
			shuffle(A.begin(), A.end(), rnd);
			shuffle(B.begin(), B.end(), rnd);
		}
	}
	
	do {	
		int ok = 1;
		for (int v = 0; v < 2 * n; v++) for (int to : E[v])
			if (G[A[v]][A[to]]++) ok = 0;
			
		if (ok) {
			do {
				int good = 1;
				for (int v = 0; v < 2 * n; v++) for (int to : E[v])
					if (G[B[v]][B[to]]++) good = 0;
					
				if (good) {
					for (int v = 0; v < 2 * n; v++) cout << v + 1 << " \n"[v == 2 * n - 1];
					for (int v = 0; v < 2 * n; v++) cout << A[v] + 1 << " \n"[v == 2 * n - 1];
					for (int v = 0; v < 2 * n; v++) cout << B[v] + 1 << " \n"[v == 2 * n - 1];
					return;
				}
				
				for (int v = 0; v < 2 * n; v++) for (int to : E[v])
					G[B[v]][B[to]]--;
			} while (next_permutation(B.begin(), B.end()));
		}
			
		for (int v = 0; v < 2 * n; v++) for (int to : E[v])
			G[A[v]][A[to]]--;
	
	} while (next_permutation(A.begin(), A.end()));
}

#define TASK "embedding"

int main() {
#ifndef HOME
	freopen(TASK".in", "r", stdin), freopen(TASK".out", "w", stdout);
#endif
	
	int n; 
	while (cin >> n) {
		if (n == 0) break;
		solve(n);
	}
	
	return 0;
}