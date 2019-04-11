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
	double x, y;
	pt() {}
	pt(double x, double y) : x(x), y(y) {}
};

struct vt {
	double x, y;
	vt(double x, double y) :x(x), y(y) {}
	vt(pt a, pt b) {
		x = b.x - a.x;
		y = b.y - a.y;
	}
	double len() {
		return sqrt(x * x + y * y);
	}
	void norm() {
		double cur = len();
		x /= cur, y /= cur;
	}
	vt operator * (int v) {
		return vt(x * v, y * v);
	}
};

double dist(pt a, pt b) {
	return sqrt((b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y));
}

pt st, en, ans;

double l1, l2, ansy, l[1007];

double f(double x, double y) {
	pt cur;
	cur.x = x, cur.y = y;
	return abs(dist(st, cur) - l1) + abs(dist(cur, en) - l2);
}

double f(double x) {
	double l = -10000, r = 10000;
	forn(gg, 50) {
		double m1 = l + (r - l) / 3,
			m2 = r - (r - l) / 3;
		if (f(x, m1) > f(x, m2))
			l = m1;
		else
			r = m2;
	}
	ansy = l;
	return f(x, l);
}

bool check(double l1, double l2) {
	if (dist(st, en) > l1 + l2) {
		return false;
	}
	double l = -10000, r = 10000;
	forn(gg, 50) {
		double m1 = l + (r - l) / 3,
			m2 = r - (r - l) / 3;
		if (f(m1) > f(m2))
			l = m1;
		else
			r = m2;
	}
	f(l);
	ans = pt(l, ansy);
	return true;
}

pt cross(pt O, double r, pt m, pt n) {
	double a = n.y - m.y, b = m.x - n.x, c = -(a * m.x + b * m.y);

	double dist = a * O.x + b * O.y + c;
	double cur = sqrt(r * r - dist * dist);
}

int solve() {
	int n;
	cin >> st.x >> st.y >> en.x >> en.y >> n;
	if (n == 1) {
		cin >> l1;
		if (dist(st, en) == l1) {
			cout << "YES\n";
			printf("%.10f %.10f\n", st.x, st.y);
			printf("%.10f %.10f", en.x, en.y);
		}
		else
			cout << "NO\n";
		exit(0);
	}

	forn(i, n)
		cin >> l[i];

	double l1 = 0, l2 = 0;
	forn(i, n)
		l2 += l[i];

	for (int i = 0; i < n + 1; i++) {
		if (check(l1, l2)) {
			cout << "YES\n";
			pt cur = ans;
			int f = i;
			while (cur.x != st.x && cur.y != st.y) {
				pt cr = cross(cur, l[f - 1], st, ans);
				f--;
			}
		}
		if (i < n)
			l1 += l[i], l2 -= l[i];
	}
	return 0;
}