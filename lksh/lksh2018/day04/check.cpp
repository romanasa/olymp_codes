#include "testlib.h"

#include <algorithm>
#include <bitset>
#include <cassert>
#include <climits>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <utility>
#include <vector>

#define forn(i, n) for (int i = 0; i < int(n); i++)
#define forl(i, n) for (int i = 1; i <= int(n); i++)
#define ford(i, n) for (int i = int(n) - 1; i >= 0; i--)
#define fore(i, l, r) for (int i = int(l); i <= int(r); i++)
#define correct(x, y, n, m) (0 <= (x) && (x) < (n) && 0 <= (y) && (y) < (m))
#define all(a) (a).begin(), (a).end()
#define sz(a) int((a).size())
#define pb(a) push_back(a)
#define mp(x, y) make_pair((x), (y))
#define ft first
#define sc second
#define x first
#define y second

using namespace std;

typedef long long li;
typedef long double ld;
typedef pair<int, int> pt;

template<typename X> inline X abs(const X& a) { return a < 0? -a: a; }
template<typename X> inline X sqr(const X& a) { return a * a; }
inline ostream& operator<< (ostream& out, const pt& p) { return out << '(' << p.x << ", " << p.y << ')'; }

using namespace std;

int n;
vector<string> s;
string result;

bool readAnswer(InStream& in)
{
	string yesno = in.readToken("YES|NO");
	
	if (yesno == "NO")
		return false;
		
	string p = in.readToken();
	if (int(p.length()) != n + 2)
		in.quitf(_wa, "Printed password '%s' has invalid length %d, but expected %d", compress(p).c_str(), p.length(), n + 2);
			
	vector<string> subs;
	forn(i, p.length() - 2)
		subs.push_back(p.substr(i, 3));	
	sort(subs.begin(), subs.end());

	if (subs != s)
		in.quitf(_wa, "Printed password '%s' doesn't correspond to the input", compress(p).c_str());
		
	result = p;	
	return true;	
}

int main(int argc, char * argv[])
{
    registerTestlibCmd(argc, argv);
    
    n = inf.readInt();
    s.resize(n);
    forn(i, n)
    	s[i] = inf.readToken();
    sort(s.begin(), s.end());	
    	
    bool ja = readAnswer(ans);
    bool pa = readAnswer(ouf);	
    
    if (ja == pa)
    {
		if (pa)
			quitf(_ok, "YES: %s", compress(result).c_str());
		else
			quitf(_ok, "NO");
    }
    else
    {
    	if (ja)
    		quitf(_wa, "Jury has answer, but participant hasn't");
   		else
    		quitf(_fail, "Participant has answer '%s', but jury hasn't", compress(result).c_str());
    }
}
