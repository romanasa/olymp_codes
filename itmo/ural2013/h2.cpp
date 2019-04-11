#include <stdio.h>
#include <stdarg.h>
#include <cstring>
#include <algorithm>
#include <vector>
#include <cmath>
#include <set>
#define clr(a) memset(a, 0, sizeof(a))

typedef std::pair<int, int> pii;
typedef std::pair<double, int> pdi;
typedef long long ll;
#ifdef ONLINE_JUDGE
	#define LL "%I64d"
#else
	#define LL "%lld"
#endif

void dbg(const char * fmt, ...)
{
	#ifndef ONLINE_JUDGE
		va_list args;
		va_start(args, fmt);
		vfprintf(stdout, fmt, args);
		va_end(args);
		fflush(stdout);
	#endif
}

const int size = 1000;
const double eps = 1e-9;
const double pi = acos(-1.0);

class point
{
public:
	ll x, y;
	int num;
	point(ll x = 0, ll y = 0): x(x), y(y) {}
	void operator += (const point &p)
	{
		x += p.x;
		y += p.y;
	}
	point operator + (const point & p) const
	{
		return point(x + p.x, y + p.y);
	}
	point operator - (const point & p) const
	{
		return point(x - p.x, y - p.y);
	}
	double len()
	{
		return sqrt((double)x * (double)x + (double)y * (double)y);
	}
	void scan(int num)
	{
		this->num = num;
		scanf("%lld%lld", &x, &y);
	}
	void print()
	{
		dbg("%lld %lld\n", x, y);
	}
	bool operator < (const point & p) const
	{
		if (y != p.y)
			return y < p.y;
		return x < p.x;
	}
	bool operator == (const point & p) const
	{
		return x == p.x && y == p.y;
	}
	bool operator != (const point & p) const
	{
		return x != p.x || y != p.y;
	}
	double ang()
	{
		double ans = atan2((double)y,(double)x);
		if (ans < -eps)
			ans += 2*pi;
		return ans;
	}
};

point ar[size];
point pref_sum[size];
double ans[size];
bool used[size][size];

std::set<pdi> swap_times;

pdi make_pair(int pos)
{
	return pdi((ar[pos] - ar[pos-1]).ang(), pos);
}

void insert(int pos)
{
	if (ar[pos-1] == ar[pos])
		return;
	if (used[ar[pos-1].num][ar[pos].num])
		return;
	swap_times.insert(make_pair(pos));
}

void erase(int pos)
{
	if (ar[pos-1] == ar[pos])
		return;
	if (used[ar[pos-1].num][ar[pos].num])
		return;
	swap_times.erase(swap_times.find(make_pair(pos)));
}


int main()
{
#ifndef ONLINE_JUDGE
	//freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);
#endif
	int n;
	scanf("%d", &n);
	int zero_count = n;
	for(int i = 0; i < n; i++)
		ar[i].scan(i);
	n = (int)(std::remove(ar, ar+n, point(0,0)) - ar);
	zero_count -= n;

	std::sort(ar, ar+n);
	point sum(0,0);
	for(int i = 0; i < n; i++)
	{
		pref_sum[i] = sum;
		sum += ar[i];
		ans[i] = sum.len();
		if(i && ar[i] != ar[i-1])
			insert(i);
	}
	while(!swap_times.empty())
	{
		std::set<pdi>::iterator it = swap_times.begin();
		pdi cur = *it;
		swap_times.erase(it);
		int pos = cur.second;
		if (pos - 1 > 0)
			erase(pos-1);
		if (pos + 1 < n)
			erase(pos+1);
		used[ar[pos-1].num][ar[pos].num] = 1;
		std::swap(ar[pos], ar[pos-1]);
		insert(pos);
		if (pos - 1 > 0)
			insert(pos-1);
		if (pos + 1 < n)
			insert(pos+1);
		pref_sum[pos] = pref_sum[pos-1] + ar[pos-1];
		ans[pos-1] = std::max(ans[pos-1], pref_sum[pos].len());
	}

	for(int i = 0; i < zero_count; i++)
	{
		for(int j = n; j > 0; j--)
			ans[j] = std::max(ans[j], ans[j-1]);
		n++;
	}
	for(int i = 0; i < n; i++)
		printf("%.10lf\n", ans[i]);


	return 0;
}
