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

const int MAXN = 2e5 + 7;

int n, st, en;

int used[MAXN], prev[MAXN], dist[MAXN], d[MAXN], pref[MAXN], suff[MAXN];
vector<int> ans;

vector<vector<int> > e;

bool dfs(int v) {
	int cur = -1, rev = -1;
	used[v] = true;

	forn(i, e[v].size()) {
		int to = e[v][i];

		if (to == en) {
			cur = i; 
			forn(j, e[to].size())
				if (e[to][j] == v)
					rev = j;
			break;
		}

		if (!used[to]) 
			if (dfs(to)) {
				cur = i;
				forn(j, e[to].size())
					if (e[to][j] == v)
						rev = j;
				break;
			}
	}

	if (cur != -1) {
		int to = e[v][cur];
		ans.pk(to);

		e[v].erase(e[v].begin() + cur);
		e[to].erase(e[to].begin() + rev);

		return true;
	}
	else
		return false;
}

int max_d(int st) {
	queue<int> q;
	q.push(st);
	dist[st] = 0;

	int maxd = 0;
	while (q.size()) {
		int v = q.front();
		q.pop();
		if (dist[v] > maxd)
			maxd = dist[v];

		forn(i, e[v].size()) {
			int to = e[v][i];
			if (dist[to] > dist[v] + 1) {
				dist[to] = dist[v] + 1;
				q.push(to);
			}
		}
	}
	return maxd;
}

int solve() {
	cin >> n;
	e.resize(n);

	memset(prev, -1, sizeof(int) * n);
	memset(dist, inf, sizeof(int) * n);

	forn(i, n - 1) {
		int a, b;
		cin >> a >> b;

		e[a - 1].pk(b - 1);
		e[b - 1].pk(a - 1);
	}

	cin >> st >> en;
	st--, en--;

	dfs(st);
	ans.pk(st);

	reverse(all(ans));
	forn(i, ans.size()) {
		d[i] = max_d(ans[i]);
	}
	forn(i, ans.size()) {
		pref[i] = d[i] + i + 1;
		if (i > 0)
			pref[i] = max(pref[i], pref[i - 1]);
	}

	for (int i = ans.size() - 1; i >= 0; i--) {
		suff[i] = d[i] + ans.size() - i;
		if (i + 1 < ans.size())
			suff[i] = max(suff[i], suff[i + 1]);
	}

	int res = -inf;
	for (int k = 0; k < ans.size() - 1; k++) {
		res = max(res, min(pref[k], suff[k + 1]));
	}
	cout << res;
	return 0;
}