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

struct pt {
	ll x, y;
};

ll dist(pt a, pt b) {
	return (b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y);
}

bool cmp(pair<pair<ll, ll>, int> g, pair<pair<ll, ll>, int> f) {
	ll a = g.first.first, b = g.first.second, c = f.first.first, d = f.first.second;
	if (a * d == b * c) {
		return g.second < f.second;
	}
	return a * d > b * c;
}

int solve() {
	ll n, m, r, l;
	cin >> n >> m >> r >> l;

	vector<pt> fr(n), an(m);
	vector<ll> z(m);
	vector<pair<pair<ll, ll>, int> > b(n);

	forn(i, n) {
		cin >> fr[i].x >> fr[i].y;
	}
	forn(i, m) {
		cin >> an[i].x >> an[i].y >> z[i];
	}

	forn(i, n) {
		ll cost = 0;
		if (fr[i].x * fr[i].x + fr[i].y * fr[i].y <= r * r)
			cost = 2;
		else
			cost = 3;

		ll d = fr[i].x * fr[i].x + fr[i].y * fr[i].y;

		ll cur = 1;
		forn(j, m) {
			if (dist(fr[i], an[j]) <= l * l)
				cur += z[j];
		}

		b[i] = mp(mp(cost, d * cur), i);
	}
	sort(all(b), cmp);
	forn(i, b.size())
		cout << b[i].second + 1 << " ";
	return 0;
}