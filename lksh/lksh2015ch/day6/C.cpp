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
#define pair ppair

struct pair {
	ll first, second, c, s;
	pair(ll first, ll second, ll c, ll s) : first(first), second(second), c(c), s(s) {}
	bool operator < (pair b) const {
		if (first == b.first)
			return second < b.second;
		return first < b.first;
	}
};

struct frac {
	ll a, b;
	frac(ll a, ll b) : a(a), b(b) {}
	bool operator < (frac g) const {
		ll c = g.a, d = g.b;
		return (a * d < b * c);
	}
	void out() const {
		printf("%.10f\n", a * 1.0 / b);
	}
};

set<pair> s;
multiset<frac> ans;

int solve() {
	int n;
	scanf("%d", &n);
	forn(i, n) {
		ll l, r, c, curc = 0, curs = 0;
		scanf("%lld%lld%lld", &l, &r, &c);

		if (!i) {
			s.insert(pair(l, r, 1, c));
			ans.insert(frac(c, 1));

			(ans.rbegin())->out();
			continue;
		}

		set<pair>::iterator it = s.lower_bound(pair(l, 0, 1, c)), a = it, b = it;

		curc = 1, curs = c;
		pair cur(l, r, 1, c);

		if (it == s.begin()) {

			while (b != s.end() && b->first < r) {
				curs += b->s;
				curc += b->c;

				r = max(r, b->second);

				ans.erase(ans.find(frac(b->s, b->c)));

				b++;
			}

			s.erase(a, b);
			ans.insert(frac(curs, curc));
			s.insert(pair(l, r, curc, curs));

			(ans.rbegin())->out();
			continue;
		}
		it--;
		if (it->second > l) {
			l = min(l, it->first);
			a = it;
		}
		else {
			it++;
			a = it;
		}

		b = it;
		while (b != s.end() && b->first < r) {
			curs += b->s;
			curc += b->c;

			r = max(r, b->second);
			ans.erase(ans.find(frac(b->s, b->c)));
			b++;
		}

		s.erase(a, b);

		s.insert(pair(l, r, curc, curs));
		ans.insert(frac(curs, curc));

		(ans.rbegin())->out();
	}
	return 0;
}