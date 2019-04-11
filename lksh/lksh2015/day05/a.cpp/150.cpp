#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <algorithm>
#include <set>
#include <map>
#include <numeric>
#include <bitset>
#include <ctime>
#include <sstream>
#include <queue>
#include <cassert>

using namespace std;

int solve();

int main() {
#ifdef ZAOCHKA
	freopen("input.txt", "r", stdin), freopen("output.txt", "w", stdout);
#endif
	solve();
	return 0;
}

const int dd = (int)3e5 + 1;

int A[dd], ans[dd];
pair<int, int> T[dd], G[dd];

int n, m;
const int inf = (int)1e9 + 1;

bool in(pair<int, int> a, int c) {
	return a.first <= c && c <= a.second;
}

int used[dd];
int cnt[dd];

struct SegmentTree {
	vector<int> T[4 * dd];

	void upd(int v, int tl, int tr, int l, int r, int val) {
		if (l == tl && r == tr) {
			T[v].push_back(val);
		} else {
			int tm = (tl + tr) / 2;
			if (r <= tm) upd(v * 2, tl, tm, l, r, val);
			else if (l > tm) upd(v * 2 + 1, tm + 1, tr, l, r, val);
			else upd(v * 2, tl, tm, l, tm, val), upd(v * 2 + 1, tm + 1, tr, tm + 1, r, val);
		}
	}

	int get(int v, int tl, int tr, int pos, int p1, int p2) {
		
		int i = 0;
		while (i < (int)T[v].size() && (T[v][i] == p1 || T[v][i] == p2)) i++;
		if (i < (int)T[v].size()) return T[v][i];

		int t = -1;
		if (tl != tr) {
			int tm = (tl + tr) / 2;
			if (pos <= tm) t = get(v * 2, tl, tm, pos, p1, p2);
			else t = get(v * 2 + 1, tm + 1, tr, pos, p1, p2);
		}
		return t;
	}

	int gets(int v, int tl, int tr, int pos) {
		if (tl == tr) {
			return (int)T[v].size();
		} else {
			int tm = (tl + tr) / 2;
			if (pos <= tm) return gets(v * 2, tl, tm, pos) + (int)T[v].size();
			else return gets(v * 2 + 1, tm + 1, tr, pos) + (int)T[v].size();
		}
	}
} H;

int solve() {
	scanf("%d %d", &n, &m);

	vector<int> G;
	for (int i = 0; i < n; i++) {
		scanf("%d", &A[i]);
		G.push_back(A[i]);
	}

	for (int i = 0; i < m; i++) {
		scanf("%d %d", &T[i].first, &T[i].second);
		G.push_back(T[i].first), G.push_back(T[i].second);
	}

	sort(G.begin(), G.end());
	G.resize(unique(G.begin(), G.end()) - G.begin());

	int N = (int)G.size() - 1;

	for (int i = 0; i < m; i++) {
		T[i].first =  lower_bound(G.begin(), G.end(), T[i].first) - G.begin();
		T[i].second = lower_bound(G.begin(), G.end(), T[i].second) - G.begin();
		H.upd(1, 0, N, T[i].first, T[i].second, i);
	}

	for (int i = 0; i < n; i++) {
		A[i] = lower_bound(G.begin(), G.end(), A[i]) - G.begin();
	}

	set<pair<int, int> > S;

	for (int i = 0; i < n; i++) {
		cnt[i] = H.gets(1, 0, N, A[i]);
		S.insert( { cnt[i], i } );
		if (cnt[i] == 0) return 0 * puts("No");
	}

	fill(ans, ans + n, -1);

	while (S.size()) {

		int i = S.begin()->second;
		S.erase(S.begin());

		int p1 = (i ? ans[i - 1] : -1);
		int p2 = (i + 1 < n ? ans[i + 1] : -1);

		ans[i] = H.get(1, 0, N, A[i], p1, p2);

		if (ans[i] == -1) {
			return 0 * puts("No");
		}

		if (i && ans[i - 1] == -1 && in(T[ans[i]], A[i - 1])) {
			S.erase({ cnt[i - 1], i - 1 });
			cnt[i - 1]--;
			S.insert({ cnt[i - 1], i - 1 });
		}

		if (i + 1 < n && ans[i + 1] == -1 && in(T[ans[i]], A[i + 1])) {
			S.erase({ cnt[i + 1], i + 1 });
			cnt[i + 1]--;
			S.insert({ cnt[i + 1], i + 1 });
		}
	}

	puts("Yes");
	for (int i = 0; i < n; i++) {
		printf("%d ", ans[i] + 1);
	}
	return 0;
}

