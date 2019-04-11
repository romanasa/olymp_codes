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

int dx[] = {-1,  0,  1,  0 };
int dy[] = { 0, -1,  0,  1 };
int dg[] = {-1, 1, 2 };

int used[107][107][4], n, m;
string st[107], en[107];

bool ok(int i, int j) {
	return i >= 0 && i < n && j >= 0 && j < m;
}

bool ok2(int i, int j, int g, string *a) {
	if (!ok(i, j))
		return false;
	if ((g % 2 == 0) && (j == 0 || j == m - 1 || a[i][j - 1] == '*' || a[i][j + 1] == '*' || a[i][j] == '*'))
		return false;
	if ((g % 2) && (i == 0 || i == n - 1 || a[i - 1][j] == '*' || a[i + 1][j] == '*' || a[i][j] == '*'))
		return false;
	return true;
}

bool is1(int i, int j, string *a) {
	return (ok(i, j - 1) && ok(i, j + 1) && a[i][j - 1] == '\\' && a[i][j + 1] == '/' && a[i][j] == '-');
}

bool is2(int i, int j, string *a) {
	return (ok(i - 1, j) && ok(i + 1, j) && a[i - 1][j] == '\\' && a[i + 1][j] == '/' && a[i][j] == '|');
}

bool is3(int i, int j, string *a) {
	return (ok(i, j - 1) && ok(i, j + 1) && a[i][j - 1] == '/' && a[i][j + 1] == '\\' && a[i][j] == '-');
}

bool is4(int i, int j, string *a) {
	return (ok(i - 1, j) && ok(i + 1, j) && a[i - 1][j] == '/' && a[i + 1][j] == '\\' && a[i][j] == '|');
}

int solve() {
	forn(i, 107)
		forn(j, 107)
			forn(g, 4)
				used[i][j][g] = inf;

	cin >> n >> m;

	forn(i, n)
		cin >> st[i];

	forn(i, n)
		cin >> en[i];

	queue<pair<pair<int, int>, int> > q;

	forn(i, n)
		forn(j, m) {
			if (is1(i, j, st))
				used[i][j][0] = 0, q.push(mp(mp(i, j), 0));
			if (is2(i, j, st))
				used[i][j][1] = 0, q.push(mp(mp(i, j), 1));
			if (is3(i, j, st))
				used[i][j][2] = 0, q.push(mp(mp(i, j), 2));
			if (is4(i, j, st))
				used[i][j][3] = 0, q.push(mp(mp(i, j), 3));
		}


	while (q.size()) {
		pair<pair<int, int>, int> v = q.front();
		q.pop();
		int i = v.first.first, j = v.first.second;
		int g = v.second;

		int ni = i + dx[g], nj = j + dy[g];
		if (ok2(ni, nj, g, st) && used[ni][nj][g] > used[i][j][g] + 1)
			used[ni][nj][g] = used[i][j][g] + 1, q.push(mp(mp(ni, nj), g));

		forn(gg, 3) {
			int ng = (g + dg[gg] + 4) % 4;
			if (ok2(i, j, ng, st) && used[i][j][ng] > used[i][j][g] + 1)
				used[i][j][ng] = used[i][j][g] + 1, q.push(mp(mp(i, j), ng));
		}
	}

	forn(i, n)
		forn(j, m) {
			if (is1(i, j, en))
				cout << (used[i][j][0] == inf ? -1 : used[i][j][0]);
			if (is2(i, j, en))
				cout << (used[i][j][1] == inf ? -1 : used[i][j][1]);
			if (is3(i, j, en))
				cout << (used[i][j][2] == inf ? -1 : used[i][j][2]);
			if (is4(i, j, en))
				cout << (used[i][j][3] == inf ? -1 : used[i][j][3]);
	}
	return 0;
}