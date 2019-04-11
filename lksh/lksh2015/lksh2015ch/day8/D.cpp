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

int n;

int pr(int i) {
	return (i + n - 1) % n;
}

vector<int> zf(string s) {
	int n = s.size();
	vector<int> z(n);

	for (int i = 1, l = 0, r = 0; i < n; i++) {
		if (i <= r)
			z[i] = min(z[i - l], r - i + 1);

		while (i + z[i] < n && s[z[i]] == s[i + z[i]])
			z[i]++;

		if (i + z[i] - 1 > r)
			l = i, r = i + z[i] - 1;
	}
	return z;
}

int solve() {
	string s;
	cin >> s;
	n = s.size();
	char minc = (char)('z' + 1);
	char maxc = (char)('a' - 1);

	forn(i, s.size()) {
		minc = min(minc, s[i]),
		maxc = max(maxc, s[i]);
	}
	int mind = inf;

	vector<int> z = zf(s);
	int per = n;
	fornn(i, 1, n)
		if (n % i == 0 && i + z[i] == n) {
			per = i;
			break;
		}

	forn(i, per) 
		mind = min(mind, (max(maxc - s[i], s[i] - minc) + max(maxc - s[pr(i)], s[pr(i)] - minc)));

	int cur = 0;
	forn(i, per) 
		cur += max(maxc - s[i], s[i] - minc) + max(maxc - s[pr(i)], s[pr(i)] - minc) == mind; 
	
	cout << mind << " " << cur;
	return 0;
}