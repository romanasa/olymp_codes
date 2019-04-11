#include <bits/stdc++.h>
  
using namespace std;
  
int p = 101;
int n;
  
int P[31];
  
int mod = (int)1e8 + 31;
/*
int gethash() {
    int sq = 0;
    for (int i = 0; i < n; i++)
        h = (1ll * h * p + T[i]) % mod, sq = (sq + T[i] * T[i] + 1) % mod;
    return (h + sq) % mod;
}
*/
//unordered_map<int, int> H;
  
int T[31];
  
int K;
int ans = 100 * 30 + 1;
  
  
int cnt = 0;
bool is_tl = false;
   
inline void tl() {
    if (++cnt == 1000)
        is_tl |= clock() > 0.48 * CLOCKS_PER_SEC, cnt = 0;
}
  
int H[31];
unordered_map<int, int> Z, G;
 
inline int get(int used) {
	if (Z.count(used))
		return Z[used];
		
    int cur = 0, S = 0;
    int cH = 0;
     
    for (int i = 0; i < n; i++)
        if ((used & (1 << i)) == 0)
            H[i] = T[i], S += T[i];
        else
        	H[i] = 0;
     
    //sort(H, H + cH);
     
    for (int i = n - 1; i >= 0; i -= 3) {
        S -= H[i];
        H[i] = 0;
        
        if (i > 0)
            S -= H[i - 1], H[i - 1] = 0;
        if (i > 1)
            S -= H[i - 2], H[i - 2] = 0;    
        
        cur += S;
    }   
    return Z[used] = cur;
}
 
struct req {
	int cur, used;
	bool operator < (req b) const {
		return cur + get(used) < b.cur + get(b.used);
	}
};

set<req> Q;

int main() {
#ifndef HOME
    freopen("mirror.in", "r", stdin);
    freopen("mirror.out", "w", stdout);
#endif
    scanf("%d", &n);
      
    for (int i = 0; i < n; i++)
        scanf("%d", &T[i]);

    Q.insert({ 0, 0 });
    G[0] = 0;
    
	while (Q.size()) {
	
	    int cur = Q.begin()->cur, used = Q.begin()->used;
		Q.erase(Q.begin());
     
    	if (used == (1 << n) - 1) {
        	ans = min(ans, cur);
    	} else {
     
        	int S = 0;
        	for (int i = 0; i < n; i++) {
            	if ((used & (1 << i)) == 0) {
                	S += T[i];
            	}
        	}
           
        	for (int i = 0; i < n; i++) {
            	int prv = (i ? i - 1 : n - 1);
            	int nxt = (i + 1 < n ? i + 1 : 0);
              
            	int s = 0;
              
            	if ((used & (1 << prv)) == 0)  s += T[prv];
            	if ((used & (1 << i)) == 0) s += T[i];  
            	if ((used & (1 << nxt)) == 0) s += T[nxt];
              
            	if (s > 0) {
            		int nused = used | (1 << prv) | (1 << nxt) | (1 << i);
            		
            		//if (G[nused] > cur + S - s) {
            			//G[nused] = cur + S - s;
            			Q.insert({ cur + S - s, nused });
            		//}
            	}
        	}
    	}
    }
    printf("%d", ans);
    return 0;
}