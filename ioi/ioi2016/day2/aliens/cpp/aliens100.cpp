#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)
#define ll long long

using namespace std;

inline ll sqr(ll x) { return x * x; }

inline bool upd(ll &a, ll b) { if (a > b) { a = b; return true; } return false; }

const int dd = (int)5e4 + 7;
const ll linf = (ll)2e18 + 7;

ll dp[dd], cnt[dd];

struct line {
	ll k, b;
	int ind;
};

struct hull {
	vector<line> T;
	vector<double> G;

	int j = 0;

	void clear() {
		T.clear();
		G.clear();
		j = 0;
	}

	void add(line Q) {

		while (1) {
			if (!T.size()) {
				T.push_back(Q);
				G.push_back(-linf);
				break;
			}

			if (T.back().k == Q.k) {
				if (T.back().b < Q.b) {
					break;
				} else {
					T.pop_back();
					G.pop_back();
				}
			} else {

				double x = (Q.b - T.back().b) * 1.0 / (T.back().k - Q.k);

				if (x < G.back()) {
					T.pop_back();
					G.pop_back();
				} else {
					T.push_back(Q);
					G.push_back(x);
					break;
				}
			}
		}
	}

	int get(ll x) {
		//for (auto c : T) err("(k = %I64d, b = %I64d), ", c.k, c.b); err("\n");
		//for (auto t : G) err("%.10f, ", t); err("\n");
		j = min(j, (int)G.size());
		while (j + 1 < (int)G.size() && x * 1.0 >= G[j + 1]) {
			j++;
		}
		return T[j].ind;
	}
} J;


pair<int, int> get(vector<pair<int, int> > &A, ll C) {
	dp[0] = 0;

    J.clear();
    J.add({ -2 * (A[0].first - 1), (dp[0] + sqr(A[0].first - 1)), 0 });

    for (int i = 1; i <= n; i++) {
        int j = J.getI(A[i - 1].second);

        dp[i] = dp[j] + sqr(A[i].second - A[j].first + 1) + C;
        if (j)
            dp[i] -= sqr(max(0, A[j - 1].second - A[j].first + 1));
        cnt[i] = cnt[j] + 1;

        if (i == n)
            continue;

        ll b = (dp[i] + sqr(A[i].first - 1)) - sqr(max(0, A[i - 1].second - A[i].first + 1));
        J.add({ -2 * (A[i].first - 1), b, i });
    }
    return { dp[n], cnt[n] };
}

ll take_photos(int n, int m, int k, vector<int> r, vector<int> c) {
	vector<pair<int, int> > A;

	for (int i = 0; i < n; i++) {
		A.push_back({ min(r[i], c[i]), max(r[i], c[i]) });
	}

	sort(A.begin(), A.end(), [](pair<int, int> a, pair<int, int> b) { return a.first == b.first ? a.second > b.second : a.first < b.first; });

	vector<pair<int, int> > st;

	for (auto c : A) {
		if (st.size() && st.back().first <= c.first && st.back().second >= c.second) continue;
		st.push_back(c);
	}

	A = st;

	n = (int)A.size();

    ll l = -1, r = m * m + 2;

    while (r - l > 1) {
        ll mid = (l + r) / 2;

        auto c = get(A, mid);

        if (c.second < k)
            r = mid;
        else
            l = mid;
    }

    auto c1 = get(A, l);
    auto c2 = get(A, r);

    if (c1.second == k) {
        return c1.first - l * k;
    }

    if (c2.second == k) {
        return c2.first - r * k;
    }

    ll diff = c1.first - c2.first;

    return c1.first + diff / (c1.second - c2.second) * (k - c1.second);

	//for (int i = 0; i < n; i++)
	//	err("(%d, %d), ", A[i].first, A[i].second);
}

