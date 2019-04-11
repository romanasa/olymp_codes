#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

const int maxN = 1234;

char A[maxN][maxN];
int p[maxN][maxN], used[maxN][maxN];
int n, m, k;

int dx[] = { -1, 0, 1, 0 };
int dy[] = { 0, 1, 0, -1 };

bool ok(int i, int j) { return i >= 0 && i < n && j >= 0 && j < m; }

bool check(int i, int j) {
	int cnt = 0;
	for (int gg = 0; gg < 4; gg++) {
		int ni = i + dx[gg], nj = j + dy[gg];
		if (ok(ni, nj) && used[ni][nj]) cnt++;
		if (cnt > 1) return false;
	} 
	return true;
}

void go(int i, int j) {
	for (int i = 0; i < n; i++) fill(used[i], used[i] + m, 0);
	
	vector<pair<int, int> > cur;
	
	used[i][j] = 1;
	cur.push_back({ i, j });
	
		srand(time(0));
		
	int it = 0;
	while (1) {
		int mx = -1;
		int ii = -1, jj = -1;
		
		random_shuffle(cur.begin(), cur.end());
		int cc = 0;
		for (auto c : cur)  {
			//if (++cc == 7 * n) break;
			for (int gg = 0; gg < 4; gg++) {
				int ni = c.first + dx[gg], nj = c.second + dy[gg];
				
				if (!ok(ni, nj) || A[ni][nj] == '#' || used[ni][nj] || !check(ni, nj)) continue;
				
				used[ni][nj] = 1;
				
				int cur = 0;
				for (int ff = 0; ff < 4; ff++) {
					int ni2 = ni + dx[ff], nj2 = nj + dy[ff];
					if (ok(ni2, nj2) && A[ni2][nj2] != '#' && check(ni2, nj2)) cur++;
				}
				
				used[ni][nj] = 0;
				if (cur > mx) {
					mx = cur, ii = ni, jj = nj;
				}
			}
		}
		
		if (mx == 0) break;
		if (mx == -1) break;
		
		used[ii][jj] = 1;
		
		for (int gg = 0; gg < 4; gg++) {
			int ni = ii + dx[gg], nj = jj + dy[gg];
			if (ok(ni, nj) && A[ni][nj] != '#' && check(ni, nj)) used[ni][nj] = 1, cur.push_back({ ni, nj });
		}
		cur.push_back({ ii, jj });
		
		vector<pair<int, int> > ncur;
		for (auto c : cur) if (check(c.first, c.second)) ncur.push_back(c);
		cur = ncur;
	}
}

int calc() {
	int cnt = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cnt += (used[i][j] && check(i, j));
		}
	}
	return cnt;
}

int main(int argc, char* argv[]) {
	scanf("%d %d %d", &n, &m, &k);
	for (int i = 0; i < n; i++) scanf("%s", A[i]);
	
	int ans = -1, ii = -1, jj = -1;
	
	vector<pair<int, int> > P;
	for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) if (A[i][j] == '.')
		P.emplace_back(i, j);
	
	srand(time(0));
	random_shuffle(P.begin(), P.end());
		
	for (int it = 0; it < P.size(); it++) {
		int i = P[it].first, j = P[it].second;
		go(i, j);
		int cur = calc();
		if (cur > ans) {
			ans = cur, ii = i, jj = j;
			err("%.2f, (%d, %d)\n", 10.0 * ans / k, ii, jj);
		}
		//if (++it % 100 == 0) err("it = %d\n", it);
		//err("it = %d\n", it);
		if (ans >= k) break;
	}
	
	go(ii, jj);
	
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) putchar(A[i][j] == '.' && !used[i][j] ? 'X' : A[i][j]);
		putchar('\n');
	}
	err("score = %.2f\n", 10.0 * ans / k);
	err("ii = %d, jj = %d\n", ii, jj);
	
	return 0;
}
