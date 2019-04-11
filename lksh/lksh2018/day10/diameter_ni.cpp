#include <iostream>
#include <cassert>
#include <cmath>
#include <string>
#include <cstring>
#include <vector>
#include <fstream>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <set>
#include <map>
#include <iomanip>
#define nextLine() { for (int c = getchar(); c != '\n' && c != EOF; c = getchar()); }
#define sqr(a) ((a)*(a))
#define has(mask,i) (((mask) & (1<<(i))) == 0 ? false : true)
#define eprintf(...) fprintf(stderr, __VA_ARGS__)
#define TASK "diameter"
using namespace std;

#define pii pair<int,int>
#define mp make_pair
#define pb push_back
#define fi first
#define se second

#if ( _WIN32 || __WIN32__ )
    #define LLD "%I64d"
#else
    #define LLD "%lld"
#endif

typedef long long LL;
typedef long double ldb;

const int INF = (1 << 30) - 1;
const ldb EPS = 1e-9;
const ldb PI = fabs(atan2(0.0, -1.0));

class Point
{
public:
	int x, y;

	inline Point() {};

	inline Point(int x, int y)
	{
		this->x = x;
		this->y = y;
	}

	inline void read()
	{
		scanf("%d%d", &x, &y);
	}

	inline LL dist2(const Point &p) const
	{
		return sqr((LL)x - (LL)p.x) + sqr((LL)y - (LL)p.y);
	}

	inline ldb dist(const Point &p) const
	{
		return sqrtl(dist2(p));
	}
};

inline Point operator + (const Point &a, const Point &b)
{
	return Point(a.x + b.x, a.y + b.y);
}

inline Point operator - (const Point &a, const Point &b)
{
	return Point(a.x - b.x, a.y - b.y);
}

inline LL operator * (const Point &a, const Point &b)
{
	return a.x * 1LL * b.x + a.y * 1LL * b.y;
}

inline LL operator ^ (const Point &a, const Point &b)
{
	return a.x * 1LL * b.y - a.y * 1LL * b.x;
}

inline bool operator < (const Point &a, const Point &b)
{
	if (a.y != b.y) return a.y < b.y;
	return a.x < b.x;
}

int n;
vector <Point> pts;

void load()
{
	scanf("%d", &n);
	pts.resize(n);
	for (int i = 0; i < n; i++)
		pts[i].read();
}

inline bool cmp(const Point &a, const Point &b)
{
	LL v = a ^ b;
	if (v == 0)
		return a * a < b * b;
	return v > 0;
}

inline bool bad(const Point &p1, const Point &p2, const Point &p3)
{
	return ((p3 - p2) ^ (p2 - p1)) >= 0;
}

vector <Point> convexHull(const vector <Point> &ipts)
{
	vector <Point> pts(ipts.begin(), ipts.end());
	int bi = 0;
	for (int i = 0; i < (int)pts.size(); i++)
		if (pts[i] < pts[bi]) bi = i;

	swap(pts[0], pts[bi]);
	Point shift = pts[0];
	for (int i = (int)pts.size() - 1; i >= 0; i--)
		pts[i] = pts[i] - pts[0];	

	sort(pts.begin(), pts.end(), cmp);

	vector <Point> hull;

	for (int i = 0; i < 2; i++)
		hull.pb(pts[i]);

	for (int i = 2; i < (int)pts.size(); i++)
	{
		while (hull.size() > 2 && bad(hull[(int)hull.size() - 2], hull.back(), pts[i]))
			hull.pop_back();
		hull.pb(pts[i]);
	}
		
	for (int i = 0; i < (int)hull.size(); i++)
		hull[i] = hull[i] + shift;

	return hull;
}

inline int next(int i, int n)
{
	return (i + 1) % n;
}

void solve()
{
	vector <Point> hull = convexHull(pts);

	LL mdist = 0;
	int j = 0;
	for (int i = 0; i < (int)hull.size(); i++)
	{
		mdist = max(mdist, hull[i].dist2(hull[j]));
		while (hull[i].dist2(hull[j]) <= hull[i].dist2(hull[next(j, hull.size())]))
		{
			j = next(j, hull.size());
			mdist = max(mdist, hull[i].dist2(hull[j]));
		}
	}

	printf("%.12lf", sqrt(mdist));
}

int main()
{
	freopen(TASK".in","r",stdin);
	freopen(TASK".out","w",stdout);
	load();
	solve();
	return 0;
}
