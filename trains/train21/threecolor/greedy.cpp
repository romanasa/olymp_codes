#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

const int dd = (int)1007;

int color[dd], tmp[dd];
int G[dd][dd];

int n, m;
vector<vector<int> > E;
	
int get(int v) {
	int c1 = 0, c2 = 0, c3 = 0;
	for (int to : E[v]) {
		if (color[to] == 1) c1 = 1;
		if (color[to] == 2) c2 = 1;
		if (color[to] == 3) c3 = 1;
	}
	if (!c1) return 1;
	else if (!c2) return 2;
	else if (!c3) return 3;
	return -1;
}

int found = 0;
int CUR;

void go() {
	fill(tmp, tmp + n, 0);

	int cnt = 0;
	for (int i = 0; i < n; i++) if (color[i]) {
		for (int to : E[i]) if (!color[to]) tmp[to] = 1;
		cnt++;
	}
	
	if (cnt == n) {
		found = 1;
		return;
	}
	
	vector<pair<pair<int, int>, int> > P;
	for (int i = 0; i < n; i++) if (!color[i]) {
		int deg = 0, deg2 = 0;
		for (int to : E[i]) deg += tmp[to], deg2 += !color[to];
		P.push_back({ { deg, deg2 }, i });
	}
	
	sort(P.begin(), P.end());
	
	int it = 0;
	for (auto c : P) {
		int v = c.second;
		int col = get(v);
		if (col != -1) {
			color[v] = col;
			go();
			if (found) return;
			color[v] = 0;
		}
		if (++it > CUR) break;
	}
}

int main() {
	int test = 1;
	
	while (scanf("%d %d", &n, &m) == 2) {
		
		E.clear();
		E.resize(n);
	
		for (int i = 0; i < m; i++) {
			int a, b;
			scanf("%d %d", &a, &b);
			a--, b--;
			//G[a][b] = G[b][a] = 1;
			E[a].push_back(b);
			E[b].push_back(a);
		}
		
		fill(color, color + n, 0);
		
		int ind = 0;
		for (int v = 0; v < n; v++) if (E[v].size() > E[ind].size()) ind = v;
		
		found = 0;
		
		vector<int> P;
		for (int i = 0; i < n; i++) P.push_back(i);
		//sort(P.begin(), P.end(), [](int a, int b){ return E[a].size() > E[b].size(); });
		srand(135);
		for (CUR = 0; ; CUR++) {
			random_shuffle(P.begin(), P.end());
			for (int x : P) {
				color[x] = 1;
				go();
				if (found) break;
				color[x] = 0;
			}
			if (found) break;
		}
		
		if (found) {
			for (int i = 0; i < n; i++) printf("%d%c", color[i], " \n"[i == n - 1]);
		} else {
			assert(0);
		}
		err("done test = %d\n", test);
		test++;
	}
	return 0;
}