#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <vector>
#include <string>
#include <set>
#include <map>
#include <bitset>


using namespace std;

int solve();

#define forn(i, n) for (int i = 0; i < (n); ++i)
#define fornn(i, q, n) for (int i = q; i < (n); ++i)
#define all(v) v.begin(), v.end()
#define mp make_pair

typedef long long ll;

#define TASK "castle"

int main() {
#ifdef KAZAN
	freopen("input.txt", "r", stdin), freopen("output.txt", "w", stdout);
#else
	freopen(TASK".in", "r", stdin), freopen(TASK".out", "w", stdout);
#endif
	solve();
}

int solve() {
	int n, s;
	scanf("%d %d", &n, &s);

	multiset<pair<int, int> > S;

	ll ans = 0;

	forn(i, n) {
		int a, k;
		scanf("%d %d", &a, &k);
		S.insert(mp(-k, a));

		ans += a;
	}

	while (s) {
		if (S.size() == 0)
			break;

		ll a, k;
		k = -S.begin()->first;
		a = S.begin()->second;

		S.erase(S.begin());

		if (a >= k) {

			int t = a / k;

			int x = min(s, t);

			s -= x;
			a -= 1ll * x * k;
			ans -= 1ll * x * k;

			if (a > 0)
				S.insert(mp(-k, a));
		}
		else {
			S.insert(mp(-a, a));
		}
	}

	cout << ans;

	return 0;
}