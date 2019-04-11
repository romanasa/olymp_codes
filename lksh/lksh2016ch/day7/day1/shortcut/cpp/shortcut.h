#include <bits/stdc++.h>
#define ll long long
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stdout)
 
using namespace std;
 
const ll linf = (ll)1e18 + 7;
 
const int dd = (int)1e6 + 7;
ll P[dd], D[dd], C;
 
inline ll dist(int i, int j) {
    if (i > j) 
    	return P[i] - P[j];
    return P[j] - P[i];
}
 
inline ll dist(int a, int b, int i, int j) {
    if (a == b)
        return 0;
    ll q = min(dist(a, b), dist(a, i) + C + dist(j, b));
    q = min(q, dist(a, j) + C + dist(i, b));
    return q + D[a] + D[b];
}
 
struct myQ {
	deque<int> Q;

	myQ() {}
    
    inline void push(ll x) {
        while (Q.size() && Q.back() < x)
            Q.pop_front();
        Q.push_back(x);
    }
    inline void pop(ll x) {
        if (Q.front() == x)
            Q.pop_front();
    }
    
    inline ll get() {
        return Q.front();
    }
    
    inline void clear() {
    	Q.clear();
    }
    inline int sz() {
    	return (int)Q.size();
    }
};
 
ll find_shortcut(int n, vector <int> l, vector <int> d, int c) {
    C = c;
    copy(d.begin(), d.end(), D);
     
    for (int i = 0; i < n - 1; i++) {
        P[i + 1] = P[i] + l[i];
    }
            
    myQ S1, S2;
     
    ll ans = linf;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {            

			S1.clear();
			S2.clear();
        
            ll cur = 0;
             
            int indS = (j + 1 < n ? j + 1 : j);
            int indP = (i > 0 ? i - 1 : i);
             
            for (int t = j + 1; t < n; t++) {
                if (dist(j, t) + d[t] > dist(j, indS) + d[indS])
                    indS = t;
            }
             
            for (int t = i - 1; t >= 0; t--) {
                if (dist(t, i) + d[t] > dist(indP, i) + d[indP])
                    indP = t;
            }
 
            ll val = -P[0] + d[0];
             
            for (int t = 1; t <= i; t++) {
                cur = max(cur, val + P[t] + d[t]);
                val = max(val, -P[t] + d[t]);
            }
             
            val = P[n - 1] + d[n - 1];
            for (int t = n - 2; t >= j; t--) {
                cur = max(cur, val - P[t] + d[t]);
                val = max(val, P[t] + d[t]);
            }
             
            cur = max(cur, dist(indP, indS, i, j));
             
            for (int t = i; t <= j; t++) {
            	//ll q = min(P[t] - P[indP], P[j] - P[t] + C + P[i] - P[indP]) + d[t] + d[indP];	
                //cur = max(cur, q);
                //q = min(P[indS] - P[t], P[indS] - P[j] + C + P[t] - P[i]) + d[t] + d[indS];
                //cur = max(cur, q);
				cur = max(cur, dist(indP, t, i, j));
                cur = max(cur, dist(t, indS, i, j));
            }           
             
            int opt = i;
             
            S1.push(-P[i] + d[i]);
             
            for (int t = i + 1; t <= j; t++) {
                 
                while (2 * P[opt] < 2 * P[t] + P[i] - P[j] - C) {
                    S1.pop(-P[opt] + d[opt]);
                    S2.push(P[opt] + d[opt]);
                    opt++;
                }
             
                if (S1.sz())
                    cur = max(cur, S1.get() + P[t] + d[t]);
                     
                if (S2.sz())
                    cur = max(cur, S2.get() + C + P[j] + d[t] - P[t] - P[i]);       
 
                S1.push(-P[t] + d[t]);
            }
            /*
            for (int t = i + 1; t <= j; t++) {
                ll x = (P[t] + P[t] + P[i] - P[j] - c) / 2;
                 
                for (int k = i; k < t; k++) {
                    if (2 * P[k] >= 2 * P[t] + P[i] - P[j] - C)
                        cur = max(cur, P[t] - P[k] + d[k] + d[t]);
                    else
                        cur = max(cur, P[k] - P[i] + C + P[j] - P[t] + d[k] + d[t]);
                }*/
                /*
                int opt = upper_bound(P + i, P + t + 1, x) - (P + i);
                 
                for (int dopt = -2; dopt <= 2; dopt++) {
                    if (opt + dopt >= i && opt + dopt < t)
                        cur = max(cur, dist(opt + dopt, t, i, j));
                }
                 
                opt = lower_bound(P + i, P + t + 1, x) - (P + i);
                 
                for (int dopt = -2; dopt <= 2; dopt++) {
                    if (opt + dopt >= i && opt + dopt < t)
                        cur = max(cur, dist(opt + dopt, t, i, j));
                }*/
                //err("(%d; opt = %d), ", t, opt);
            //}
             
            //err("(%d--->%d) : %lld\n", i, j, cur);
            ans = min(ans, cur);
        }
    }
    return ans;
}