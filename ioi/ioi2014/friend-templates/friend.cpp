#include "grader.h"
#include <bits/stdc++.h>
#define ll long long
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)
using namespace std;


// Find out answer

const int dd = (int)1e5 + 7;

int p[dd], q[dd];

int findSample(int n,int confidence[],int host[],int protocol[]) {
	for (int i = 0; i < n; i++)
		p[i] = confidence[i], q[i] = 0;
		
	for (int i = n - 1; i > 0; i--) {
		int x = host[i];
		int y = i;
		int P = p[x], Q = q[x], P1 = p[y], Q1 = q[y];
		
		if (protocol[i] == 2) {
			p[x] = max(P + Q1, P1 + Q);
			q[x] = Q + Q1;
		}
		
		if (protocol[i] == 1) {
			p[x] = max(P + P1, max(P + Q1, P1 + Q));
			q[x] = Q + Q1;
		}
		
		if (protocol[i] == 0) {
			p[x] = P + Q1;
			q[x] = max(P1 + Q, Q + Q1);
		}
	}
	//for (int i = 0; i < n; i++)
	//	err("(%d, %d)\n", p[i], q[i]);
	return max(p[0], q[0]);
}

