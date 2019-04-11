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
string suf[MAXN], take[31], words[MAXN];
int dp[MAXN],    p[MAXN], is[31], a[MAXN];
int n, s;

bool ok(char c) {
	return (c == 'a' || c == 'o' || c == 'e' || c == 'i' || c == 'u' || c == 'y');
}

void restore(int i) {
	vector<string> ans;

	ans.pk(words[i]);
	int ind = s - a[i];
	while (ind) {
		ans.pk(take[p[ind]]);
		ind -= p[ind];
	}
	for (int i = ans.size() - 1; i >= 0; i--)
		cout << ans[i] << " ";
	cout << "\n";
}

int solve() {
	cin >> n >> s;

	memset(p, -1, sizeof(int) * MAXN);
	forn(i, n) {
		string word;
		cin >> word;
		words[i]        = word;

		int c = 0, ind = word.size();
		forn(j, word.size())
			if (ok(word[j]))
				c++, ind = j;

		for (int j = ind; j < word.size(); j++)
			suf[i] += word[j];

		a[i] = c;
		if (!is[c]) {
			is[c] = 1;
			take[c] = word;
		}
	}

	dp[0] = 1;
	forn(i, 31) {
		if (!is[i])
			continue;
		fornn(j, i, s + 1) {
			if (!dp[j] && dp[j - i]) {
				dp[j] =  1;
				p[j] = i;
			}
		}
	}
	map<string, int> ans;

	forn(i, n) {
		if (dp[s - a[i]]) {
			if (ans.count(suf[i])) {
				restore(ans[suf[i]]);
				restore(i);
				exit(0);
			}
			ans[suf[i]] = i;
		}
	}
	cout << "Impossible";
	return 0;
}