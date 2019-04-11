#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

map<vector<vector<int> >, int> M;

int n, m;
	
void move1(int i, int x, vector<vector<int>> &A) {
	rotate(A[i].rbegin(), A[i].rbegin() + x, A[i].rend());
}	

void move2(int j, int x, vector<vector<int>> &A) {
	vector<int> tmp;
	for (int i = 0; i < n; i++) tmp.push_back(A[i][j]);
	rotate(tmp.rbegin(), tmp.rbegin() + x, tmp.rend());
	for (int i = 0; i < n; i++) A[i][j] = tmp[i];
}


struct ev { int tp, ind, x; };
vector<ev> cur;

void out(vector<vector<int>> &A) {
	for (int i = 0; i < n; i++)	
		for (int j = 0; j < m; j++) 	
			printf("%d%c", A[i][j], " \n"[j == m - 1]);
	printf("_______________\n");
}

int ANS;

void go(vector<vector<int>> &A, int last, int pos, int dep) {

	int ok = 1;
	for (int i = 0; i < n && ok; i++) {
		for (int j = 0; j < m && ok; j++) {
			ok &= (A[i][j] == (i * m + j));
		}
	}
	
	//out(A);
	
	if (ok) {
		printf("%d\n", (int)cur.size());
		for (auto c : cur) printf("%d %d %d\n", c.tp, c.ind, c.x);
		exit(0);
	}
	
	if (dep >= ANS) return;
	
  	for (int i = 0; i < n; i++) {
  		if (last == 1 && pos == i) continue;
  		for (int x = 1; x < m; x++) {
  			cur.push_back({ 1, i + 1, x });
  			move1(i, x, A);
  			go(A, 1, i, dep + 1);
  			move1(i, m - x, A);
  			cur.pop_back();
  		}
  	}
	
   for (int j = 0; j < m; j++) {
   		if (last == 2 && pos == j) continue;
   		for (int x = 1; x < n; x++) {
   			cur.push_back({ 2, j + 1, x });
   			move2(j, x, A);
   			go(A, 2, j, dep + 1);
   			move2(j, n - x, A);
   			cur.pop_back();
   		}
   	}
}

int main() {
	scanf("%d %d", &n, &m);
	vector<vector<int>> A(n, vector<int>(m));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			scanf("%d", &A[i][j]);
		}
	}
	
	ANS = 1;
	go(A, -1, -1, 0);
	
	set<int> S1, S2;
	vector<int> cnt(n), cnt2(m);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (A[i][j] != i * m + j) {
				cnt[i]++, cnt2[j]++;
				//err("i = %d, j = %d\n", i, j);
			}
		}
	}
	
	for (int i = 0; i < n; i++) if (cnt[i] == m) {
		//err("i = %d\n", i);
		S1.insert(i);
	}
	
	for (int j = 0; j < m; j++) if (cnt2[j] == n) {
		//err("j = %d\n", j);
		S2.insert(j);
	}
	
	if (S1.size() == 2 && S2.empty()) {
		for (int d1 = 0; d1 < m; d1++) {
			move1(*S1.begin(), d1, A);
			for (int d2 = 0; d2 < m; d2++) {
				move1(*S1.rbegin(), d2, A);
				
				int ok = 1;
				for (int j = 0; j < m; j++) {
					ok &= (A[*S1.begin()][j] == (*S1.begin()) * m + j);
					ok &= (A[*S1.rbegin()][j] == (*S1.rbegin()) * m + j);
				}
				
				if (ok) {
					printf("2\n");
					printf("%d %d %d\n", 1, *S1.begin() + 1, d1);
					printf("%d %d %d\n", 1, *S1.rbegin() + 1, d2);
					return 0;
				}
				
				move1(*S1.rbegin(), m - d2, A);
			}
			move1(*S1.begin(), m - d1, A);
		}
	}
	
	if (S2.size() == 2 && S1.empty()) {
		for (int d1 = 0; d1 < n; d1++) {
			move2(*S2.begin(), d1, A);
			for (int d2 = 0; d2 < n; d2++) {
				move2(*S2.rbegin(), d2, A);
				
				int ok = 1;
				for (int i = 0; i < n; i++) {
					ok &= (A[i][*S2.begin()] == (*S2.begin()) + m * i);
					ok &= (A[i][*S2.rbegin()] == (*S2.rbegin()) + m * i);
				}
				
				if (ok) {
					printf("2\n");
					printf("%d %d %d\n", 2, *S2.begin() + 1, d1);
					printf("%d %d %d\n", 2, *S2.rbegin() + 1, d2);
					return 0;
				}
				
				move2(*S2.rbegin(), n - d2, A);
			}
			move2(*S2.begin(), n - d1, A);
		}
	}
	
	if (S1.size() == 1 && S2.size() == 1) {
		for (int dx = 0; dx < m; dx++) {
			move1(*S1.begin(), dx, A);
			for (int dy = 0; dy < n; dy++) {
				move2(*S2.begin(), dy, A);
				
				int ok = 1;
				for (int i = 0; i < n; i++) {
					ok &= (A[i][*S2.begin()] == (*S2.begin()) + m * i);
				}
				for (int j = 0; j < m; j++) {
					ok &= (A[*S1.begin()][j] == (*S1.begin()) * m + j);
				}
				
				if (ok) {
					printf("2\n");
					printf("%d %d %d\n", 1, *S1.begin() + 1, dx);
					printf("%d %d %d\n", 2, *S2.begin() + 1, dy);
					return 0;
				}
				
				move2(*S2.begin(), n - dy, A);
			}
			move1(*S1.begin(), m - dx, A);
		}
	}
	
	if (S1.size() == 1 && S2.size() == 1) {
		
		for (int dy = 0; dy < n; dy++) {
			move2(*S2.begin(), dy, A);
    		for (int dx = 0; dx < m; dx++) {
    			move1(*S1.begin(), dx, A);
				
				int ok = 1;
				for (int i = 0; i < n; i++) {
					ok &= (A[i][*S2.begin()] == (*S2.begin()) + m * i);
				}
				for (int j = 0; j < m; j++) {
					ok &= (A[*S1.begin()][j] == (*S1.begin()) * m + j);
				}
				
				if (ok) {
					printf("2\n");
					printf("%d %d %d\n", 2, *S2.begin() + 1, dy);
					printf("%d %d %d\n", 1, *S1.begin() + 1, dx);
					return 0;
				}
				move1(*S1.begin(), m - dx, A);	
			}
			move2(*S2.begin(), n - dy, A);
		}
	}
	
	
	for (ANS = 1; ;ANS++) {
		go(A, -1, -1, 0);	
	}
	return 0;
}