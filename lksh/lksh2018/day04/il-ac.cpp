#include <iostream>
#include <sstream>
#include <fstream>
#include <ctime>
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <bitset>
#include <queue>
#include <deque>
#include <list>
#include <algorithm>
#include <iomanip>
#include <stack>

using namespace std;

typedef pair<int, int> pt;
typedef long long li;
typedef long double ld;

template<typename X> inline X abs(const X& a) { return a < 0 ? -a: a; }
template<typename X> inline X sqr(const X& a) { return a * a; }

#define forn(i,n) for(int i = 0; i < int(n); i++)
#define pb push_back
#define sz(a) int(a.size())
#define mp make_pair
#define all(a) a.begin(), a.end()
#define ford(i,n) for (int i = int(n) - 1; i >= 0; i--)
#define fore(i,l,r) for (int i = int(l); i <= int(r); i++)
#define ft first
#define sc second
#define x first
#define y second

const int INF = int(1e9);
const li INF64 = li(1e18);
const ld EPS = ld(1e-9);
const ld PI = acos(-1.0);

const int CNT = 62;
const int N = CNT + 13;

vector<int> g[N * N];
int n;
char buf[5];
int degin[N * N];
int degout[N * N];

inline int getId(char c)
{
    if('a' <= c && c <= 'z')
        return c - 'a';
    if('A' <= c && c <= 'Z')
        return c - 'A' + 26;
    return c - '0' + 52;
}

inline char intToChar(int v)
{
    if(v < 26)
        return char('a' + v);
    if(v < 52)
        return char('A' + v - 26);
    return char('0' + v - 52);
}

inline void add(string s)
{
	int v = getId(s[0]) * CNT + getId(s[1]);
	int to = getId(s[1]) * CNT + getId(s[2]);

    g[v].pb(to);

    degout[v]++;
    degin[to]++;
}

inline bool read()
{
	if (scanf("%d", &n) != 1)
		return false;

	forn (i, n)
	{
		assert(scanf("%s", buf) == 1);
		string s = string(buf);

		add(s);
	}

    return true;
}

const int M = 200 * 1000 + 13;
int szs = 0, szt = 0;
int s[M], t[M];
int szp = 0, sztmp = 0;
int path[M], tmp[M];

void findEulerPath (int v)
{
	while (!g[v].empty())
	{
		int to = g[v].back();
		g[v].pop_back();

		findEulerPath(to);
	}

	path[szp++] = v;
}

inline void solve()
{
	szs = 0, szt = 0;
	int v = -1;

	forn (i, CNT * CNT)
	{
		if (degin[i] > 0)
			v = i;

		if (degin[i] == degout[i])
			continue;

		if (abs(degin[i] - degout[i]) > 1)
		{
			puts("NO");
			return;
		}

		if (degin[i] == degout[i] + 1)
			s[szs++] = i;

		if (degin[i] + 1 == degout[i])
			t[szt++] = i;
	}

	assert(v != -1);

	if (szs > 1 || szt > 1)
	{
		puts("NO");
		return;
	}

	if (szs == 1 && szt == 1)
	{
		/*putchar(intToChar(s[0] / CNT));
		putchar(intToChar(s[0] % CNT));
		putchar(' ');

		putchar(intToChar(t[0] / CNT));
		putchar(intToChar(t[0] % CNT));
		putchar(' ');

		puts("");*/

		g[ s[0] ].pb( t[0] );
	}
	else
		assert(szs == 0 && szt == 0);

	szp = 0;
	findEulerPath(v);

	reverse(path, path + szp);

	if (szs == 1)
	{
		forn (i, szp - 1)
		{
			if (path[i] == s[0] && path[i + 1] == t[0])
			{
				sztmp = 0;
				for (int k = i + 1; k < szp; k++)
					tmp[sztmp++] = path[k];

				for (int k = 1; k <= i; k++)
					tmp[sztmp++] = path[k];

				szp = sztmp;
				forn (k, szp)
					path[k] = tmp[k];

				break;
			}
		}
	}

	forn (i, N * N)
		if (!g[i].empty())
		{
			puts("NO");
			return;
		}

	puts("YES");

	for (int i = 0; i < szp; i++)
	{
		if (i == 0)
			putchar(intToChar(path[i] / CNT));
		putchar(intToChar(path[i] % CNT));
		//putchar(' ');
	}
	puts("");
}

int main()
{
#ifdef SU2_PROJ
	assert(freopen("input.txt", "r", stdin));
	assert(freopen("output.txt", "w", stdout));
#endif

	srand(int(time(NULL)));

    cerr << setprecision(10) << fixed;
    cout << setprecision(15) << fixed;

    assert(read());
	solve();

#ifdef SU2_PROJ
    cerr << "TIME: " << clock() << endl;
#endif

    return 0;
}
