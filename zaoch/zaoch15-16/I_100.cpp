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

string s;

vector<int> suf;
vector<int> c;

void build() {
	int n = s.size();
	int L = 1;

	vector<int> a(n), na(n), head(n), nc(n);
	c.resize(n);

	vector<pair<int, int> > cur;

	forn(i, n)
		cur.pk(mp(s[i], i));

	sort(all(cur));

	forn(i, n)
		a[i] = cur[i].second;

	int cc = -1;
	forn(i, n) {
		if (!i || s[a[i]] != s[a[i - 1]])
			cc++, head[cc] = i;
		c[a[i]] = cc;
	}

	while (L < n) {

		forn(i, n) {
			int j = (a[i] - L + n) % n;
			na[head[c[j]]++] = j;
		}

		int cc = -1;
		forn(i, n) {
			if (!i || c[na[i]] != c[na[i - 1]] || c[(na[i] + L) % n] != c[(na[i - 1] + L) % n])
				cc++, head[cc] = i;
			nc[na[i]] = cc;
		}


		forn(i, n)
			c[i] = nc[i], a[i] = na[i];
		L *= 2;
	}

	suf = a;
}

const int dd = 1e5 + 7;

int L[dd], R[dd], minl[dd];
string G[dd];

int solve() {
	int n;
	cin >> n;

	forn(i, n)
		minl[i] = inf;

	int cnt = 0;
	forn(i, n) {
		cin >> G[i];
		L[i] = cnt;
		R[i] = (cnt += G[i].size()) - 1;
		forn(j, G[i].size())
			s.pk(G[i][j]);
		s.pk('#');
		cnt++;
	}

	build();


	int kk = suf.size();

	vector<int> lcp(kk), b(kk), ind(kk);
	
	forn(i, kk)
		b[suf[i]] = i;

	int z = 0;
	forn(j, kk) {
		int i = b[j];
		if (i == kk - 1)
			continue;

		int t = suf[i + 1];

		while (z < kk && s[(j + z) % kk] == s[(t + z) % kk] && s[(j + z) % kk] >= 'a' && s[(j + z) % kk] <= 'z')
			z++;

		lcp[i] = z;
		if (z > 0)
			z--;
	}

	reverse(all(suf));
	reverse(all(lcp));
	while (suf.size() && s[suf.back()] == '#')
		suf.pop_back(), lcp.pop_back();
	reverse(all(suf));
	reverse(all(lcp));
	
	kk = suf.size();

	forn(i, kk) {
		ind[i] = lower_bound(R, R + n, suf[i]) - R;
	}

	vector<int> LM(kk), RM(kk);

	fornn(i, 1, kk) {
		if (ind[i] != ind[i - 1]) 
			LM[i] = lcp[i - 1];
		else 
			LM[i] = min(lcp[i - 1], LM[i - 1]);
	}

	for (int i = kk - 2; i >= 0; i--) {
		if (ind[i] != ind[i + 1]) 
			RM[i] = lcp[i];
		else 
			RM[i] = min(lcp[i], RM[i + 1]);
	}

	vector<int> len(kk);
	L[n] = s.size();
	
	forn(i, kk) {
		int pos = suf[i];
		int rpos = (*upper_bound(L, L + n + 1, pos)) - 1;
		len[i] = rpos - pos;
	}

	forn(i, kk) {
		int cur = max(RM[i], LM[i]) + 1;
		if (cur <= len[i])
			minl[ind[i]] = min(minl[ind[i]], cur);
	}
	
	vector<string> ans(n, "?");

	forn(i, kk) {
		int cur = max(RM[i], LM[i]) + 1;
		if (cur <= len[i] && cur == minl[ind[i]]) {
			string c;
			for (int j = suf[i]; j < suf[i] + cur; j++)
				c.pk(s[j]);
			ans[ind[i]] = c;
			minl[ind[i]] = -1;
		}
	}

	forn(i, n)
		cout << ans[i] << "\n";
	return 0;
}
