#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

const int dd = (int)1500 + 7;
const int maxC = (int)1e6 + 1;
vector<int> G[maxC];

int A[dd][dd];
vector<pair<int, int> > T[maxC], H[maxC];

short U[dd][dd];
short nxt[dd][dd], prv[dd][dd];

pair<int, int> st[dd];
int sz;
int ans;

int main() {

	for (int t = 2; t < maxC; t++) {
		if (G[t].size()) continue;
		for (int j = t; j < maxC; j += t)
			G[j].push_back(t);
	}
	
	int n, m;
	scanf("%d %d", &n, &m);
	
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			scanf("%d", &A[i][j]);
			for (int x : G[A[i][j]]) {
				T[x].push_back({ i, j });
			}
		}
	}
	
	for (int j = 0; j < m; j++) {
		for (int i = 0; i < n; i++) {
			for (int x : G[A[i][j]])
				H[x].push_back({ i, j });
		}
	}
	
	for (int x = 0; x < maxC; x++) {
		if (T[x].empty()) continue;
		
		for (int i = 0; i < (int)H[x].size(); i++) {
			if (i && H[x][i - 1].second == H[x][i].second && H[x][i - 1].first + 1 == H[x][i].first)
				U[H[x][i].first][H[x][i].second] = U[H[x][i - 1].first][H[x][i - 1].second] + 1;
			else
				U[H[x][i].first][H[x][i].second] = 0;
		}
		
		sz = 0;
		for (int q = 0; q < (int)T[x].size(); q++) {
			int i = T[x][q].first, j = T[x][q].second;
			if (q == 0 || T[x][q - 1].first != i || T[x][q - 1].second + 1 != j) {
				while (sz) {
					int ind = st[sz - 1].second;
					nxt[T[x][ind].first][T[x][ind].second] = q - ind, sz--;
				}
				sz = 0;
			}
			while (sz && st[sz - 1].first > U[i][j]) {
				int ind = st[sz - 1].second;
				nxt[T[x][ind].first][T[x][ind].second] = q - ind, sz--;
			}
			st[sz++] = { U[i][j], q };
		}
		
		while (sz) {
			int ind = st[sz - 1].second;
			nxt[T[x][ind].first][T[x][ind].second] = (int)T[x].size() - ind, sz--;
		}
		
		int S = (int)T[x].size();
		for (int q = S - 1; q >= 0; q--) {
			int i = T[x][q].first, j = T[x][q].second;
			if (q == S - 1 || T[x][q + 1].first != i || T[x][q + 1].second != j + 1) {
				while (sz) {
					int ind = st[sz - 1].second;
					prv[T[x][ind].first][T[x][ind].second] = ind - q, sz--;
				}
				sz = 0;
			}
			while (sz && st[sz - 1].first > U[i][j]) {
				int ind = st[sz - 1].second;
				prv[T[x][ind].first][T[x][ind].second] = ind - q, sz--;
			}
			st[sz++] = { U[i][j], q };
		}
		
		while (sz) {
			int ind = st[sz - 1].second;
			prv[T[x][ind].first][T[x][ind].second] = ind + 1, sz--;
		}
		
		for (auto c : T[x]) {
			int cur = (U[c.first][c.second] + 1) * (nxt[c.first][c.second] + prv[c.first][c.second] - 1);
			if (cur > ans) ans = cur;
		}
		/*
		err("x = %d\n", x);
		for (auto c : T[x]) {
			err("(%d, %d), up = %d, nxt = %d, prv = %d\n", c.first, c.second, U[c.first][c.second], 
					nxt[c.first][c.second], prv[c.first][c.second]); 
		}
		*/
	}
	printf("%d\n", ans);
	return 0;
}