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
#include <unordered_map>
#include <cassert>

using namespace std;

int solve();

#define forn(i, n) for (int i = 0; i < (n); ++i)
#define fornn(i, q, n) for (int i = q; i < (n); ++i)
#define all(v) v.begin(), v.end()
#define mp make_pair

typedef long long ll;
typedef long double ld;

#define TASK "mountain"

int main() {
#ifdef KAZAN
	freopen("input.txt", "r", stdin), freopen("output.txt", "w", stdout);
#else
	freopen(TASK".in", "r", stdin), freopen(TASK".out", "w", stdout);
#endif
	solve();
}

struct pt {
	ll x, y;
	pt() {}
	pt(ll x, ll y) : x(x), y(y) {}
};

struct vt {
	ll x, y;
	vt() {}
	vt(pt a, pt b) {
		x = b.x - a.x;
		y = b.y - a.y;
	}
	ll operator % (vt b) {
		return x * b.y - y * b.x;
	}
};

int solve() {
	int n, q;
	scanf("%d %d", &n, &q);

	vector<pt> P(n + 1);
	P[0] = pt(0, 0);

	vector<ll> d(n), k(n);

	forn(i, n) {
		scanf("%lld %lld", &d[i], &k[i]);
		ll x = P[i].x + d[i];
		ll y = P[i].y + k[i] * d[i];
		P[i + 1] = pt(x, y);
	}

	if (n <= 3000 && q <= 3000) {
		while (q--) {
			int x, y;
			scanf("%d %d", &x, &y);

			int l = -1, r = -1;
			for (int i = 0; i < n; i++) {
				if (P[i].x <= x && x <= P[i + 1].x) {
					l = i, r = i + 1;
					break;
				}
			}
			pt A(x, y);

			while (l - 1 >= 0 && (vt(A, P[l]) % vt(A, P[l - 1]) <= 0))
				l--;

			while (r + 1 <= n && (vt(A, P[r]) % vt(A, P[r + 1]) >= 0))
				r++;

			printf("%lld %lld\n", P[l].x, P[r].x);
		}
	}
	else {

		vector<pair<pair<int, int>, int> > A(q);
		vector<pair<int, int> > ans(q);

		bool ok = true;

		forn(i, q) {
			cin >> A[i].first.first >> A[i].first.second;
			A[i].second = i;

			if (i && A[i].first.first != A[i - 1].first.first)
				ok = false;
		}

		if (ok) {
			sort(all(A));

			int l = -1, r = -1;

			forn(gg, q) {
				int x = A[gg].first.first;
				int y = A[gg].first.second;

				if (l == -1) {
					for (int i = 0; i < n; i++) {
						if (P[i].x <= x && x <= P[i + 1].x) {
							l = i, r = i + 1;
							break;
						}
					}
				}

				pt M(x, y);

				while (l - 1 >= 0 && (vt(M, P[l]) % vt(M, P[l - 1]) <= 0))
					l--;

				while (r + 1 <= n && (vt(M, P[r]) % vt(M, P[r + 1]) >= 0))
					r++;

				ans[A[gg].second] = mp(P[l].x, P[r].x);
			}
			for (auto c : ans) {
				printf("%d %d\n", c.first, c.second);
			}
		}
		else {
			auto OP = P;

			forn(i, n + 1) {
				ll x = P[i].x;
				ll y = P[i].y;

				P[i].x = x + y;
				P[i].y = y - x;
			}

			vector < pair<pair<ll, ll>, ll> > H, J;

			forn(gg, q) {
				ll x = A[gg].first.first + A[gg].first.second;
				ll y = A[gg].first.second - A[gg].first.first;

				H.push_back(mp(mp(x, y), gg));
				J.push_back(mp(mp(y, x), gg));
			}

			sort(all(H));
			sort(all(J));

			int jH = 0, jJ = 0;

			forn(i, n) {
				if (P[i].x == P[i + 1].x) {
					while (jH < H.size() && H[jH].first.first < P[i].x) {
						ans[H[jH].second].second = OP[i].x;
						jH++;
					}
				}
			}

			while (jH < H.size()) {
				ans[H[jH].second].second = OP.back().x;
				jH++;
			}

			for (int i = n - 1; i >= 0; i--) {
				if (P[i].y == P[i + 1].y) {
					while (jJ < J.size() && J[jJ].first.first < P[i].y) {
						ans[J[jJ].second].first = OP[i + 1].x;
						jJ++;
					}
				}
			}


			while (jJ < J.size() ) {
				ans[J[jJ].second].first = 0;
				jJ++;
			}

			for (auto c : ans) {
				printf("%d %d\n", c.first, c.second);
			}
		}
	}
	return 0;
}