#define _CRT_SECURE_NO_WARNINGS
#pragma comment(linker, "/STACK:256000000")
#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <bitset>
#include <sstream>
#include <fstream>
#include <ctime>
#include <cstring>
#include <numeric>
#include <queue>
#include <cassert>
#include <unordered_map>

using namespace std;

typedef long long ll;
typedef long double ld;

#define TASK "sorting"

int solve();

int main() {
#ifdef HOME
	freopen("input.txt", "r", stdin), freopen("output.txt", "w", stdout);
#else
	//freopen(TASK".in", "r", stdin), freopen(TASK".out", "w", stdout);
#endif
	solve();
}

const int dd = (int)1e6 + 7;
const int inf = (int)1e9 + 1;
int A[dd], dist[dd], color[dd];

struct st { int d, v, c; };

vector<vector<int> > E;

int solve() {
	int n, m;
	scanf("%d %d", &n, &m);

	fill(dist, dist + n, inf);
	fill(color, color + n, -1);

	for (int i = 0; i < n; i++) {
		scanf("%d", &A[i]);
	}

	E.resize(n);

	for (int i = 0; i < m; i++) {
		int a, b;
		scanf("%d %d", &a, &b);
		E[a - 1].push_back(b - 1);
		E[b - 1].push_back(a - 1);
	}

	queue<st> q;
	for (int i = 0; i < n; i++) {
		if (A[i]) {
			q.push({ 0, i, A[i] });
			dist[i] = 0;
			color[i] = A[i];
		}
	}

	int ans = n - 1;

	while (q.size()) {
		int d = q.front().d, v = q.front().v, c = q.front().c;
		q.pop();

		for (int to : E[v]) {

			if (A[to] && A[to] != c) {
				ans = min(ans, d + 1);
			}

			if (A[to] == 0 && dist[to] <= d + 1 && color[to] != c) {
				ans = min(ans, d + dist[to] + 1);
			}

			if (A[to] == 0 && dist[to] > d + 1) {
				dist[to] = d + 1;
				color[to] = c;
				q.push({ dist[to], to, c });
			}
		}
	}
	printf("%d\n", ans);
	return 0;
}