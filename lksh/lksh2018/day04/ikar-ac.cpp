#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cassert>
#include <ctime>
#include <cstring>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <queue>
#include <deque>
#include <list>
#include <stack>
#include <bitset>
#include <algorithm>
#include <iomanip>

using namespace std;

#define forn(i, n) for (int i = 0; i < int(n); i++)
#define ford(i, n) for (int i = int(n) - 1; i >= 0; i--)
#define fore(i, l, r) for (int i = int(l); i <= int(r); i++)
#define all(a) a.begin(), a.end()
#define sz(a) int(a.size())
#define mp make_pair
#define pb push_back
#define ft first
#define sc second
#define x first
#define y second

template<typename X> inline X abs(const X& a) { return a < 0 ? -a : a; }
template<typename X> inline X sqr(const X& a) { return a * a; }

typedef long long li;
typedef long double ld;
typedef pair<int, int> pt;

const int INF = int(1e9);
const li INF64 = li(1e18);
const ld EPS = 1e-9;
const ld PI = acosl(ld(-1));

const int N = 200 * 1000 + 13;
const int M = 62 * 62 + 13;

int n;
string s[N];
char buf[5];
vector< pair<int, char> > g[M];
int idx[M];

inline bool read() {
	if (scanf("%d", &n) != 1)
		return false;
	forn(i, n) {
		assert(scanf("%s", buf) == 1);
		s[i] = string(buf);
	}
	return true;
}

string alph = "";
int pos[M];

int get(int a, int b) {
	return pos[a] * sz(alph) + pos[b];
}

string get(int idx) {
	string res = "";
	res += alph[idx / sz(alph)];
	res += alph[idx % sz(alph)];
	return res;
}

int deg[M];
string ans = "";

void dfs(int v, char c = -1) {
	for(; idx[v] < sz(g[v]);) {
		int to = g[v][idx[v]].ft;
		char c = g[v][idx[v]].sc;
		idx[v]++;
		dfs(to, c);
	}
	if (c != -1)
		ans += c;
}


inline void solve() {
	fore(c, 'a', 'z')
		alph += char(c);
	fore(c, 'A', 'Z')
		alph += char(c);
	fore(c, '0', '9')
		alph += char(c);
	forn(i, sz(alph)) {
		pos[int(alph[i])] = i;
	}
	forn(i, n) {
		int from = get(s[i][0], s[i][1]);
		int to = get(s[i][1], s[i][2]);
		g[from].pb(mp(to, s[i][2]));
		deg[from]++;
		deg[to]--;
	}
	bool ok = true;
	int idxm = -1;
	int idxp = -1;
	forn(i, M) {
		if (deg[i] == 0)
			continue;
		if (deg[i] == -1) {
			if (idxm != -1)
				ok = false;
			idxm = i;
		} else if (deg[i] == 1) {
			if (idxp != -1)
				ok = false;
			idxp = i;
		} else {
			ok = false;
		}
	}
	if (!ok) {
		puts("NO");
		return;
	}
	if (idxm == -1 && idxp == -1) {
		idxm = idxp = get(s[0][0], s[0][1]);
	}
	if (idxm == -1 || idxp == -1) {
		puts("NO");
		return;
	}
	dfs(idxp);
	forn(i, M) {
		if (sz(g[i]) != idx[i]) {
			puts("NO");
			return;
		}
	}

	puts("YES");
	reverse(all(ans));
	ans = get(idxp) + ans;
	puts(ans.c_str());
}

int main()
{
#ifdef SU2_PROJ
	assert(freopen("input.txt", "r", stdin));
	assert(freopen("output.txt", "w", stdout));
#endif

	cout << setprecision(25) << fixed;
	cerr << setprecision(10) << fixed;

	srand(int(time(NULL)));

	assert(read());
	solve();

#ifdef SU2_PROJ
	cerr << "TIME: " << clock() << endl;
#endif

	return 0;
}
