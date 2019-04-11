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

int c = 0, n, m;
vector<vector<vector<int> > > num;

vector<vector<int> > a(16, vector<int>(16, 0)), cur;
int matr[133][133];

void out(vector<vector<int> > &a) {
	forn(i, a.size())
		forn(j, a[i].size())
		cout << a[i][j] << " \n"[j == a[i].size() - 1];
	printf("\n\n");
}

bool equals(vector<vector<int> > &a, vector<vector<int> > &b) {
	forn(i, m)
		forn(j, m)
			if (a[i][j] != b[i][j])
				return false;
	return true;
}

void gen_next(int v, int nm, bool ff = true) {
	if (v == m) {
		vector<vector<int> > g(m, vector<int>(m, 0));

		forn(i, m)
			forn(j, m)
				g[i][j] = a[i][j + 1];

		int ddd = -1;
		forn(k, num.size()) {
			if (equals(num[k], g)) {
				ddd = k;
				break;
			}
		}

		if (ddd == -1) {
			num.pk(g);
			ddd = num.size() - 1;
		}

		if (ff) 
			matr[nm][ddd] = 1;
	}

	if (a[v][1] == 1)
		gen_next(v + 1, nm, ff);

	fornn(i, 1, m + 1) {
		if (v + i > m)
			continue;
		bool ok = true;

		for (int x = 0 + 1; x < i + 1; x++)
			for (int y = v; y < v + i; y++)
				if (a[y][x])
					ok = false;

		if (ok) {
			for (int x = 0 + 1; x < i + 1; x++)
				for (int y = v; y < v + i; y++)
					a[y][x] = 1;

			gen_next(v + i, nm, ff);

			for (int x = 0 + 1; x < i + 1; x++)
				for (int y = v; y < v + i; y++)
					a[y][x] = 0;
		}
	}
}

void gen(int v) {
	if (v == m) {
		vector<vector<int> > f(m, vector<int>(m, 0));
		forn(i, m)
			forn(j, m)
				f[i][j] = a[i][j];
		int ddd = -1;
		forn(k, num.size()) {
			if (equals(num[k], f)) {
				ddd = k;
				break;
			}
		}
		if (ddd == -1) {
			num.pk(f);
			ddd = num.size() - 1;
		}

		gen_next(0, ddd, 0);
	}
	fornn(i, 1, m + 1) {
		if (v + i > m)
			continue;

		for (int x = 0; x < i; x++)
			for (int y = v; y < v + i; y++)
				a[y][x] = 1;

		gen(v + i);

		for (int x = 0; x < i; x++)
			for (int y = v; y < v + i; y++)
				a[y][x] = 0;
	}
}

ll dp[1007][133];

void out(int c) {
	forn(i, c)
		forn(j, c)
			if (matr[i][j]) {
				cout << i << " " << j << "\n\n";
				out(num[i]);
				printf("toto\n\n");
				out(num[j]);
			}
}

int solve() {
	cin >> n >> m;
	if (m > n)
		swap(m, n);
	gen(0);
	forn(i, num.size()) {
		forn(j, m)
			forn(k, m)
				a[j][k] = num[i][j][k];
		gen_next(0, i);
	}

	dp[0][0] = 1;
	c = num.size();
	fornn(i, 1, n + 1) {
		forn(j, c) {
			forn(k, c) {
				dp[i][k] = (dp[i][k] + dp[i - 1][j] * matr[j][k]) % MM;
			}
		}
	}

	//out(c);

	cout << dp[n][0];
	return 0;
}