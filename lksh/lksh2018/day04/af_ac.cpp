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

#define forn(i, n) for (int i = 0; i < int(n); i++)
#define pb push_back
#define sz(a) int(a.size())
#define mp make_pair
#define all(a) a.begin(), a.end()
#define ford(i, n) for (int i = int(n) - 1; i >= 0; i--)
#define fore(i, l, r) for (int i = int(l); i <= int(r); i++) 
#define ft first
#define sc second
#define x first
#define y second

const int INF = int(1e9);
const li INF64 = li(1e18);
const ld EPS = ld(1e-9);
const ld PI = acos(-1.0);
const int N = 63;
const int CNT = 62;

vector<int>g[N * N];
int n;
char buf[5];
int last[N * N];
int degin[N * N];
int degout[N * N];
int szans;
int szres;
const int M = 200 * 1000 + 13;
int res[M];

int getId(char c)
{
    if ('a' <= c && c <= 'z')
        return c - 'a';
    if ('A' <= c && c <= 'Z')
        return c - 'A' + 26;
    return c - '0' + 52;
}

char intToChar(int v)
{
    if (v < 26)
        return char('a' + v);
    if (v < 52)
        return char('A' + v - 26);
    return char('0' + v - 52);
}

void add(string s)
{
	int v = getId(s[0]) * CNT + getId(s[1]);
	int to = getId(s[1]) * CNT + getId(s[2]);
    g[v].pb(to);
    degout[v]++;
    degin[to]++;
}

inline bool read()
{
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
	{
		scanf("%s", buf);
		string s = string(buf);
		add(s);
}
    return true;
}                                  

inline void solve()
{
    int v = 0;
    while (!degout[v]) v++;
	int v1 = -1;
	int v2 = -1;
	for (int i = 0; i < N * N; i++)
    {
        if (degin[i] == degout[i])
            continue;
		if (degin[i] == degout[i] + 1)
        {   
            if (v2 != -1)
            {
                puts("NO");
                return;
            }
			v2 = i; continue;

        }		
		if (degin[i] + 1 == degout[i])
        {
            if (v1 != -1)
            {   
            	puts("NO");
            	return;
            }
			v1 = i; continue;
        }
        puts("NO");
        return;
    }
    if (v1 != -1)
        g[v2].pb(v1);        
   	stack<int> st;
	st.push(v);
	while (!st.empty())
	{
		int v = st.top();
		int to = -1;
        if (last[v] != sz(g[v]))
        {
            to = g[v][last[v]];
            last[v]++;
        }
        if (to == -1)
		{
			res[szres++] = v;
			st.pop();
		}
		else
			st.push(to);
	}
    reverse(res, res + szres);
    int pos = 0;
    if (v1 != -1)
    {
        for (int i = 0; i + 1 < szres; i++)
            if (res[i] == v2 && res[i + 1] == v1)
            {
                pos = i + 1;
                break;
            }
    }
    string ans = "";
    for (int i = pos; i < szres; i++)
    {
        if (i == pos)
            ans.pb(intToChar(res[i] / CNT));
        ans.pb(intToChar(res[i] % CNT));
    }    
    for (int i = 1; i < pos; i++)
        ans.pb(intToChar(res[i] % CNT));
    if (sz(ans) != n + 2)
    {
        puts("NO");
        return;
    }
    puts("YES");
    puts(ans.c_str());
    return;
}

int main()
{
    cerr << setprecision(10) << fixed;
    cout << setprecision(15) << fixed;
    
    srand(time(NULL));
    assert(read());
	solve();
	       
#ifdef fcspartakm
    cerr << "TIME: " << clock() << endl;
#endif      
    
    return 0;
}
