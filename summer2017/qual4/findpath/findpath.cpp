#include "findpath.h"
#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

int solve(int n, int* P, int* Q, int* a) {
	int l = -1, r = n - 1;
    while (r - l > 1) {
        int m = (l + r) / 2;
        for (int i = 0; i < n; i++) Q[i] = 0;
        Q[0] = 1;
        ask(m);
        if (a[n - 1])
            r = m;
        else
            l = m;
    }
    int len = r + 1;
    P[0] = 0, P[len - 1] = n - 1;
	
    for (int it = 1; it < len - 1; it++) {
    	vector<int> cur;
    	//err("it = %d\n", it);
  		for (int i = 0; i < n; i++) Q[i] = 0;
  		Q[P[it - 1]] = 1;
  		ask(1);
  		for (int i = 0; i < n; i++) if (a[i]) cur.push_back(i);
  		
  		//err("cur = {"); for (int x : cur) err(" %d,", x); err(" }\n");
  		
  		for (int i = 0; i < n; i++) Q[i] = 0;
  		Q[n - 1] = 1;
  		ask(len - 1 - it);
  		for (int i : cur) if (a[i]) {
  			P[it] = i;
  			break;
  		}
  		//err("P[%d] = %d\n", it, P[it]);
    }
    return len;
}
