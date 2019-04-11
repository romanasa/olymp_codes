#include "grader.h"
#include <bits/stdc++.h>
#define ll long long
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

ll get(multiset<int> &S, int k) {
	ll sum = 0;
	int cnt = 0;
	for (auto it = S.rbegin(); it != S.rend(); ++it) {
		sum += *it;
		if (++cnt == k) break;
	}
	return sum;
}

ll findMaxAttraction(int n, int start, int d, int attraction[]) {
	ll ans = 0;
	for (int l = 0; l <= start; l++) {
		multiset<int> S;
		for (int i = l; i < start; i++) S.insert(attraction[i]);
		for (int r = start; r < n; r++) {
			S.insert(attraction[r]);
			
			int t1 = d - (r - start) - (r - l);
			if (t1 > 0) ans = max(ans, get(S, t1));
			int t2 = d - (start - l) - (r - l);
			if (t2 > 0) ans = max(ans, get(S, t2));
			//err("l = %d, r = %d, t1 = %d, t2 = %d\n", l, r, t1, t2);
		}
	}
	
	for (int l = 0; l <= start; l++) {
		multiset<pair<int, int> > S;
		multiset<int> T;
		for (int i = l; i < start; i++) S.insert({ attraction[i], i }), T.insert(attraction[i]);
		for (int r = start; r < n; r++) {
			S.insert({ attraction[r], r }), T.insert(attraction[r]);
			
			int t1 = d - (r - start) - (r - l);
			if (t1 > 0 && ans == get(T, t1)) {
				auto it = S.rbegin();
				
				for (int i = 0; i < t1; i++) {
					err("(%d, %d)\n", it->first, it->second);	
					++it;
				}
				
				err("R: l = %d, r = %d\n", l, r);
			}
		}
	}
	
    return ans;
}
