#ifdef HOME
	#include "traffic.h"
#else
	#include "grader.h"
#endif

#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int dd = (int)1e6 + 7;

vector<vector<int> > E;
int cost[dd], S[dd], sum;
int ans = (int)2e9 + 1;
int ind = -1;

void calc(int v, int pr = -1) {
	S[v] = cost[v];
	
	int cur = 0;
	
	for (int to : E[v]) {
		if (to == pr) continue;
		calc(to, v);
		S[v] += S[to];
		cur = max(cur, S[to]);
	}
	cur = max(cur, sum - S[v]);
	
	if (ans > cur) {
		ans = cur;
		ind = v;
	}
}

int LocateCentre(int N, int pp[], int S[], int D[]) {
	E.resize(N);
	
	for (int i = 0; i < N - 1; i++) {
		E[S[i]].push_back(D[i]);
		E[D[i]].push_back(S[i]);
	}
		
	copy(pp, pp + N, cost);
	sum = accumulate(cost, cost + N, 0);
	
	calc(0, -1);
	
	return ind;
}
