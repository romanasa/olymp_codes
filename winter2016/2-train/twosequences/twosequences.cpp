#include "twosequences.h"
#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__)
 
using namespace std;
 
typedef long long ll;
 
const int dd = (int)8e7 + 7;

int P[dd], S[dd];
int G[dd];

const int mod = (int)1e9 + 7;
 
void add(int &a, int b) {
    a += b;
    if (a >= mod) a -= mod;
}
 
int countSequences(int n, int *a) {

	if (n == 1) return 1;

	P[0] = -1;
	for (int i = 0; i < n; i++) {
		P[i + 1] = max(P[i], a[i]);
	}
	
	S[n - 1] = (int)1e9;
	
	for (int i = n - 1; i > 0; i--)
		S[i - 1] = min(S[i], a[i]);

	for (int i = 0; i < n; i++) {
		if (P[i] >= a[i] && a[i] >= S[i])
			return 0;
	}	
	
	for (int i = 0; i < n; i++)
		G[a[i]] = i;
	
	for (int i = 1; i < dd; i++) {
		G[i] = max(G[i], G[i - 1]);
	}
		
	/*for (int i = 0; i <= 5; i++) {
		printf("G[%d] = %d\n", i, G[i]);
	}*/
	
	int ans = 1;
	for (int i = 1; i < n; i++) {
	
		if (a[i] <= P[i]) continue;
		if (G[P[i]] >= i) continue;
		
		add(ans, ans);
	}
	
    return ans;
}