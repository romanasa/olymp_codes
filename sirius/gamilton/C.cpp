#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

int dx[] = { -2, -2, -1, -1, 1, 1, 2, 2 };
int dy[] = { -1, 1, -2, 2, -2, 2, -1, 1 };
vector<pair<int, int> > cur;

int used[501][501];

int main() {	
	int n;
	scanf("%d", &n);
	
	srand(135);
	int ci = rand() % n, cj = rand() % n;
	
	for (int it = 0; it < n * n; it++) {
		used[ci][cj] = 1;
		cur.push_back({ ci, cj });
		
		int gi = -1, gj = -1;
		int cnt = (int)1e9;
		int maxd = (int)1e9;
		
		for (int gg = 0; gg < 8; gg++) {
			int ni = ci + dx[gg], nj = cj + dy[gg];
			if (ni < 0 || ni >= n || nj < 0 || nj >= n) continue;
			if (used[ni][nj]) continue;
			
			int cur = 0;
			for (int ff = 0; ff < 8; ff++) {
				int qi = ni + dx[ff], qj = nj + dy[ff];
				if (qi < 0 || qi >= n || qj < 0 || qj >= n) continue;
				if (!used[qi][qj]) cur++;
			}
			
			int curd = min(nj, n - nj - 1) + min(ni, n - ni - 1);
			
			if (cur < cnt || (cur == cnt && curd < maxd)) {
				maxd = curd;
				cnt = cur, gi = ni, gj = nj;
			}
		}
		//assert(it + 1 == n * n || (gi != -1 && gj != -1));
		
		if (gi == -1 && gj == -1 && it + 1 < n * n) {
			//err("new\n");
			it = -1;
			ci = rand() % n, cj = rand() % n;
			for (int i = 0; i < n; i++) fill(used[i], used[i] + n, 0);
			cur.clear();
			continue;
		}
		ci = gi, cj = gj;
	}
	
	for (auto c : cur) {
		printf("%d %d\n", c.first, c.second);
	}
	return 0;
}