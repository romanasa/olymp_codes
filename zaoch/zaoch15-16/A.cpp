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

ll f(ll x) {
	return x * (x - 1) / 2;
}

int solve() {
	ll n, k;
	cin >> n >> k;

	ll ans1 = 0;
	ll old1 = k / (n / k);

	ll cf = k % (n / k);

	if (cf >= n / k) {
		ans1 = f(old1 + 1) * n / k;
	}
	else {
		ans1 = cf * f(old1 + 1) + (n / k - cf) * f(old1);
	}

	cout << ans1 * (n / k) << "\n";

	/*ll ans = 0;
	forn(i, n / k) {
		ll old = k / (n / k) + (k % (n / k) > i);
		ans += f(old);
	}

	cout << ans * (n / k);*/
	return 0;
}