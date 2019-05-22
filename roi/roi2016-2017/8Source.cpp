#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <bitset>
#include <algorithm>
#include <map>
#include <set>
#include <queue>
#include <cassert>
#include <random>
#include <cstring>
#include <numeric>
#include <ctime>

using namespace std;

typedef long long ll;
typedef long double ld;

int solve();

#define TASK "internship"

int main() {
#ifdef HOME
	freopen("input.txt", "r", stdin), freopen("output.txt", "w", stdout);
#else
	freopen(TASK".in", "r", stdin), freopen(TASK".out", "w", stdout);
#endif
	solve();
}

#define y1 dfasdfsaf

const int dd = (int)1e6 + 7;

ll A[dd], B[dd], X[dd], Y[dd];
ll pX[dd], pY[dd];
int iA[dd], iB[dd], iP;
pair<int, int> P[dd];

ll ans = 0;
int x1, y1, x2, y2;


struct SegmentTree2 {
	int P[8 * dd];
	int T[8 * dd];
	
	void clear() { fill(P, P + 8 * dd, -2); fill(T, T + 4 * dd, -2); }

	void push(int v) {
		if (P[v] != -2) {
			P[v * 2] = P[v];
			P[v * 2 + 1] = P[v];
			T[v] = P[v];
			P[v] = -2;
		}
	}

	void upd(int v, int tl, int tr, int l, int r, int val) {
		push(v);
		if (tl == l && tr == r) {
			P[v] = val;
		} else {
			int tm = (tl + tr) / 2;
			if (r <= tm) upd(v * 2, tl, tm, l, r, val);
			else if (l > tm) upd(v * 2 + 1, tm + 1, tr, l, r, val);
			else upd(v * 2, tl, tm, l, tm, val), upd(v * 2 + 1, tm + 1, tr, tm + 1, r, val);
			push(v * 2), push(v * 2 + 1);
			T[v] = max(T[v * 2], T[v * 2 + 1]);
		}
	}

	int get(int v, int tl, int tr, int pos) {
		push(v);
		if (tl == tr) return T[v];
		int tm = (tl + tr) / 2;
		if (pos <= tm) return get(v * 2, tl, tm, pos);
		return get(v * 2 + 1, tm + 1, tr, pos);
	}
} FL, FR;

struct SegmentTree {
	ll P[4 * dd];
	pair<ll, int> T[4 * dd];

	void build(int v, int tl, int tr) {
		P[v] = 0;
		if (tl == tr) {
			T[v] = { 0, tl };
		} else {
			int tm = (tl + tr) / 2;
			build(v * 2, tl, tm), build(v * 2 + 1, tm + 1, tr);
			T[v] = max(T[v * 2], T[v * 2 + 1]);
		}
	}

	void upd(int v, int tl, int tr, int l, int r, ll val) {
		if (tl == l && tr == r) {
			P[v] += val;
			T[v].first += val;
		} else {
			int tm = (tl + tr) / 2;
			if (r <= tm) upd(v * 2, tl, tm, l, r, val);
			else if (l > tm) upd(v * 2 + 1, tm + 1, tr, l, r, val);
			else upd(v * 2, tl, tm, l, tm, val), upd(v * 2 + 1, tm + 1, tr, tm + 1, r, val);
			T[v] = max(T[v * 2], T[v * 2 + 1]);
			T[v].first += P[v];
		}
	}

	pair<ll, int> get() {
		return T[1];
	}
} T;

int n, m;

struct ev {
	int first, second, fin;
};

void cut(int d, bool inv = false) {
	sort(P, P + iP);
	vector<ev> stL, stR;
	
	T.build(1, 0, n - 1);
	FL.clear(), FR.clear();
	
	int j = 0;

	for (int x = 0; x < n; x++) {

		FL.upd(1, 0, n - 1, x, x, -1);
		FR.upd(1, 0, n - 1, x, x, m);

		stL.push_back({ x, -1, x });
		stR.push_back({ x, m, x });

		T.upd(1, 0, n - 1, x, x, pY[m] - pY[0] - pX[x]);

		while (j < iP && P[j].first == x) {
			if (P[j].second <= d) {
				int last = x;
				while (stL.size() && stL.back().second <= P[j].second) {

					ll add = (-pY[P[j].second + 1]) - (-pY[stL.back().second + 1]);
					T.upd(1, 0, n - 1, stL.back().first, stL.back().fin, add);

					last = stL.back().first;
					stL.pop_back();
				}

				FL.upd(1, 0, n - 1, last, x, P[j].second);
				stL.push_back({ last, P[j].second, x });

			} else {
				int last = x;
				while (stR.size() && stR.back().second >= P[j].second) {

					ll add = (pY[P[j].second]) - pY[stR.back().second];
					T.upd(1, 0, n - 1, stR.back().first, stR.back().fin, add);

					last = stR.back().first;
					stR.pop_back();
				}

				FR.upd(1, 0, n - 1, last, x, P[j].second);
				stR.push_back({ last, P[j].second, x });
			}
			j++;
		}

		auto c = T.get();

		ll cur = pX[x + 1] + c.first;

		if (cur > ans) {
			ans = cur;
			(inv ? y1 : x1) = FL.get(1, 0, n - 1, c.second) + 1, (inv ? y2 : x2) = FR.get(1, 0, n - 1, c.second) - 1;
			(inv ? x1 : y1) = c.second, (inv ? x2 : y2) = x;
		}
	}

}

int solve() {
	scanf("%d %d", &n, &m);

	for (int i = 0; i < n; i++) scanf("%lld", &A[i]);
	for (int i = 0; i < n; i++) scanf("%lld", &X[i]);

	for (int i = 0; i < m; i++) scanf("%lld", &B[i]);
	for (int i = 0; i < m; i++) scanf("%lld", &Y[i]);

	for (int i = 0; i < n; i++) pX[i + 1] = pX[i] + X[i];
	for (int i = 0; i < m; i++) pY[i + 1] = pY[i] + Y[i];

	fill(iA, iA + n + m, -1);
	fill(iB, iB + n + m, -1);

	for (int i = 0; i < n; i++) iA[A[i] - 1] = i;
	for (int i = 0; i < m; i++) iB[B[i] - 1] = i;

	for (int c = 0; c < n + m; c++) if (iA[c] != -1 && iB[c] != -1) 
		P[iP++] = { iA[c], iB[c] };

	ans = pX[n];
	x1 = 0, x2 = n - 1;
	y1 = y2 = -1;

	if (pY[m] > ans) {
		ans = pY[m];
		x1 = x2 = -1;
		y1 = 0, y2 = m - 1;
	}

	for (int i = 0; i < m; i++) {
		if (pY[i + 1] >= pY[m] / 2) {
			cut(i, true);
			break;
		}
	}

	swap(A, B);
	swap(X, Y);
	swap(pX, pY);
	swap(iA, iB);
	swap(n, m);

	iP = 0;
	for (int c = 0; c < n + m; c++) if (iA[c] != -1 && iB[c] != -1)
		P[iP++] = { iA[c], iB[c] };
	

	for (int i = 0; i < m; i++) {
		if (pY[i + 1] >= pY[m] / 2) {
			cut(i);
			break;
		}
	}
	printf("%lld\n", ans);
	printf("%d %d\n", x1 + 1, x2 + 1);
	printf("%d %d\n", y1 + 1, y2 + 1);
	return 0;
}