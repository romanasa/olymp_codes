#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

int A[234][234];
const int dd = (int)1e4 + 7;
int sz[dd], s[dd];
int num[dd];

int dx[] = { -1, 0, 1, 0 };
int dy[] = { 0, 1, 0, -1 };

int h, w, n, k;

bool ok(int i, int j) { return i >= 0 && j >= 0 && i < h && j < w; }
	
bool G[dd][dd];
vector<int> V[dd];


void add(int A, int B) {
	if (A != B) G[A][B] = G[B][A] = 1;
}

int par(int v) { return num[v] == v ? v : num[v] = par(num[v]); }

int check(int a, int b) {
	for (int x : V[a])
		for (int y : V[b]) if (G[x][y]) return 1;
	return 0;
}

map<int, int> M;
int nv = 1;

int get(int x) {
	int &res = M[x];
	if (res) return res;
	return res = nv++;	
}

int main() {
	cin >> h >> w >> n >> k;
	
	for (int i = 0; i < h; i++) for (int j = 0; j < w; j++) cin >> A[i][j];
	for (int i = 1; i <= n; i++) cin >> s[i];
	double x, y;
	cin >> x >> y;
	
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			for (int gg = 0; gg < 4; gg++) {
				int ni = i + dx[gg], nj = j + dy[gg];
				if (ok(ni, nj)) {
					add(A[i][j], A[ni][nj]);
				}
			}
		}
	}
	
	set<pair<int, int> > S;
	
	for (int i = 1; i <= n; i++) {
		sz[i] = s[i];
		V[i].push_back(i);
		S.insert({ sz[i], i });
		num[i] = i;
	}
	
	while (S.size() > k) {
		
		int f = 0;
		int ii = -1, jj = -1;
		
		for (auto i : S) {
			for (auto j : S) {
				if (j == i) break;
				if (check(i.second, j.second)) {
					ii = i.second;
					jj = j.second;
					f = 1;
					break;
				}	
			}
			if (f) break;
		}
		
		//err("ii = %d, jj = %d\n", ii, jj);
		if (ii == -1) break;
		
		S.erase({ sz[ii], ii });
		S.erase({ sz[jj], jj });
		
		if (V[jj].size() > V[ii].size()) swap(ii, jj);
		
		num[jj] = ii;
		sz[ii] += sz[jj];
		for (int x : V[jj]) V[ii].push_back(x);
		V[jj].clear();
		
		S.insert({ sz[ii], ii });
	}
	
	for (int i = 1; i <= n; i++)
		cout << get(par(i)) << "\n";
		
	return 0;
}