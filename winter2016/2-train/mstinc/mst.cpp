#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <set>
#include <map>
#include <bitset>
#include <string>
#include <fstream>
#include <vector>
#include <cstring>
#include <cassert>
#include <random>
#include <ctime>
#include <numeric>

using namespace std;

typedef long long ll;
typedef double ld;

int solve();
#define TASK "qual"
#define err(...) fprintf(stdout, __VA_ARGS__), fflush(stdout)

int main() {
#ifdef HOME
	//freopen("input.txt", "r", stdin), freopen("output.txt", "w", stdout);
#else
	//freopen(TASK".in", "r", stdin), freopen(TASK".out", "w", stdout);
#endif
	solve();
}

const int dd = (int)1e6 + 7;

struct ev { int tp, a, b, c; } A[dd];

map<string, int> M;
int nv = 1;

int getnum(string s) {
	auto it = M.find(s);
	if (it != M.end()) return it->second;
	return M[s] = nv++;
}

ev get(string s) {
	ev T = { 0, -1, -1, -1 };
	string cur, t;
	int i = (s[0] == ' ' ? 1 : 0);
	for (; i < (int)s.size() && s[i] != ' '; i++) cur.push_back(s[i]);
	if (cur == "var") {
		T.tp = 1;
		for (i++, cur = ""; i < (int)s.size(); i++) cur.push_back(s[i]);
	}
	for (i = 0; i < (int)cur.size() && cur[i] != '='; i++) t.push_back(cur[i]);
	T.c = getnum(t);
	t = "";
	for (i++; i < (int)cur.size(); i++) {
		if (isalnum(cur[i])) {
			t.push_back(cur[i]);
		} else {
			if (isalpha(t[0])) (T.a == -1 ? T.a : T.b) = getnum(t);
			t = "";
		}
	}
	if (isalpha(t[0])) (T.a == -1 ? T.a : T.b) = getnum(t);
	return T;
}

set<int> V[dd], U[dd];
int v[dd];

struct SegmentTreeVar {
	int T[4 * dd];

	SegmentTreeVar() { fill(T, T + 4 * dd, -1); }

	void upd(int v, int tl, int tr, int pos, int val) {
		if (tl == tr) {
			T[v] = val;
		} else {
			int tm = (tl + tr) / 2;
			if (pos <= tm)
				upd(v * 2, tl, tm, pos, val);
			else
				upd(v * 2 + 1, tm + 1, tr, pos, val);

			T[v] = max(T[v * 2], T[v * 2 + 1]);
		}
	}

	int get(int v, int tl, int tr, int l, int r) {
		if (l == tl && tr == r)
			return T[v];
		int tm = (tl + tr) / 2;
		if (r <= tm)
			return get(v * 2, tl, tm, l, r);
		if (l > tm)
			return get(v * 2 + 1, tm + 1, tr, l, r);
		return max(get(v * 2, tl, tm, l, tm), get(v * 2 + 1, tm + 1, tr, tm + 1, r));
	}
} TV;

struct SegmentTreeUse {
	int T[4 * dd];

	SegmentTreeUse() { fill(T, T + 4 * dd, (int)1e9); }

	void upd(int v, int tl, int tr, int pos, int val) {
		if (tl == tr) {
			T[v] = val;
		} else {
			int tm = (tl + tr) / 2;
			if (pos <= tm)
				upd(v * 2, tl, tm, pos, val);
			else
				upd(v * 2 + 1, tm + 1, tr, pos, val);

			T[v] = min(T[v * 2], T[v * 2 + 1]);
		}
	}

	int get(int v, int tl, int tr, int l, int r) {
		if (l == tl && tr == r)
			return T[v];
		int tm = (tl + tr) / 2;
		if (r <= tm)
			return get(v * 2, tl, tm, l, r);
		if (l > tm)
			return get(v * 2 + 1, tm + 1, tr, l, r);
		return min(get(v * 2, tl, tm, l, tm), get(v * 2 + 1, tm + 1, tr, tm + 1, r));
	}
} TU;

int N;

void add1U(int x, int ind) {
	if (x == -1) return;
	auto it = U[x].lower_bound(ind);
	int val = (it == U[x].begin() ? -1 : *(--it));
	if (V[x].count(ind))
		TU.upd(1, 0, N, ind, (int)1e9);
	else
		TU.upd(1, 0, N, ind, val);
}

