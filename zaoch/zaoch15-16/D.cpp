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

int check(vector<int> &A, vector<int> &B) {
	int i = 0, j = 0, ans = 0;

	while (i < A.size() && j < B.size()) {
		if (A[i] == B[j])
			ans++;

		if (A[i] <= B[j])
			i++;
		else
			j++;
	}
	return ans;
}

int solve() {
	int n, m;
	srand(137);
	scanf("%d%d", &n, &m);

	if (n == 1) {
		cout << 0;
		return 0;
	}

	vector<vector<int> > G(n, vector<int>(m));

	forn(i, n) {
		forn(j, m)
			scanf("%d", &G[i][j]);
	}

	forn(i, n) {
		sort(all(G[i]));
	}

	int ans = 0, gg = 0;

	random_shuffle(all(G));

	forn(ii, n) {
		fornn(jj, ii + 1, n) {
			if (gg % 1000 == 0) {
				if (times > 1.1) {
					cout << ans + 1;
					return 0;
				}
			}
			gg++;
			ans = max(ans, check(G[ii], G[jj]));
		}
	}
	cout << ans + 1;
	return 0;
}