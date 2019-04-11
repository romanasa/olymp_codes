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
typedef double ld;

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
	//gen();
    solve();
    return 0;
}

struct pt {
	ll x, y;
	bool operator < (pt b) const {
		if (y == b.y)
			return x < b.x;
		return y < b.y;
	}
};

struct vt {
	ll x, y;
	vt(pt a, pt b) {
		x = b.x - a.x;
		y = b.y - a.y;
	}
	vt(pt a) {
		x = a.x, y = a.y;
	}
	friend ll operator %(vt a, vt b) {
		return a.x * b.y - a.y * b.x;
	}
};
        
pt st;

bool cmp(pt a, pt b) {
	return vt(st, a) % vt(st, b) > 0;
}

bool check(vector<pt> &p) {
	if (p.size() < 3)
		return false;
	sort(all(p));
	st = p[0];
	sort(p.begin() + 1, p.end(), cmp);

	int n = p.size();
	forn(i, n) {
		if (vt(p[(i + n - 1) % n], p[i]) % vt(p[i], p[(i + 1) % n]) < 0)
			return false;
	}
	return true;
}

double sq(vector<pt> &p) {
	double ans = 0;
	int n = p.size();
	forn(i, n) {
		ans += vt(p[i]) % vt(p[(i + 1) % n]);
	}
	ans /= 2.0;
	return abs(ans);
}

void gen() {
	srand(time(0));
	ofstream cout("input.txt");
	int n = rand() % 7;
	cout << n << "\n";
	forn(i, n)
		cout << rand() % 5 << " " << rand() % 5 << "\n";
}

int solve() {
	int n;
	cin >> n;
	vector<pt> p(n);
	forn(i, n) {
		cin >> p[i].x >> p[i].y;
	}

	double ans = linf;
	forn(i, n)
		forn(j, n) 
			if (i != j) {
				ll a = p[j].y - p[i].y, b = p[i].x - p[j].x,
					c = -(a * p[i].x + b * p[i].y);
				vector<pt> ans1, ans2;
				forn(k, n) {
					if (a * p[k].x + b * p[k].y + c <= 0)
						ans1.pk(p[k]);
					else
						ans2.pk(p[k]);
				}
				if (check(ans1) && check(ans2)) {
					ans = min(ans, abs(sq(ans1) - sq(ans2)));
				}
				ans1.clear();
				ans2.clear();

				forn(k, n) {
					if (a * p[k].x + b * p[k].y + c < 0)
						ans1.pk(p[k]);
					else
						ans2.pk(p[k]);
				}
				if (check(ans1) && check(ans2)) {
					ans = min(ans, abs(sq(ans1) - sq(ans2)));
				}
			}
	//check(p);
	//cout << sq(p) << "\n";
	if (ans == linf)
		cout << -1;
	else
		printf("%.10f", ans);
	
	return 0;
}