#define _CRT_SECURE_NO_WARNINGS
#pragma comment(linker, "/STACK:66777216")
#include <iostream>
#include <cstdio>
#include <cmath>
#include <vector>
#include <ctime>
#include <map>
#include <set>
#include <string>
#include <queue>
#include <deque>
#include <cassert>
#include <cstdlib>
#include <bitset>
#include <algorithm>
#include <string>
#include <list>
#include <fstream>
#include <cstring>
#include <sstream>
#include <numeric>

using namespace std;

typedef long long ll;

#define TASK "o"
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stdout);
#define all(v) v.begin(), v.end()

int solve();

int main() {
#ifdef HOME
	freopen("input.txt", "r", stdin), freopen("output.txt", "w", stdout);
#else
	//if (TASK != "")
	//freopen(TASK".in", "r", stdin), freopen(TASK".out", "w", stdout);
#endif
	solve();
	return 0;
}

const int dd = (int)2000 + 7;
const int inf = (int)1e9 + 7;

struct pt {
	ll x, y;
};

ll dist(pt A, pt B) {
	return (B.x - A.x) * (B.x - A.x) + (B.y - A.y) * (B.y - A.y);
}

vector<pair<int, pair<int, int> > > T;
vector<vector<int> > E;
int used[dd];
int n, k;

bool get(int v, int k) {
	
	if (k < 0)
		return false;

	if (v == n)
		return true;

	if (used[v]) {
		return get(v + 1, k);
	}

	for (int i : E[v]) {
		if (!used[i]++) {
			k--;
		}
	}

	if (get(v + 1, k))
		return true;

	int deg = k;
	for (int i : E[v]) {
		if (--used[i] == 0)
			k++;
	}

	used[v] = 1;
	if (k - deg > 1 && get(v + 1, k - 1))
		return true;
	used[v] = 0;
	
	return false;
}

bool check(int t) {
	fill(used, used + n, 0);
	for (int i = 0; i < n; i++)
		E[i].clear();

	for (auto c : T) {
		if (c.first > t) {
			E[c.second.first].push_back(c.second.second);
			E[c.second.second].push_back(c.second.first);
		}
	}

	return get(0, k);
}

int solve() {
	scanf("%d %d", &n, &k);

	E.resize(n);

	vector<pt> P(n);
	for (int i = 0; i < n; i++) {
		scanf("%d %d", &P[i].x, &P[i].y);
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			T.push_back({ dist(P[i], P[j]), make_pair(i, j) });
		}
	}

	sort(T.rbegin(), T.rend());

	int l = 0, r = T.front().first;
	while (r - l > 1) {
		int m = (l + r) / 2;
		if (!check(m)) {
			l = m;
		} else {
			r = m;
		}
	}

	check(r);
	for (int i = 0; i < n; i++)
		if (used[i]) {
			printf("%d ", i + 1);
			k--;
		}

	for (int i = 0; i < n; i++) {
		if (!used[i] && k) {
			printf("%d ", i + 1);
			k--;
		}
	}
	return 0;
}