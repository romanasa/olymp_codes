#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

#define TASK "player"

struct segment {
	ll l, r, f, len, sf;
	int ind;
	segment() {}
	segment(ll _l, ll _r, ll _f, int id): l(_l), r(_r), f(_f), ind(id) {
		len = r - l;
		sf = f * (r - l);
	}
	bool operator < (segment b) const {
		return f == b.f ? l < b.l : f > b.f;
	}
};

set<segment> S;

int main() {
#ifndef HOME
	freopen(TASK".in", "r", stdin), freopen(TASK".out", "w", stdout);
#endif
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int n, v, F;
	cin >> n >> v >> F;
	
	vector<segment> A;
	
	int cc = 0;
	ll T = 0;
	for (int i = 0; i < n; i++) {
		int t, k;
		cin >> t >> k;
		vector<segment> cur;
		for (int j = 0; j < k; j++) {
			int l, r, f;
			cin >> l >> r >> f;
			cur.push_back(segment(l + T, r + T, f, cc++));
		}
		if (cur.empty()) A.push_back(segment(T, t + T, 0, cc++));
		else {
			if (cur.back().r < t + T) cur.push_back(segment(cur.back().r, t + T, 0, cc++));
			if (cur[0].l > T) cur.insert(cur.begin(), segment(T, cur[0].l, 0, cc++));
			for (int j = 0; j < (int)cur.size(); j++) {
				A.push_back(cur[j]);
				if (j + 1 < (int)cur.size() && cur[j].r < cur[j + 1].l) A.push_back(segment(cur[j].r, cur[j + 1].l, 0, cc++));
			}
		}
		T += t;
	}
	/*
	for (auto c : A) {
		err("l = %I64d, r = %I64d, f = %I64d, ind = %d\n", c.l, c.r, c.f, c.ind);
	}
	*/
	double len = 0;
	ll sf = 0;
	double ans = 1e18;
	
	for (int i = 0; i < cc; i++) {
		len += A[i].len;
		sf += A[i].sf;
		S.insert(A[i]);

    	if (sf >= F) {
    		double cur = len - A[i].len;
    		cur += max(0ll, F - (sf - A[i].sf)) * 1.0 / A[i].f;		
    		ans = min(ans, cur);
    	}	
				
		int ok = 1;
		while (S.size()) {
			auto it = --S.end();
			if (sf - it->sf < F) break;
		
			len -= it->len;
			len += it->len * 1.0 / v;
			sf -= it->sf;
			
			ok &= (it->ind != A[i].ind);
			S.erase(it);
			
    		if (sf >= F && ok) {
    			double cur = len - A[i].len;
    			cur += max(0ll, F - (sf - A[i].sf)) * 1.0 / A[i].f;		
    			ans = min(ans, cur);
    		}	
		}
	}
	
	if (ans > 1e17) printf("-1\n");
	else printf("%.10f\n", ans);
	return 0;
}