void add1V(int x, int ind) {
	auto it = V[x].lower_bound(ind);
	int val = (it == V[x].begin() ? -1 : *(--it));
	TV.upd(1, 0, N, ind, val);
}

void delV(int a) {
	auto it = V[A[a].c].lower_bound(3 * a + 2);
	auto nxt = it;
	++nxt;
	int pos = -1;
	if (it != V[A[a].c].begin()) {
		auto prv = it;
		pos = *(--prv);
	}
	if (nxt != V[A[a].c].end()) {
		TV.upd(1, 0, N, *nxt, pos);
	}
	V[A[a].c].erase(it);
	TV.upd(1, 0, N, 3 * a + 2, -1);
}

void delU(int x, int ind) {
	if (x == -1) return;
	auto it = U[x].lower_bound(ind);
	auto nxt = it;
	++nxt;
	int pos = -1;
	if (it != U[x].begin()) {
		auto prv = it;
		pos = *(--prv);
	}
	if (nxt != U[x].end() && !V[x].count(*nxt)) {
		TU.upd(1, 0, N, *nxt, pos);
	}
	U[x].erase(ind);
	TU.upd(1, 0, N, ind, (int)1e9);
}

void addV(int a) {
	V[A[a].c].erase(3 * a + 2);
	auto nxt = V[A[a].c].lower_bound(3 * a + 2);
	if (nxt != V[A[a].c].end()) {
		TV.upd(1, 0, N, *nxt, 3 * a + 2);
	}
	auto prv = nxt;
	if (prv != V[A[a].c].begin()) {
		--prv;
		TV.upd(1, 0, N, 3 * a + 2, *prv);
	}
	V[A[a].c].insert(3 * a + 2);
}

void addU(int x, int ind) {
	if (x == -1) return;
	U[x].erase(ind);
	auto nxt = U[x].lower_bound(ind);
	if (nxt != U[x].end() && !V[x].count(*nxt)) {
		TU.upd(1, 0, N, *nxt, ind);
	}
	int pos = -1;
	auto prv = nxt;
	if (prv != U[x].begin()) {
		pos = *(--prv);
	}
	if (V[x].count(ind))
		TU.upd(1, 0, N, ind, (int)1e9);
	else
		TU.upd(1, 0, N, ind, pos);
	U[x].insert(ind);
}

int solve() {
	int n;
	cin >> n;

	N = 3 * n - 1;

	string s;
	getline(cin, s);
	for (int i = 0; i < n; i++) {
		getline(cin, s);
		A[i] = get(s);

		if (A[i].tp == 1) V[A[i].c].insert(3 * i + 2);
		U[A[i].c].insert(3 * i + 2);
		if (A[i].a != -1) U[A[i].a].insert(3 * i + 0);
		if (A[i].b != -1) U[A[i].b].insert(3 * i + 1);
	}

	for (int i = 0; i < n; i++) {
		if (A[i].tp == 1) add1V(A[i].c, 3 * i + 2);
		add1U(A[i].c, 3 * i + 2);
		add1U(A[i].b, 3 * i + 1);
		add1U(A[i].a, 3 * i + 0);
	}

	int m;
	cin >> m;

	for (int i = 0; i < m; i++) {
		cin >> s;

		if (s == "fix") {
			int a;
			string t;

			cin >> a;
			getline(cin, t);

			a--;

			delU(A[a].c, 3 * a + 2);
			delU(A[a].b, 3 * a + 1);
			delU(A[a].a, 3 * a + 0);
			if (A[a].tp == 1) delV(a);

			A[a] = get(t);

			if (A[a].tp == 1) addV(a);
			addU(A[a].c, 3 * a + 2);
			addU(A[a].b, 3 * a + 1);
			addU(A[a].a, 3 * a + 0);
		} else {
			int l, r;
			cin >> l >> r;

			int L = (l - 1) * 3, R = 3 * r - 1;
			if (TV.get(1, 0, N, L, R) < L && TU.get(1, 0, N, L, R) > L)
				puts("YES");
			else
				puts("NO");
		}
	}
	return 0;
}