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

const int dd = 2e3 + 7;

int A[5007][5007];
int lg[100007];
map<int, int> M;
set<int> S;

bool H[10007][207];

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
	lg[1] = 0;
	fornn(i, 2, dd)
		lg[i] = lg[i / 2] + 1;
	lg[0] = lg[1] = 1;


	int n, m, c = 0;
	srand(137);
	scanf("%d%d", &n, &m);

	if (n == 1) {
		cout << 0;
		return 0;
	}

	vector<vector<int> > G(n, vector<int>(m));

	forn(i, n) {
		forn(j, m) {
			scanf("%d", &G[i][j]);
			c = max(c, G[i][j]);
		}
	}

	forn(i, n) {
		sort(all(G[i]));
	}

	int ans = 0, gg = 0;

	if (n * n / 2 * m < 2e8) {
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

	if (c <= 200) {

		random_shuffle(all(G));

		gg = 0;
		forn(ii, n) {
			fornn(jj, ii + 1, n) {
				if (gg > 2e8 / (n * n)) {
					break;
				}

				ans = max(ans, check(G[ii], G[jj]));
				gg++;
			}

			if (gg > 2e8 / (n * n)) {
				break;
			}
		}
		cout << ans + 1;
		return 0;
	}

	forn(i, n)
		forn(j, m)
			S.insert(G[i][j]);

	int i = 0;
	for (int s : S)
		M[s] = i++;

	vector<vector<char> > H(n, vector<char>(S.size(), false));
	forn(i, n) {
		forn(j, m) {
			H[i][M[G[i][j]]] = true;
		}
	}

	int k = (lg[n] + 1);

	forn(i, 1 << k) {
		forn(j, 1 << k) {
			forn(l, k)
				A[i][j] += ((i & (1 << l)) > 0) * ((j & (1 << l)) > 0);
		}
	}

	vector<vector<int> > J(n);
	forn(i, n) {
		for (int l = 0; l < S.size(); l += k) {
			int cc = 0;
			for (int p = l; p < l + k && p < S.size(); p++) {
				if (H[i][p])
					cc += (1 << (p - l));
			}
			J[i].push_back(cc);
		}
	}

	ans = 0;

	random_shuffle(all(G));

	int cc = 0;

	forn(i, n) {
		forn(j, i) {
			int cur = 0;
			for (int l = 0, g = 0; l < S.size(); l += k, g++) {
				cur += A[J[i][g]][J[j][g]];
			}
			ans = max(ans, cur);

			cc++;
			if (cc % 1000 == 0) {
				if (times > 1.8) {
					cout << ans + 1;
					return 0;
				}
			}
		}
	}
	cout << ans + 1;

	return 0;
}