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

int p[207];

int solve() {
	string s;
	vector<vector<string> > lines;

	while (getline(cin, s)) {
		vector<string> words;

		int i = 0;
	
		while (i < s.size()) {
			string cur;
			while (i < s.size() && s[i] == ' ')
				i++;
			while (i < s.size() && s[i] != ' ')
				cur += s[i], i++;
			while (i < s.size() && s[i] == ' ')
				i++;
			words.pk(cur);
		}

		lines.pk(words);
	}

	p[0] = 0;
	fornn(j, 1, 207)
		forn(i, lines.size()) {
			if (j - 1 < lines[i].size())
				p[j] = max(p[j], p[j - 1] + (int)lines[i][j - 1].size() + 1);
		}

	forn(i, lines.size()) {
		int j = 0;
		forn(k, lines[i].size()) {
			cout << lines[i][k];
			j += lines[i][k].size();

			if (k != lines[i].size() - 1)
				while (j < p[k + 1]) {
					cout << " ";
					j++;
				}
		}
		cout << "\n";
	}
	return 0;
}