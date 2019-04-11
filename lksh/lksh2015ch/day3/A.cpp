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

const int MAXN = 1e6 + 7;
int a[MAXN], b[MAXN], pol = 1;

void add(int x, int y) {
	x++, y--;
	b[x]++, b[y + 1]--;
}

int solve() {
	int w, h, n;
	cin >> w >> h >> n;

	forn(i, n) {
		int x1, x2, y1, y2;
		cin >> x1 >> y1 >> x2 >> y2;

		if (x2 < x1)
			swap(x1, x2);

		if (y2 < y1)
			swap(y1, y2);

		add(x1 + y1, x2 + y2);

		int c = 1;
		while (x1 + y1 <= h + w) {
			x1 += w, x2 += w;
			c++;
			add(x1 + y1, x2 + y2);
		}
		pol = max(pol, c);
	}

	int cur = 0;
	forn(i, pol * w + 1) {
		cur += b[i];
		a[i] = cur;
	}

	fornn(i, (pol - 1) * w, pol * w)
		if (!a[i]) {
			cout << "Yes\n";
			cout << (w - (i % w));
			exit(0);
		}
	cout << "No";

	return 0;
}