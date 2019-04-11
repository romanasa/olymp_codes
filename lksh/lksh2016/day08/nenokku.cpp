#define _CRT_SECURE_NO_WARNINGS
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

using namespace std;

typedef unsigned long long ull;
typedef long long ll;
typedef long double ld;

#define forn(i, n) for (int i = 0; i < (int)(n); i++)
#define fornn(i, q, n) for (ll i = q; i < (ll)n; i++)
#define mp make_pair
#define all(v) v.begin(), v.end()
#define times clock() * 1.0 / CLOCKS_PER_SEC

#define TASK "nenokku"

const double eps = 1e-7;
const double pi = acos(-1.0);

const ll inf = (ll)2e9 + 1;
const ll linf = (ll)8e18;

int solve();
void gen();

int main()
{
#ifdef HOME
	freopen("input.txt", "r", stdin), freopen("output.txt", "w", stdout);
#else
	freopen(TASK".in", "r", stdin), freopen(TASK".out", "w", stdout);
	//freopen("input.txt", "r", stdin), freopen("output.txt", "w", stdout), freopen("test.txt", "w", stderr);
#endif
	solve();
	return 0;
}

const int dd = 2e5 + 7;

string s;
map<char, int> go[dd];
int l[dd], r[dd], p[dd], suf[dd];
int nv = 2;
vector<string> e[dd];

void ask(string t, int N) {
	int v = 1, ind = 0, pos = 0;

	while (ind < t.size()) {
		if (!go[v].count(t[ind])) {
			puts("NO");
			return;
		}
		v = go[v][t[ind]];
		pos = l[v];
		while (ind < t.size() && pos < min(r[v], N)) {
			if (s[pos] != t[ind]) {
				puts("NO");
				return;
			}
			pos++, ind++;
		}
	}
	puts("YES");
}

void dfs(int v, int ind, int pos) {
	reverse(all(e[ind]));
	while (e[ind].size()) {
		ask(e[ind].back(), ind);
		e[ind].pop_back();
	}

	if (ind >= s.size())
		return;
	char c = s[ind];

	if (pos >= r[v]) {
		if (!go[v].count(c)) {

			int x = nv++;
			p[x] = v;
			l[x] = ind, r[x] = dd, go[v][c] = x;

			dfs(suf[v], ind, r[v]);
			return;
		}
		dfs(go[v][c], ind + 1, l[go[v][c]] + 1);
	} else if (c == s[pos]) {
		dfs(v, ind + 1, pos + 1);
	} else {
		int x = nv++;

		l[x] = l[v], r[x] = pos, p[x] = p[v];
		l[v] = pos, p[v] = x;

		go[p[x]][s[l[x]]] = x;
		go[x][s[pos]] = v;

		int y = nv++;

		p[y] = x, l[y] = ind, r[y] = dd;
		go[x][c] = y;

		v = suf[p[x]];
		pos = l[x];

		while (pos < r[x]) {
			v = go[v][s[pos]];
			pos += r[v] - l[v];
		}

		suf[x] = (pos == r[x] ? v : nv);

		dfs(v, ind, r[v] - (pos - r[x]));
	}
}

bool ok(char c) {
	return (c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z');
}

int solve() {
	l[1] = -1;
	forn(i, 127)
		go[0][i] = 1;

	char t = getchar();

	while (t == 'A' || t == '?') {
		char c = getchar();

		if (t == 'A') {
			char c = getchar();
			while (ok(c))
				s += tolower(c), c = getchar();
		} else {
			char c = getchar();

			string a;

			while (ok(c))
				a += tolower(c), c = getchar();

			e[s.size()].push_back(a);
		}
		t = getchar();
	}

	dfs(1, 0, 0);

	return 0;
}