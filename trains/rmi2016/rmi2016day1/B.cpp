#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)
 
using namespace std;
 
typedef unsigned long long ull;
typedef long double ld;
 
int ok = 0;
const ull maxC = (1ull << 64) - 1;
const int maxT = 2642246;

bool okmul(ull a, ull b) {
	return a <= maxC / b;
}

bool oksum(ull a, ull b) {
	return a <= a + b;
}

const int dd = 322000;
const int maxN = 1e5 + 1;



ull cur[111];
pair<ull, unsigned short> A[dd];
ull Q[maxN];
int ind[maxN];
//ull ans[maxN];

int iA;

bool cmp(int a, int b) {
	return Q[a] < Q[b];
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    
    for (ull b = 2; b < (1 << 16); b++) {
  		ull p = 1;	
  		int ind = 0;
  		
  		while (okmul(p, b)) {
  			cur[ind++] = p;
  			p *= b;
  		}	
  		cur[ind++] = p;
  		
  		for (int i = 4; i < ind; i++) {
  			for (int j = 0; j < i; j++) if (oksum(cur[i], cur[j])) {
  				A[iA++] = { cur[i] + cur[j], b };
  			}
  		}
    }
    sort(A, A + iA);
    
    int n;
    cin >> n;
    
    
    for (int i = 0; i < n; i++) {
    	cin >> Q[i];
    }
    
    for (int i = 0; i < n; i++) ind[i] = i;
    sort(ind, ind + n, cmp);
    
    int pos = 0;
    ull cube = 1, cuberoot = 1;
    for (int it = 0; it < n; it++) {
    	int i = ind[it];
    	
    	while (pos < iA && A[pos].first < Q[i]) pos++;
    	
    	if (pos < iA && A[pos].first == Q[i]) {
    		Q[i] = A[pos].second;
    		continue;	
    	} 
    	
    	while (cuberoot < maxT && cube < Q[i]) {
    		cuberoot++;
    		cube = cuberoot * cuberoot * cuberoot;
    	}
    	cuberoot--;
    	cube = cuberoot * cuberoot * cuberoot;
    	
    	if (cube + 1 == Q[i] || cube + cuberoot == Q[i] || cube + cuberoot * cuberoot == Q[i]) {
    		Q[i] = cuberoot;
    		continue;
    	}
    	
    	ull t = sqrtl(Q[i]);
    	ull sq = t * t;
    	
    	if (sq + 1 == Q[i] || sq + t == Q[i]) {
    		Q[i] = t;
    		continue;
    	}
    	Q[i] = Q[i] - 1;
    }
    
    for (int i = 0; i < n; i++) cout << Q[i] << "\n";
    return 0;
}