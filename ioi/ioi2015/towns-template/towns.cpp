#include "towns.h"
#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

int hubDistance(int N, int sub) {
	int v = 0, s = -1;
	int d = -1;
	
	vector<int> dv(N), ds(N);
	
	for (int i = 0; i < N; i++) if (i != v) {
		int cur = getDistance(v, i);
		dv[i] = cur;
		if (cur > d) d = cur, s = i;
	}
	
	ds[v] = dv[s];
	
	for (int i = 0; i < N; i++) if (i != v && i != s) {
		int cur = getDistance(s, i);
		ds[i] = cur;
	}
	
	int diam = *max_element(ds.begin(), ds.end());
	
	vector<int> B(N);
	for (int i = 0; i < N; i++) 
		B[i] = (ds[i] + ds[v] - dv[i]) / 2;
	
	sort(B.begin(), B.end());
	B.resize(unique(B.begin(), B.end()) - B.begin());
	
	int R = diam;
	for (int x : B) R = min(R, max(x, diam - x));
	
	int pos1 = -1, pos2 = -1;
	for (int x : B) if (R == max(x, diam - x)) {
		if (pos1 == -1) pos1 = x;
		else if (pos2 == -1) pos2 = x;
		else assert(0);
	}
	
	
	int ok1 = (pos1 != -1), ok2 = (pos2 != -1);
	{ // pos1
		int cnt1 = 0, cnt2 = 0;
    	for (int x = 0; x < N; x++) {
    		int cur = ds[x] + ds[v] - dv[x];
    		if (cur > 2 * pos1) cnt1++;
    		if (cur < 2 * pos1) cnt2++;
    	}
		if (cnt1 > N / 2 || cnt2 > N / 2) ok1 = 0;
	}
	
	
	if (pos2 != -1) {
		int cnt1 = 0, cnt2 = 0;
    	for (int x = 0; x < N; x++) {
    		int cur = ds[x] + ds[v] - dv[x];
    		//if (x == s) err("%d\n", cur);
    		if (cur > 2 * pos2) cnt1++;
    		if (cur < 2 * pos2) cnt2++;
    	}
		if (cnt1 > N / 2 || cnt2 > N / 2) ok2 = 0;
	}
	if (!ok1 && !ok2) return -R;
	
	int stC = (int)1e7;
	
	auto check = [&](vector<int> G, int rad1, int rad2) {
		auto eq = [&](int a, int b) {
			if (a == stC || b == stC) return false;
			if (a < stC && b > stC) return false;
			if (a > stC && b < stC) return false;
			
			if (a == b) return true;
			if (a < stC && b < stC) return ds[a] + ds[b] - getDistance(a, b) > 2 * rad1;
			else if (a > stC && b > stC) return ds[a - stC - 1] + ds[b - stC - 1] - getDistance(a - stC - 1, b - stC - 1) > 2 * rad2;
			else assert(0);
		};
		
		
		int n = (int)G.size();
		
		vector<int> l, b;
		for (int i = 0; i < n; i++) {
			if (l.empty() || !eq(l.back(), G[i])) {
				l.push_back(G[i]);
				if (b.size()) l.push_back(b.back()), b.pop_back();
			} else {
				b.push_back(G[i]);
			}
		}
		
		if (l.empty()) return true;
		
		int T = l.back();
		int cur = 0;
		
		while (l.size()) {
			if (eq(l.back(), T)) {
				if (l.size() == 1) b.push_back(l.back()), l.pop_back();
				else l.pop_back(), l.pop_back();
			} else {
				if (b.empty()) return true;
				l.pop_back();
				b.pop_back();
			}
		}
		return b.empty();
	};
	
	vector<int> T;
	for (int x = 0; x < N; x++) 
		if (ds[x] + ds[v] - dv[x] == 2 * pos1) T.push_back(x);
		else if (ds[x] + ds[v] - dv[x] == 2 * pos2) T.push_back(x + 1 + stC);
		else T.push_back(stC);
	
	if (!check(T, pos1, pos2)) return -R;
	return R;
}
