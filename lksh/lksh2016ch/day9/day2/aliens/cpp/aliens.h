#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)
#define ll long long

using namespace std;

inline ll sqr(ll x) { return x * x; }

inline bool upd(ll &a, ll b) { if (a > b) { a = b; return true; } return false; }

const int dd = (int)5e4 + 7;
const ll linf = (ll)2e18 + 7;

ll dp1[dd], dp2[dd];

struct line {
	ll k, b;
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
	
	ll get(ll x) {
		//for (auto c : T) err("(k = %I64d, b = %I64d), ", c.k, c.b); err("\n");
		//for (auto t : G) err("%.10f, ", t); err("\n"); 
		j = min(j, (int)G.size());
		while (j + 1 < (int)G.size() && x * 1.0 >= G[j + 1]) {
			j++;
		}
		//err("%I64d %d\n______\n", x, j);
		return T[j].k * x + T[j].b;
	}
} J;

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

	for (int i = 0; i <= n; i++)
		dp1[i] = dp2[i] = linf;
			
	dp1[0] = 0;
	
	ll ans = linf;
	
	//for (int i = 0; i < n; i++)
	//	err("(%d, %d), ", A[i].first, A[i].second);
	
	for (int j = 1; j <= k; j++) {
		J.clear();
		J.add({ -2 * (A[0].first - 1), (dp1[0] + sqr(A[0].first - 1)) }); 
	
		for (int i = 1; i <= n; i++) {
				
			ll p = J.get(A[i - 1].second) + sqr(A[i - 1].second);
			
			upd(dp2[i], p);
			
			if (i == n) 
				continue;
			if (dp1[i] == linf)
				continue;
			ll b = (dp1[i] + sqr(A[i].first - 1)) - sqr(max(0, A[i - 1].second - A[i].first + 1));
			J.add({ -2 * (A[i].first - 1), b });
		}	
		
		copy(dp2, dp2 + n + 1, dp1);
		fill(dp2, dp2 + n + 1, linf);
		
		ans = min(ans, dp1[n]);
	}
	return ans;
}

