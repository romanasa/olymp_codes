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

const ll p = 31;
const int MAXN = 2e5 + 7;

map<string, int> m;
set<int> S[MAXN];

int tmm = 0;
int num[MAXN];
set<int>::iterator beg[MAXN];

int solve() {
	int n;
	cin >> n;
	vector<string> s;

	s.reserve(MAXN);
	getchar();

	forn(i, n) {
		string v, nm, name;

		cin >> v;

		s.pk(v);

		forn(j, v.size())
			if (v[j] <= '9' && v[j] >= '0')
				nm.pk(v[j]);
			else
				name.pk(v[j]);
		
		num[i] = atoi(nm.c_str());
		s[i] = name;

		if (!m.count(name))
			m[name] = tmm++;
	}

	forn(i, n) 
		S[m[s[i]]].insert(num[i]);

	forn(i, tmm)
		beg[i] = S[i].begin();

	int k;
	cin >> k;
	getchar();

	forn(i, k) {
		string v; 
		char c;
		
		cin >> v;

		int ans = -1;

		if (!m.count(v)) {
			ans = 1;

			S[tmm].insert(ans);

			beg[tmm] = S[tmm].begin();

			m[v] = tmm++;
		}
		else {
			int ind = m[v];

			if (*S[ind].begin() != 1) {
				ans = 1;
				S[ind].insert(ans);

				beg[ind] = S[ind].begin();
			}
			else {
				for (set<int>::iterator it = beg[ind]; it != S[ind].end(); it++, beg[ind]++) {
					if (it == S[ind].begin())
						continue;

					set<int>::iterator pr = it;
					pr--;
					if (*it - *pr > 1) {
						ans = *pr + 1;
						beg[ind] = pr;
						break;
					}
				}

				if (ans == -1) {
					ans = *S[ind].rbegin() + 1;
					beg[ind] = S[ind].end();
				}

				S[ind].insert(ans);
			}
		}
		cout << ans << "\n";
	}
	return 0;
}