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

typedef unsigned long long ull;
typedef long long ll;
typedef long double ld;

#define forn(i, n) for (int i = 0; i < (int)n; i++)
#define fornn(i, q, n) for (int i = q; i < (ll)n; i++)
#define mp make_pair
#define pk push_back
#define all(v) v.begin(), v.end()
#define times clock() * 1.0 / CLOCKS_PER_SEC

#define TASK "olympiad"

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
	//freopen("input.txt", "r", stdin), freopen("output.txt", "w", stdout);
#else
	//freopen(TASK".in", "r", stdin), freopen(TASK".out", "w", stdout);
	//freopen("input.txt", "r", stdin), freopen("output.txt", "w", stdout), freopen("test.txt", "w", stderr);
#endif
	solve();
	return 0;
}

int A[57][57];

ull get(int x1, int y1, int x2, int y2) {

	/*ull t = 0;
	for (int i = x1; i <= x2; i++)
		for (int j = y1; j <= y2; j++)
			t += A[i][j];
	*/
	
	cout << "? " << x1 << " " << y1 << " " << x2 << " " << y2 << endl;
	
	ull t;
	cin >> t;

	//cout << t << endl;
	return t;
}

void ask(int x1, int y1, int x2, int y2) {
	cout << "! " << x1 << " " << y1 << " " << x2 << " " << y2 << endl;
	exit(0);
}

int solve() {
	int n;
	cin >> n;

	ll sum = get(1, 1, n, n);

	ll l = 0, r = n;

	while (r - l > 1) {
		ll m = (l + r) / 2;

		if (get(1, 1, m, n) > 0)
			r = m;
		else
			l = m;
	}

	ll x1 = r;

	l = 0, r = n;

	while (r - l > 1) {
		ll m = (l + r) / 2;

		if (get(1, 1, m, n) >= sum)
			r = m;
		else
			l = m;
	}
	ll x2 = r;

	l = 0, r = n;

	while (r - l > 1) {
		ll m = (l + r) / 2;

		if (get(1, 1, n, m) > 0)
			r = m;
		else
			l = m;
	}

	ll y1 = r;

	
	ll lenx = x2 - x1 + 1;
	ll leny = sum / lenx;

	ll y2 = y1 + leny - 1;

	ask(x1, y1, x2, y2);
	return 0;
}
