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
#include <unordered_set>

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

#define TASK "king"

const double eps = 1e-7;
const double pi = acos(-1.0);

const ll INF = (ll)2e9 + 1;
const ll LINF = (ll)8e18;
const ll inf = (ll)2e9 + 1;
const ll linf = (ll)2e18;
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


bool is_pr(ull x) {

	if (x < 2)
		return false;
	for (ull i = 2; i * i <= x; i++)
		if (x % i == 0)
			return false;
	return true;
}


int solve() {

	/*fornn(i, 2, 10000007)
		F[i] = 1;
	for (int i = 2; i * i < 10000007; i++)
		if (F[i])
			for (int j = i * i; j < 10000007; j += i)
				F[j] = 0;*/


	ull x;
	cin >> x;
	x--;
	vector<ull> ans, cur;

	for (ull i = 2; i * i <= x; i++) {

		while (x % i == 0) {
			ans.push_back(i);
			cur.push_back(x / i);

			x /= i;
		}
		
	}
	
	if (x > 1)
		for (ull i : cur) {
			if (x % i == 0) {
				ans.push_back(i);
				x /= i;
			}
		}

	if (ans.size() == 0) {
		ans.push_back(x);
	}

	cout << ans.size() << "\n";
	for (ull i : ans)
		cout << i - 1 << " ";
	return 0;
}