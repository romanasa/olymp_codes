#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)
 
using namespace std;
 
typedef long long ll;
 
const int C = 1;
const int dd = (int)3e5 + 7;
const int LOG = 19;
int l[dd], r[dd];
int lg[dd];
int nxt[dd];
int mn[LOG][dd], mx[LOG][dd];
int Ans[C][C];
int L[dd], R[dd];
int n;
 
void calc() {
    for (int i = 0; i < n; i++) mx[0][i] = l[i], mn[0][i] = r[i];
    for (int t = 1; t < LOG; t++) {
        for (int i = 0; i + (1 << t) <= n; i++) {
            mx[t][i] = max(mx[t - 1][i], mx[t - 1][i + (1 << (t - 1))]);
            mn[t][i] = min(mn[t - 1][i], mn[t - 1][i + (1 << (t - 1))]);
        }
    }
}
 
int getmn(int l, int r) {
    int t = lg[r - l + 1];
    return min(mn[t][l], mn[t][r - (1 << t) + 1]);
}
 
int getmx(int l, int r) {
    int t = lg[r - l + 1];
    return max(mx[t][l], mx[t][r - (1 << t) + 1]);
}
 
struct SegmentTree {
    set<int> S[8 * dd];
     
    //SegmentTree() { fill(Mn, Mn + 4 * dd, (int)1e9), fill(Mx, Mx + 4 * dd, -1); }
     
    void upd(int v, int tl, int tr, int pos, int val, int tp) {
        if (tl != tr) {
            int tm = (tl + tr) / 2;
            if (pos <= tm) upd(v * 2, tl, tm, pos, val, tp);
            else upd(v * 2 + 1, tm + 1, tr, pos, val, tp);
        }
        if (tp == -1) S[v].erase(val);
        else S[v].insert(val);
    }
     
    pair<int, int> get(int v, int tl, int tr, int l, int r, int i) {
        if (tl == l && tr == r) {
            auto it = S[v].upper_bound(i);
             
            int c1 = -1, c2 = (int)1e9;
            if (it != S[v].end()) c2 = min(c2, *it);
            if (it != S[v].begin()) {
                --it;
                c1 = max(c1, *it);
            }
            return { c1, c2 };
        }
         
        int tm = (tl + tr) / 2;
        if (r <= tm) return get(v * 2, tl, tm, l, r, i);
        if (l > tm) return get(v * 2 + 1, tm + 1, tr, l, r, i);
        auto c1 = get(v * 2, tl, tm, l, tm, i);
        auto c2 = get(v * 2 + 1, tm + 1, tr, tm + 1, r, i);
         
        return { max(c1.first, c2.first), min(c1.second, c2.second) };
    }   
} T;

struct Seg {
	vector<pair<int, int> > T[8 * dd];
	vector<int> M[8 * dd], MR[8 * dd];
	
	void build(int v, int tl, int tr, int *A) {
		T[v].resize(tr - tl + 1);
		M[v].resize(tr - tl + 1);
		MR[v].resize(tr - tl + 1);
		
		if (tl == tr) T[v][0] = { A[tl], tl }, M[v][0] = abs(A[tl] - tl) + 1, MR[v][0] = tl;
		else {
			int tm = (tl + tr) / 2;
			build(v * 2, tl, tm, A);
			build(v * 2 + 1, tm + 1, tr, A);
			merge(T[v * 2].begin(), T[v * 2].end(), T[v * 2 + 1].begin(), T[v * 2 + 1].end(), T[v].begin());
			
			for (int i = 0; i < (int)M[v].size(); i++) M[v][i] = abs(T[v][i].first - T[v][i].second) + 1;
			for (int i = 0; i < (int)MR[v].size(); i++) MR[v][i] = T[v][i].second;
			
			for (int i = (int)MR[v].size() - 2; i >= 0; i--) MR[v][i] = min(MR[v][i], MR[v][i + 1]);
			for (int i = 1; i < (int)M[v].size(); i++) M[v][i] = max(M[v][i], M[v][i - 1]);
		}
	}
	
