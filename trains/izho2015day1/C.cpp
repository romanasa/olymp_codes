//#include <bits/stdc++.h>
#include <vector>
#include <iostream>
#include <algorithm>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)
  
using namespace std;
  
typedef long long ll;

struct hero {
    ll s, h, ind;
};
  
#define TASK "heroes"
  
const int dd = (int)2e5 + 7;
int n, m;
const int N = (1 << 18) + 7;
const int C = 450;

ll curSS;
  

ll T[dd], P[dd / C + 7];
int L[dd], R[dd], bl[dd];
ll sum;

struct MAGIC {
    
    MAGIC() {
    	fill(T, T + dd, 0ll);
    	fill(P, P + C, 0ll);
    	
  		for (int i = 0; i < dd; i++) {
			bl[i] = i / C;
			L[i] = bl[i] * C;
			R[i] = L[i] + C - 1;
  		}
    }
    
    void upd(int pos, ll val) {
    	P[bl[pos]] -= T[pos];
    	sum += val - T[pos];
    	T[pos] = val;
    	P[bl[pos]] += T[pos];
    }
    
    ll getSS() { return sum; }
    
    int get(ll sum) {
    	curSS = 0;
        int i = 0, pos = 0;
        while (P[i] <= sum) {
        	sum -= P[i];
        	::curSS += P[i];
        	i++, pos += C;
        }
        while (pos < m && T[pos] <= sum) {
        	sum -= T[pos];
        	::curSS += T[pos];
        	pos++;
        } 
    	return min(pos, m);
    }
} Q;
  
inline void upd(int pos, ll val) {
    Q.upd(pos, val);
}

int get(ll sum) {
    if (Q.getSS() <= sum) return m;
    return Q.get(sum);
}
  
int get(hero G, vector<hero> &B) {    
    int ind = get(G.h);
    if (ind == m) return m;
      
    ll s = ind ? curSS : 0;
    ll add = G.h - s;
      
    ll k = (B[ind].h + G.s - 1) / G.s;
      
    if (add - max(k - 1, 0ll) * B[ind].s > 0) ind++;
    return ind;
}

vector<int> S[dd];
 
int main() {
#ifndef HOME
    freopen(TASK".in", "r", stdin), freopen(TASK".out", "w", stdout);
#endif
  
    ios_base::sync_with_stdio(0);
    cin.tie(0);
      
    cin >> n >> m;
      
    vector<hero> A(n), B(m);
      
    for (int i = 0; i < n; i++) { cin >> A[i].s >> A[i].h; A[i].ind = i; }
    for (int i = 0; i < m; i++) cin >> B[i].s >> B[i].h;
      
    sort(A.begin(), A.end(), [](hero a, hero b) {
        return a.s == b.s ? a.ind < b.ind : a.s < b.s;
    });
     
    vector<int> tmp(m), up(m);
     
    for (int i = 0; i < m; i++) {
        tmp[i] = 1;
        S[1].push_back(i);
        up[i] = 1;
    }
     
    vector<int> ans(n);
    int pos = 0;
    	
    for (auto c : A) {      
        while (c.s >= pos && pos < dd) {
        	while (S[pos].size()) {
                int ind = S[pos].back();
                S[pos].pop_back();
             
                int x = (B[ind].h + c.s - 1) / c.s;
                upd(ind, x * B[ind].s);
                 
                if (up[ind]) {
                    tmp[ind]++;
                    if ((tmp[ind] - 1) * (tmp[ind] - 1) > B[ind].h) {
                        tmp[ind]--;
                        up[ind] = 0;
                    }
                    S[tmp[ind]].push_back(ind);
                } else {
                    tmp[ind]--;
                    if (tmp[ind] > 0) {
                    	int q = (B[ind].h + tmp[ind] - 1) / tmp[ind];
                    	while (q < pos) {
                    		tmp[ind]--;
                    		if (tmp[ind] == 0) break;
                    		q = (B[ind].h + tmp[ind] - 1) / tmp[ind];
                    	}
                    	if (tmp[ind] > 0) S[q].push_back(ind);
                    }
                }
            }
            //delete &S[pos];
            S[pos].shrink_to_fit();
            pos++;
        }
        ans[c.ind] = get(c, B);
    }
      
    for (int i = 0; i < n; i++) cout << ans[i] << "\n";
    return 0;
}