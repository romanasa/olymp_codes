#define _CRT_SECURE_NO_WARNINGS
#pragma comment(linker, "/STACK:256000000")
#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <bitset>
#include <sstream>
#include <fstream>
#include <ctime>
#include <cstring>
#include <numeric>
#include <queue>
#include <cassert>
#include <unordered_map>

using namespace std;

typedef long long ll;
typedef long double ld;

#define TASK "sorting"

int solve();

int main() {
#ifdef HOME
	freopen("input.txt", "r", stdin), freopen("output.txt", "w", stdout);
#else
	//freopen(TASK".in", "r", stdin), freopen(TASK".out", "w", stdout);
#endif
	solve();
}

int solve() {
	ll a, b, c, n;
	cin >> a >> b >> c >> n;

	b = min(b, 7 * a);
	c = min(c, 4 * b);

	cout << (n / 28) * c + min(((n % 28) / 7) * b + min((n % 7) * a, b), c);

	return 0;
}