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

int solve() {
	ll n, w, l;
	cin >> n >> w >> l;

	vector<pair<pair<ll, ll>, pair<ll, ll> > > req;

	forn(i, n) {
		ll x1, x2, y1, y2, z1, z2;
		cin >> x1 >> y1 >> z1 >> x2 >> y2 >> z2;

		ll sq = (x2 - x1) * (y2 - y1);

		req.pk(mp(mp(z1, 1), mp(sq, i)));
		req.pk(mp(mp(z2, 0), mp(sq, i)));
	}

	sort(all(req));

	ll csq = 0, op = 0;
	ll ans = inf;

	forn(i, req.size()) {
		ll x = req[i].first.first, sq = req[i].second.first;
		int tp = req[i].first.second, ind = req[i].second.second;

		if (tp)
			csq += sq, op++;
		else 
			csq -= sq, op--;

		if (csq == w * l)
			ans = min(ans, op);
	}

	if (ans == inf) {
		cout << "NO";
	}
	else {
		set<int> s;
		forn(i, req.size()) {
			ll x = req[i].first.first, sq = req[i].second.first;
			int tp = req[i].first.second, ind = req[i].second.second;

			if (tp) 
				csq += sq, op++, s.insert(ind);
			else 
				csq -= sq, op--, s.erase(ind);

			if (csq == w * l && op == ans) {
				cout << "YES\n";
				cout << s.size() << "\n";
				for (set<int>::iterator it = s.begin(); it != s.end(); it++)
					cout << (*it) + 1 << "\n";
				exit(0);
			}
		}
	}
	return 0;
}