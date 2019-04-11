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

const int cc = 410;
const int MAXN = 1e5 + 7;

ll n, m, k, a[MAXN], pref[MAXN];

struct block {
	vector<pair<int, int> > cur;
	vector<int> tosort, tonum, val;
	int left, right, last;
	ll ans = 0, extr = 0;

	int size() {
		return right - left + 1;
	}

	void count() {
		last = right;
		for (int i = left; i <= right; i++)
			if (a[i] >= m)
				last--, a[i] = m;

		ans = 0;
		for (int i = left; i <= right; i++)
			ans += a[i];

		for (int i = left; i <= right; i++) {
			pref[i] = (i > left ? pref[i - 1] : 0) + cur[i - left].first;
		}
	}

	void update_left(int r, ll c) {
		int l = left;
		for (int i = l; i <= r; i++)
			a[i] += c;
		msort();
		count();
	}

	void update_right(int l, ll c) {
		int r = right;
		for (int i = l; i <= r; i++)
			a[i] += c;
		msort();
		count();
	}

	void update(int l, int r, ll c) {
		for (int i = l; i <= r; i++)
			a[i] += c;
		msort();
		count();
	}

	void msort() {
		for (int i = left; i <= right; i++)
			cur.pk(mp(min(a[i] + extr, m), i));

		sort(all(cur));

		forn(i, cur.size()) {
			int to = cur[i].second;
			tosort[to] = i, tonum[i] = to;
		}
	}

	void update(ll c) {
		int l = left, r = last + 1;
		while (r - l > 1) {
			int mid = (l + r) / 2;
			if (a[mid] + c + extr < m)
				l = m;
			else
				r = m;
		}
		extr += c;
		ans -= pref[last] - pref[l];
		last = l;
		ans += (right - last) * m;
	}

	block(int l, int r) {
		left = l, right = r, last = r;
		val.resize(size());

		tosort.resize(size());
		tonum.resize(size());	

		msort();
		count();
	}
};

int solve() {
	cin >> n >> m >> k;	
	return 0;
}