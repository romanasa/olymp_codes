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
#include <iosfwd>

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

int solve() {
	string tmm, line;
	cin >> tmm;
	getchar();

	while (getline(cin, line)) {
		istringstream cin1 (line);

		string ip, ans, name, date;

		cin1 >> ip;

		ans += ip;
		ans += " - ";

		cin1 >> name;
		ans += name;
		
		cin1 >> date;

		int i = 0;
		string num, mon, year, hour, min, sec;
		while (date[i] != '/')
			num += date[i], i++;
		i++;

		while (date[i] != '/')
			mon += date[i], i++;
		i++;

		while (date[i] != ':')
			year += date[i], i++;
		i++;

		while (date[i] != ':')
			hour += date[i], i++;
		i++;

		while (date[i] != ':')
			min += date[i], i++;
		i++;

		while (i < date.size()) 
			sec += date[i], i++;

		cout << "g";
	}
	return 0;
}