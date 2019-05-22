#define _CRT_SECURE_NO_WARNINGS
#pragma comment(linker, "/STACK:256000000")
#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <cstring>
#include <algorithm>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <queue>
#include <deque>
#include <bitset>
#include <unordered_map>
#include <unordered_set>

using namespace std;

typedef long long ll;

#define TASK ""

int solve();

int main()
{
#ifdef _DEBUG
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#else
	//freopen(TASK".in", "r", stdin), freopen(TASK".out", "w", stdout);
#endif
	solve();
	return 0;
}

const int MAXN = (int)1000 + 23;
int tin[MAXN], tout[MAXN], up[MAXN], timer = 1;
bool bridge[MAXN], used[MAXN];
int color[MAXN];

struct edge {
	int to, ind, r;
};

vector<vector<edge>> g;

void dfs(int v, int pr = -1) {
	used[v] = true;
	tin[v] = up[v] = timer++;
	for (auto p : g[v]) {
		int to = p.to, num = p.ind;
		if (num == pr) continue;
		if (used[to]) up[v] = min(up[v], tin[to]);
		else {
			dfs(to, num);
			up[v] = min(up[v], up[to]);
			if (up[to] > tin[v]) {
				bridge[num] = true;
			}
		}
	}
}

void paint(int v, int f) {
	used[v] = true;
	for (auto p : g[v]) {
		int to = p.to, c = p.r, num = p.ind;
		if (used[f]) return;
		if (!used[to]) {
			if (bridge[num]) color[num] = c;
			paint(to, f);
			if (used[f]) return;
			if (bridge[num]) color[num] = 0;
		}
	}
}

int solve() {
	int n, m;
	cin >> n >> m;

	g.resize(n);
	for (int i = 0; i < m; i++) {
		int a, b;
		cin >> a >> b;
		a--, b--;
		g[a].push_back({ b, i, 1 });
		g[b].push_back({ a, i, 2 });
	}

	dfs(0);

	int p; cin >> p;
	for (int i = 0; i < p; i++) {
		int a, b;
		cin >> a >> b;
		a--, b--;
		fill(used, used + n, false);
		paint(a, b);
	}

	for (int i = 0; i < m; i++) {
		if (color[i] == 1) cout << 'R';
		if (color[i] == 2) cout << 'L';
		if (color[i] == 0) cout << 'B';
	}

	return 0;
}