	pair<int, int> get(int v, int tl, int tr, int l, int r, int x) {
		
			//err("tl = %d, tr = %d, l = %d, r = %d\n", tl, tr, l, r);
		
		if (tl == l && tr == r) {
			int ind = lower_bound(T[v].begin(), T[v].end(), make_pair(x, (int)1e9)) - T[v].begin();
			
			int c1 = -1e9, c2 = 1e9;
			
			if (ind > 0) c1 = M[v][ind - 1];
			if (ind < (int)T[v].size()) c2 = MR[v][ind];
			
			return { c1, c2 };
			
		} else {
			int tm = (tl + tr) / 2;
			
			if (r <= tm) return get(v * 2, tl, tm, l, r, x);
			if (l > tm) return get(v * 2 + 1, tm + 1, tr, l, r, x);
			
			auto c1 = get(v * 2, tl, tm, l, tm, x);
			auto c2 = get(v * 2 + 1, tm + 1, tr, tm + 1, r, x);
			
			return { max(c1.first, c2.first), min(c1.second, c2.second) };
		}
	}
} Q, QR;
 
 
bool check(int l, int r) {
    return getmx(l, r) < l && getmn(l, r) > r;
}
 
void init( int n, const int *l, const int *r ) {
    ::n = n;
    for (int i = 2; i < dd; i++) lg[i] = lg[i / 2] + 1;
    for (int i = 0; i < n; i++) ::l[i] = -1, ::r[i] = n;
 
    vector<pair<int, int> > A;
    for (int i = 0; i < n; i++) A.push_back({ r[i], i });
    sort(A.begin(), A.end());
 
    for (int i = 0; i < n; i++) T.upd(1, 0, 2 * n, l[i], i, 1);
 
    for (auto c : A) {
        int i = c.second;
        T.upd(1, 0, 2 * n, l[i], i, -1);
 
        if (l[i] + 1 < r[i]) {
            auto c = T.get(1, 0, 2 * n, l[i] + 1, r[i] - 1, i);
            ::l[i] = max(::l[i], c.first);
            ::r[i] = min(::r[i], c.second);
        }
    }   
     
    calc();
     
    if (n < C) {
        for (int len = 0; len < n; len++) {
            for (int i = 0; i + len < n; i++) {
                int j = i + len;
                if (check(i, j)) Ans[i][j] = j - i + 1;
                else Ans[i][j] = max(Ans[i][j - 1], Ans[i + 1][j]);
            }
        }
    } else {
  		for (int i = 0; i < n; i++) {
			nxt[i] = max(i ? nxt[i - 1] : 0, i);
			while (nxt[i] + 1 < n && check(i, nxt[i] + 1)) nxt[i]++;
			err("%d--->%d\n", i, nxt[i]);
			L[i] = i, R[i] = nxt[i];
  		}
  		
  		//err("i'm here\n");
  		Q.build(1, 0, n - 1, R);	
    }
}
 
 
int get(int L, int R) {
    int ans = 1;
    /*for (int i = L; i + ans <= R; i++) {
        while (i + ans <= R && check(i, i + ans)) ans++;
    } */

    err("L = %d, R = %d\n", L, R);
    
	auto c1 = Q.get(1, 0, n - 1, L, R, L);
	//err("ok\n");
	ans = max(ans, c1.first);
	ans = max(ans, R - c1.second + 1);
	
	err("c1 = (%d, %d)\n", c1.first, c1.second);
	
	int rL = n - 1 - L;
	int rR = n - 1 - R;
	
	//err("get %d, %d, rR + 1 = %d, rL - 1 = %d, rR = %d\n", 0, n - 1, rR + 1, rL - 1, rR);
	/*auto c2 = QR.get(1, 0, n - 1, rR, rL, rR);
	//err("ok\n");
	
	ans = max(ans, c2.first);
	ans = max(ans, rR - c2.second + 1);
	
	err("c2 = (%d, %d)\n", c2.first, c2.second); */
    
    return ans;
}