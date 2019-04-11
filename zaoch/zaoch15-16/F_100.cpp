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
#include <sstream>
#include <numeric>
#include <unordered_set>

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

#define TASK "king"

const double eps = 1e-7;
const double pi = acos(-1.0);

const ll INF = (ll)2e9 + 1;
const ll LINF = (ll)8e18;
const ll inf = (ll)2e9 + 1;
const ll linf = (ll)2e18;
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

struct cond {
	int a, b, cnt;
	cond() {}
	cond(int _a, int _b, int _cnt) : a(_a), b(_b), cnt(_cnt) {}
};

const int MAXN = 5e5 + 7;
int back[MAXN], forw[MAXN], tmm = 1, p[MAXN], cnt[MAXN], ans[MAXN];
string req[MAXN];
pair<int, int> num[MAXN];
map<pair<int, int>, int> m;

int get(int v) {
	return v == p[v] ? v : get(p[v]);
}

vector<cond> st;

void un(int a, int b) {
	a = get(a), b = get(b);
	if (a != b) {
		if (cnt[a] < cnt[b])
			swap(a, b);

		st.pk(cond(a, b, cnt[a]));
		p[b] = a, cnt[a] += cnt[b];
	}
}

void del() {
	cond cur = st.back();
	st.pop_back();
	int a = cur.a, b = cur.b, c = cur.cnt;
	p[b] = b, cnt[a] = c;
}

int n, k, comp;
int st_v, en_v;

void go(int l, int r) {
	if (l >= r)
		return;
	if (r - l == 1) {
		if (req[l] == "?")
			ans[l] = (get(st_v) == get(en_v));
		return;
	}
	int m = (l + r) / 2, c = 0;

	for (int i = m; i < r; i++)
		if (req[i] == "-" && back[i] < l) {
			if (get(num[i].first) != get(num[i].second))
				un(num[i].first, num[i].second), comp++, c++;
		}

	go(l, m);

	forn(i, c)
		del(), comp--;

	c = 0;

	for (int i = l; i < m; i++)
		if (req[i] == "+" && forw[i] >= r) {
			if (get(num[i].first) != get(num[i].second))
				un(num[i].first, num[i].second), comp++, c++;
		}

	go(m, r);

	forn(i, c)
		del(), comp--;
}

vector<vector<pair<int, int> > > E;

int solve() {
	
	int n, gg, k;
	cin >> n >> gg >> k;
	
	E.resize(k + 1);
	
	int j = 0;
	
	forn(i, gg) {
		int a, b, c;
		cin >> a >> b >> c;
		a--, b--;
		
		E[c].push_back(mp(a, b));
		


		req[j] = "+";
		num[j] = mp(a, b);
		j++;
	}

	cin >> st_v >> en_v;
	st_v--, en_v--;

	fornn(i, 1, k + 1) {
		for (auto c : E[i]) {
			req[j] = "-";
			num[j] = c;
			j++;
		}
		req[j] = "?";
		j++;
		for (auto c : E[i]) {
			req[j] = "+";
			num[j] = c;
			j++;
		}
	}



	forn(i, j + 1)
		forw[i] = INF, back[i] = -1;


	forn(i, j) {
		if (req[i] == "+" || req[i] == "-") {
			if (num[i].first > num[i].second)
				swap(num[i].first, num[i].second);
		}

		if (req[i] == "+")
			m[num[i]] = i;
		if (req[i] == "-") {
			int f = m[num[i]];
			back[i] = f;
			forw[f] = i;
		}
	}

	forn(i, n + 1)
		p[i] = i, cnt[i] = 1;

	go(0, j);	

	vector<int> cur;
	int cc = 0;

	forn(i, j)
		if (req[i] == "?") {
			cc++;
			if (ans[i])
				cur.pk(cc);
		}
	cout << cur.size() << "\n";
	for (int x : cur)
		cout << x << " ";
	return 0;
}