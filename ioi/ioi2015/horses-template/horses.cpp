#include <bits/stdc++.h>
#define ll long long
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)
using namespace std;

const int mod = (int)1e9 + 7;
const int dd = (int)5e5 + 7;

int n;
int A[dd], B[dd];

struct req {
	int l, r;
	ll val;
};

vector<req> T;
set<pair<int, int> > S;

struct SegmentTreeMul {
	int T[4 * dd];
	
	void build(int v, int tl, int tr) {
		if (tl == tr)
			T[v] = A[tl];
		else {
			int tm = (tl + tr) / 2;
			build(v * 2, tl, tm);
			build(v * 2 + 1, tm + 1, tr);
			
			T[v] = 1ll * T[v * 2] * T[v * 2 + 1] % mod;
		}
	}
	
	void upd(int v, int tl, int tr, int pos, int val) {
		if (tl == tr) {
			T[v] = val;
		} else {
			int tm = (tl + tr) / 2;
			if (pos <= tm)
				upd(v * 2, tl, tm, pos, val);
			else
				upd(v * 2 + 1, tm + 1, tr, pos, val);
				
			T[v] = 1ll * T[v * 2] * T[v * 2 + 1] % mod;
		}
	}
	
	int get(int v, int tl, int tr, int l, int r) {
		if (l == tl && r == tr)
			return T[v];
		int tm = (tl + tr) / 2;
		if (r <= tm)
			return get(v * 2, tl, tm, l, r);
		if (l > tm)
			return get(v * 2 + 1, tm + 1, tr, l ,r);
		return 1ll * get(v * 2, tl, tm, l, tm) * get(v * 2 + 1, tm + 1, tr, tm + 1, r) % mod;
	}
} H;

struct SegmentTreeMax {
	int T[4 * dd];
	
	void build(int v, int tl, int tr) {
		if (tl == tr)
			T[v] = B[tl];
		else {
			int tm = (tl + tr) / 2;
			build(v * 2, tl, tm);
			build(v * 2 + 1, tm + 1, tr);
			
			T[v] = max(T[v * 2], T[v * 2 + 1]);
		}
	}
	
	void upd(int v, int tl, int tr, int pos, int val) {
		if (tl == tr) {
			T[v] = val;
		} else {
			int tm = (tl + tr) / 2;
			if (pos <= tm)
				upd(v * 2, tl, tm, pos, val);
			else
				upd(v * 2 + 1, tm + 1, tr, pos, val);
				
			T[v] = max(T[v * 2], T[v * 2 + 1]);
		}
	}
	
	int get(int v, int tl, int tr, int l, int r) {
		if (l == tl && r == tr)
			return T[v];
		int tm = (tl + tr) / 2;
		if (r <= tm)
			return get(v * 2, tl, tm, l, r);
		if (l > tm)
			return get(v * 2 + 1, tm + 1, tr, l ,r);
		return max(get(v * 2, tl, tm, l, tm), get(v * 2 + 1, tm + 1, tr, tm + 1, r));
	}
} F;

int get() {
	
	T.clear();
	for (auto it = S.rbegin(); it != S.rend(); it++) {
		T.push_back({ it->first, it->second, F.get(1, 0, n, it->first, it->second) });
		if (T.size() > 61)
			break;
	}
	reverse(T.begin(), T.end());	

	bool ok = true;
	int ind = 0;
	
	while (ok) {
		ok = false;
		
		ll p = 1;		
		for (int j = ind + 1; j < (int)T.size(); j++) {
			p *= A[T[j].l];
			
			if (p * T[j].val > T[ind].val) {
				ind = j;
				ok = true;
				break;
			}
		}	
	}
	return H.get(1, 0, n, 0, T[ind].l) * T[ind].val % mod;
}

int init(int N, int X[], int Y[]) {
	n = N;
	copy(X, X + N, A);
	copy(Y, Y + N, B);
	
	F.build(1, 0, n);
	H.build(1, 0, n);
	
	vector<pair<int, int> > G;
	for (int i = 0; i < N; i++) {
		if (i && X[i] == X[i - 1] && X[i] == 1)
			G.back().second++;
		else
			G.push_back({ i, i });
	}
	
	for (auto c : G)
		S.insert(c);
	
	return get();
}

int updateX(int pos, int val) {

	if (A[pos] == 1 && val != 1) {
		auto it = S.upper_bound(make_pair(pos, dd));
		--it;
		
		int l = it->first, r = it->second;
		S.erase(it);
		
		if (l <= pos - 1) S.insert({ l, pos - 1 });
		S.insert({ pos, pos });
		if (pos + 1 <= r) S.insert({ pos + 1, r });
	}
	
	if (A[pos] != 1 && val == 1) {
		int R = pos;
		if (pos + 1 < n && A[pos + 1] == 1) {
			auto it = S.upper_bound(make_pair(pos + 1, dd));
			--it;
			
			int r = it->second;
			S.erase(it);
			S.insert({ pos, r });	
			R = r;
		}
		
		if (pos && A[pos - 1] == 1) {
			auto it = S.upper_bound(make_pair(pos - 1, dd));
			--it;
			
			int l = it->first;
			S.erase(it);
			S.insert({ l, R });	
		}
	}
	
	H.upd(1, 0, n, pos, val);
	A[pos] = val;
	return get();
}

int updateY(int pos, int val) {
	B[pos] = val;
	F.upd(1, 0, n, pos, val);
	return get();
}
