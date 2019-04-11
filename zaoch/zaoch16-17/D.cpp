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
	//freopen("input.txt", "r", stdin), freopen("output.txt", "w", stdout);
#else
	//freopen(TASK".in", "r", stdin), freopen(TASK".out", "w", stdout);
#endif
	solve();
}

const int dd = (int)1e6 + 7;

vector<int> G[dd];
int cnt[dd];

struct edge { int a, b, c;  };

struct dsu {
	int P[dd], R[dd];
	dsu() { for (int i = 0; i < dd; i++) P[i] = i, R[i] = 1; }
	int get(int v) { return v == P[v] ? v : P[v] = get(P[v]); }
	bool un(int a, int b) {
		a = get(a), b = get(b);
		if (a != b) {
			if (R[b] > R[a]) swap(a, b);
			P[b] = a, R[a] += R[b];
		}
		return a != b;
	}
} J;

int solve() {
	int n;
	scanf("%d", &n);

	for (int i = 0; i < n; i++) {
		int x;
		scanf("%d", &x);
		cnt[x]++;
	}

	ll ans = 0;
	for (int i = 1; i < dd; i++) {
		if (cnt[i] > 1) {
			ans += 1ll * (cnt[i] - 1) * i;
			cnt[i] = 1;
		}
	}

	vector<edge> E;

	for (int i = 1; i < dd; i++) {
		int pr = -1;

		for (int j = i; j < dd; j += i) {
			if (cnt[j]) {
				if (pr != -1)
					E.push_back({ pr, j, i });
				pr = j;
			}
		}
	}

	sort(E.begin(), E.end(), [](edge a, edge b) { return a.c > b.c; });

	for (auto c : E) {
		if (J.un(c.a, c.b)) {
			ans += c.c;
			printf("%d--->%d\n", c.a, c.b);
		}
	}

	printf("%lld\n", ans);

	return 0;
}