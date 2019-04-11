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

#define TASK "sum2"

const double eps = 1e-7;
const double pi = acos(-1.0);

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

const int MAXC = 2e6 + 7;

int P[MAXC], B[MAXC], Q[MAXC];

int solve() {
	int n, a, b, c;

	cin >> n >> a >> b >> c;
	forn(i, n) {
		int a, b;
		cin >> a >> b;

		B[a]++;
		B[b + 1]--;
	}

	int cur = 0;
	forn(i, a + 1) {
		cur += B[i];
		P[i] = cur;
	}

	Q[0] = P[0];
	fornn(i, 1, a + 1) 
		Q[i] = Q[i - 1] + P[i];

	forn(i, a + 1) {
		if (Q[i + b] - Q[i] > c) {
			cout << "No";
			return 0;
		}
	}

	cout << "Yes";

	return 0;
}