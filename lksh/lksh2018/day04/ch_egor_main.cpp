#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <string>
#include <queue>
#include <stack>
#include <set>
#include <map>
#include <algorithm>
#include <cassert>
#include <iomanip>
//#include <ctime>
//#include <cmath>

#pragma comment(linker, "/STACK:256000000")

using namespace std;

typedef long long int int64;
typedef long double double80;

const int64 INF = (1ll << 63) - 1;

struct edge
{
	int v;
	int64 len;
};

bool operator< (const edge &a, const edge &b)
{
	return (a.len < b.len || (a.len == b.len && a.v < b.v));
}

int n1, m1;
int n2, m2;
int p;
vector<edge> graf1[50005];
vector<edge> graf2[50005];
int64 res[50005];
int prev_of1[50005];
int prev_of2[50005];
int cnt1, cnt2;

set<edge> at_min;

int64 first(vector<edge> graf[], int n)
{
	for (int i = 1; i <= n; ++i)
	{
		res[i] = INF;
	}
	at_min.clear();

	res[1] = 0;
	edge add;
	edge now;
	add.v = 1;
	add.len = 0;
	at_min.insert(add);

	while (!at_min.empty())
	{
		now = *at_min.begin();
		at_min.erase(at_min.begin());

		for (int i = 0; i < graf[now.v].size(); ++i)
		{
			if (res[graf[now.v][i].v] > res[now.v] + graf[now.v][i].len)
			{
				add.v = graf[now.v][i].v;
				add.len = res[graf[now.v][i].v];
				at_min.erase(add);
				res[graf[now.v][i].v] = res[now.v] + graf[now.v][i].len;
				add.v = graf[now.v][i].v;
				add.len = res[graf[now.v][i].v];
				at_min.insert(add);
			}
		}
	}

	return res[n];
}

int dsu_prev(int prev_of[], int v)
{
	if (prev_of[v] == v)
	{
		return v;
	}
	else
	{
		int last = dsu_prev(prev_of, prev_of[v]);
		prev_of[v] = last;
		return last;
	}
}

bool dsu_uni(int prev_of[], int v1, int v2)
{
	v1 = dsu_prev(prev_of, v1);
	v2 = dsu_prev(prev_of, v2);

	if (v1 == v2)
	{
		return false;
	}
	else
	{
		if (rand() & 1)
		{
			swap(v1, v2);
		}
		prev_of[v1] = v2;

		return true;
	}
}

struct go
{
	int v1;
	int v2;
	int64 len;
	int type;
};

bool operator< (const go &a, const go &b)
{
	return (a.len < b.len);
}

int64 second(vector<edge> graf1[], vector<edge> graf2[], int n1, int n2)
{
	int m;
	vector <go> edges;
	go add;
	for (int i = 0; i < n1; ++i)
	{
		for (int j = 0; j < graf1[i].size(); ++j)
		{
			add.v1 = i;
			add.v2 = graf1[i][j].v;
			add.len = graf1[i][j].len;
			add.type = 1;
			edges.push_back(add);
		}
	}

	for (int i = 0; i < n2; ++i)
	{
		for (int j = 0; j < graf2[i].size(); ++j)
		{
			add.v1 = i;
			add.v2 = graf2[i][j].v;
			add.len = graf2[i][j].len;
			add.type = 2;
			edges.push_back(add);
		}
	}

	int64 cost = 0;
	sort(edges.begin(), edges.end());
	
	for (int i = 1; i <= n1; ++i)
	{
		prev_of1[i] = i;
	}
	for (int i = 1; i <= n2; ++i)
	{
		prev_of2[i] = i;
	}
	cnt1 = n1;
	cnt2 = n2;

	int v1, v2;
	int64 len;
	for (int i = 0; i < edges.size(); ++i)
	{
		v1 = edges[i].v1;
		v2 = edges[i].v2;
		len = edges[i].len;
		
		if (edges[i].type == 1)
		{
			if (dsu_uni(prev_of1, v1, v2))
			{
				cost += len*cnt2;
				--cnt1;
			}
		}
		else
		{
			if (dsu_uni(prev_of2, v1, v2))
			{
				cost += len*cnt1;
				--cnt2;
			}
		}
	}

	return cost;
}

int main()
{
	freopen("cartesius.in", "r", stdin);
	freopen("cartesius.out", "w", stdout);

	int v1, v2;
	int64 len;
	edge add;

//	scanf("%d", &p);
	p = 2;
	scanf("%d %d", &n1, &m1);
	for (int i = 0; i < m1; ++i)
	{
		scanf("%d %d %I64d", &v1, &v2, &len);

		add.v = v2;
		add.len = len;
		graf1[v1].push_back(add);

		add.v = v1;
		add.len = len;
		graf1[v2].push_back(add);
	}

	scanf("%d %d", &n2, &m2);
	for (int i = 0; i < m2; ++i)
	{
		scanf("%d %d %I64d", &v1, &v2, &len);

		add.v = v2;
		add.len = len;
		graf2[v1].push_back(add);

		add.v = v1;
		add.len = len;
		graf2[v2].push_back(add);
	}

	if (p == 1)
	{
		printf("%lld", first(graf1, n1) + first(graf2, n2));
	}
	else
	{
		printf("%lld", second(graf1, graf2, n1, n2));
	}

	fclose(stdin);
	fclose(stdout);

	return 0;
}
