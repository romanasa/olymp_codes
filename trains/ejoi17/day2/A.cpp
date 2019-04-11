#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

int dx[] = { -3, -2, 0, 2, 3, 2, 0, -2 };
int dy[] = { 0, -2, -3, -2, 0, 2, 3, 2 };
vector<pair<int, int> > cur;

int used[1001][1001];
int n;
int ans[1001][1001];

bool ok(int i, int j) { return i >= 0 && i < n && j >= 0 && j < n; }

int gi = -1, gj = -1;
int cnt = (int)1e9;
int maxd = (int)1e9;


pair<int, int> get(int ni, int nj) {
  	int cur = 0;
  	for (int ff = 0; ff < 8; ff++) {
  		int qi = ni + dx[ff], qj = nj + dy[ff];
  		if (ok(qi, qj) && !used[qi][qj]) cur++;
  	}
  	int curd = min(nj, n - nj - 1) + min(ni, n - ni - 1); 	
  	return { cur, 1};//curd };
}

void out() {
	printf("s = \"");
	for (int i = 0; i < n; i++) {
		for (int j = 0; j + 1 < n; j++) printf("%d ", used[i][j]);
		printf("%d\\n", used[i][n - 1]);
	}
	printf("\n");
	exit(0);
}
	
const int dd = (int)1e3 + 1;
int U[dd][dd];
	
bool check(int x, int y) {
	queue<pair<int, int> > q;
	for (int i = 0; i < n; i++) fill(U[i], U[i] + n, 0);
	
	q.push({ x, y });
	U[x][y] = 1;
	
	while (q.size()) {
		int i = q.front().first, j = q.front().second;
		q.pop();
		for (int gg = 0; gg < 8; gg++) {
			int ni = i + dx[gg], nj = j + dy[gg];
			if (ni == 0 && nj == 0) return true;
			if (ok(ni, nj) && !U[ni][nj] && !used[ni][nj]) {
				U[ni][nj] = 1;
				q.push({ ni, nj });
			}
		}
	}
	return false;
}

int K;

void go(int i, int j, int cnt) {
	if (!check(i, j)) return;

	if (cnt == n * n) {
		int ok = 0;
		for (int gg = 0; gg < 8; gg++) {
			int ni = i + dx[gg], nj = j + dy[gg];
			if (ni == 0 && nj == 0) ok = 1;
		}
		if (ok) out();
	} else {
		vector<pair<pair<int, int>, int> > cur;
		for (int gg = 0; gg < 8; gg++) {
			int ni = i + dx[gg], nj = j + dy[gg];
			if (ok(ni, nj) && !used[ni][nj]) cur.push_back({ get(ni, nj), ni * n + nj });
		}
		sort(cur.begin(), cur.end());
		
		int cc = 0;
		for (auto c : cur) {
			int ni = c.second / n, nj = c.second % n;
			used[ni][nj] = cnt + 1;
			go(ni, nj, cnt + 1);
			used[ni][nj] = 0;
			if (++cc == K) return;
		}
	}
}

int main() {
	scanf("%d", &n);
	
	
	for (K = 1; ; K++) {    
    	used[0][0] = 1;
    	go(0, 0, 1);
    	used[0][0] = 0;
    	err("k = %d\n", K);
	}
	
	
	
	return 0;
}