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

const int MAXN = 1e5 + 7;
vector<vector<int> > e;
int used[MAXN], dist[MAXN], color[MAXN];

bool dfs(int v, int pr = -1) {
	color[v] = 1;
	forn(i, e[v].size()) {
		int to = e[v][i];
		if (color[to] == 1 && to != pr)
			return true;
		if (!color[to] && dfs(to, v))
			return true;
	}
	color[v] = 2;
	return false;
}

ll bfs(int st) {
	used[st] = true;
	dist[st] = 0;
	queue<int> q;
	q.push(st);

	ll ans = 0, c = 1;

	while (q.size()) {
		int v = q.front();
		q.pop();

		used[v] = true;
		ans += (ll)dist[v];

		forn(i, e[v].size()) {
			int to = e[v][i];
			if (dist[to] > dist[v] + 1) {
				dist[to] = dist[v] + 1;
				q.push(to);
				c++;
			}
		}
	}

	if (dfs(st))
		return ans * c;

	ll cur = c * (c - 1) / 2;
	ans = 0;

	int l = c - 1, r = 1;

	forn(i, c) {
		ans += cur;
		cur = cur - l + r;
		l--, r++;
	}

	return ans;
}

int solve() {
	int n, m;
	cin >> n >> m;

	memset(dist, inf, sizeof(int) * n);
	e.resize(n);
	forn(i, m) {
		int a, b;
		cin >> a >> b;
		e[a - 1].pk(b - 1);
		e[b - 1].pk(a - 1);
	}

	ll res = 0;
	forn(i, n) {
		if (!used[i]) {
			res += bfs(i);
		}
	}
	cout << res;
	return 0;
}