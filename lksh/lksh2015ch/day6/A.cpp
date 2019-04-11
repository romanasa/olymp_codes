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

using namespace std;

typedef unsigned long long ull;
typedef long long ll;
typedef long double ld;

#define forn(i, n) for (int i = 0; i < (int)n; i++)
#define fornn(i, q, n) for (int i = q; i < (ll)n; i++)
#define mp make_pair
#define pk push_back
#define all(v) v.begin(), v.end()
#define times clock() * 1.0 / CLOCKS_PER_SEC
#define prev pprev

#define TASK "sum2"

const double eps = 1e-7;
const double pi = acos(-1.0);

const ll INF = (ll)2e9 + 1;
const ll LINF = (ll)8e18;
const ll inf = (ll)2e9 + 1;
const ll linf = (ll)8e18;
const ll MM = (ll)1e9 + 7;

int solve();
void gen();

int main()
{
#ifdef _DEBUG
	freopen("input.txt", "r", stdin), freopen("output.txt", "w", stdout);
#else
	//freopen(TASK".in", "r", stdin), freopen(TASK".out", "w", stdout);
	//freopen("input.txt", "r", stdin), freopen("output.txt", "w", stdout), freopen("test.txt", "w", stderr);
#endif
	solve();
	return 0;
}

const int MAXN = 1e5 + 7;

int T[4 * MAXN], P[4 * MAXN];

void push(int v) {
	P[v * 2] += P[v];
	P[v * 2 + 1] += P[v];

	T[v] += P[v];
	P[v] = 0;
}

int get(int v) {
	return T[v] + P[v];
}

void update(int v, int tl, int tr, int l, int r, int val) {
	push(v);
	if (tl == l && tr == r) {
		P[v] += val;
	}
	else {
		int tm = (tl + tr) / 2;
		if (r <= tm)
			update(v * 2, tl, tm, l, r, val);
		else if (l > tm)
			update(v * 2 + 1, tm + 1, tr, l, r, val);
		else {
			update(v * 2, tl, tm, l, tm, val);
			update(v * 2 + 1, tm + 1, tr, tm + 1, r, val);
		}
		T[v] = min(get(v * 2), get(v * 2 + 1));
	}
}

int get(int v, int tl, int tr, int pos) {
	push(v);
	if (tl == pos && tr == pos) {
		return T[v];
	}
	int tm = (tl + tr) / 2;
	if (pos <= tm)
		return get(v * 2, tl, tm, pos);
	else if (pos <= tr)
		return get(v * 2 + 1, tm + 1, tr, pos);
}

void build(int v, int tl, int tr, int *a) {
	if (tl == tr)
		T[v] = a[tl];
	else {
		int tm = (tl + tr) / 2;
		build(v * 2, tl, tm, a);
		build(v * 2 + 1, tm + 1, tr, a);
		T[v] = min(T[v * 2], T[v * 2 + 1]);
	}
}

int a[MAXN];

int solve() {
	int n;
	cin >> n;
	forn(i, n) 
		scanf("%d", a + i);
	
	sort(a, a + n);

	build(1, 0, n - 1, a);

	int m;
	cin >> m;

	forn(i, m) {
		int k;
		scanf("%d", &k);

		int l = -1, r = n - 1;
		while (r - l > 1) {
			int mid = (l + r) / 2;
			if (get(1, 0, n - 1, mid) < k)
				l = mid;
			else
				r = mid;	
		}
		if (get(1, 0, n - 1, r) < k)
			r++;

		printf("%d\n", n - r);
		if (r < n)
			update(1, 0, n - 1, r, n - 1, -1);
	}
	return 0;
}