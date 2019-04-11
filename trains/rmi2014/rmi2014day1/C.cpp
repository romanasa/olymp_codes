#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)
 
using namespace std;
 
typedef long long ll;
typedef unsigned long long ull;
 
const int dd = 1e5 + 7;
  
const int len1 = 10 * 1000 + 7;
const int len2 = 1000 * 1000 + 7;
  
int z[len1 + len2];
  
char P[len1];
char T[len2];
int ok[len2];
  
int A[len1];
int B[len2], C[len2];
int nxt[27];
 
int nP, nT;
  
 
inline char get(int pos) {
    if (pos < nP)
        return ( P[pos] >= 'A' && P[pos] <= 'Z') ? P[pos] : 'a';
    if (pos == nP)
        return '#';
    pos -= nP + 1;
    return  (T[pos] >= 'A' && T[pos] <= 'Z') ? T[pos] : 'a';
}

const ull p = 239017;
	
ull powers[len2];
ull curh = 0, hA;

void setval(int pos, int val, int st) {
	//assert(nP - (pos - st) - 1 >= 0);
	curh -= powers[nP - (pos - st) - 1] * (ull)C[pos];
    C[pos] = val;
    curh += powers[nP - (pos - st) - 1] * (ull)C[pos];
} 

void out() {
	for (int i = 0; i < nT; i++) err("%d, ", C[i]); err("\n");
	cerr << curh << endl;
}

inline bool check(int pos) {
	//cerr << "pos = " << pos << ", " << curh << ", " << hA << endl;
    return curh == hA;
}
  
#define TASK "source"
 
int main() {
#ifndef HOME
    freopen(TASK".in", "r", stdin), freopen(TASK".out", "w", stdout);
#endif
	powers[0] = 1;
	for (int i = 1; i < len2; i++) powers[i] = powers[i - 1] * p;
	
    scanf("%s", P);
    scanf("%s", T);
  
    nP = strlen(P);
    nT = strlen(T);
     
    fill(nxt, nxt + 27, nP);
    for (int i = nP - 1; i >= 0; i--) {
        if ('A' <= P[i] && P[i] <= 'Z') A[i] = 0;
        else {
            A[i] = nxt[P[i] - 'a'] - i;
            nxt[P[i] - 'a'] = i;
        }
    }
     
    fill(nxt, nxt + 27, nT);
    for (int i = nT - 1; i >= 0; i--) {
        if ('A' <= T[i] && T[i] <= 'Z') B[i] = 0;
        else {
            B[i] = nxt[T[i] - 'a'] - i;
            nxt[T[i] - 'a'] = i;
        }
    }
     
     
     
    //for (int i = 0; i < nP; i++) err("%d, ", A[i]); err("\n");
    //for (int i = 0; i < nT; i++) err("%d, ", B[i]); err("\n");
  
    int n = nP + nT + 1;
  
    for (int i = 1, l = 0, r = 0; i < n; i++) {
        if (i <= r) z[i] = min(z[i - l], r - i + 1);
        while (i + z[i] < n && get(z[i]) == get(i + z[i])) z[i]++;
        if (i + z[i] - 1 > r) l = i, r = i + z[i] - 1;
    }
     
    for (int i = 0; i < nP; i++) {
        if (A[i] + i >= nP) A[i] = nP;
    }
    
    for (int i = 0; i < nP; i++) hA = hA * p + A[i];
     
    //for (int i = 0; i < nP; i++) err("%d, ", A[i]); err("\n");
   // cerr << hA << endl;
    //cerr << "-------" << endl;
    
    priority_queue<pair<int, int> > Q;
    for (int i = 0; i < nP; i++) {
        Q.push({ -(B[i] + i), i });
        int cur = B[i];
        if (B[i] + i >= nP) cur = nP;
        setval(i, cur, 0);
    }
     
    int ans = 0;
    for (int i = 0; i + nP - 1 < nT; i++) {
     
    	//err("1: "); out();
        if (z[i + nP + 1] >= nP) {
            if (check(i)) ok[i] = 1, ans++;
        }
        if (i + nP == nT) break;
        int R = i + nP + 1;
         
        while (Q.size() && -Q.top().first < R) {
            if (Q.top().second >= i) setval(Q.top().second, -Q.top().first - Q.top().second, i);
            Q.pop();
        }
    	//err("2: "); out();
         
        int cur = B[R - 1];
        if (B[R - 1] + R - 1 >= i + 1 + nP) cur = nP;
 
        curh = curh * p;
        
        setval(R - 1, cur, i + 1);
    	//err("3: "); out();
        setval(i, 0, i + 1);
        
    	//err("4: "); out();
        Q.push({ -(B[R - 1] + R - 1), R - 1 });
    }
     
    printf("%d\n", ans);
    for (int i = 0; i < nT; i++) if (ok[i]) printf("%d ", i + 1);
    return 0;
}