#include <bits/stdc++.h>
#include "testlib.h"

using namespace std;

const int maxN = 50 * 1000;
const int maxQ = 100 * 1000;
const int maxC = 1000 * 1000 * 1000;

int main(int argc, char* argv[]) {
	
	registerValidation(argc, argv);
	
	int n = inf.readInt(1, maxN, "n");
	inf.readEoln();
	
	vector<int> A(n);
	
	for (int i = 0; i < n; i++) {
		A[i] = inf.readInt(1, maxC, "A_i");
		
		if (i > 0) 
			ensuref(A[i - 1] >= A[i], "A must be nonincreasing");
		
		if (i + 1 < n)
			inf.readSpace();
		else 
			inf.readEoln();
	}
	
	int q = inf.readInt(1, maxQ, "q");
	inf.readEoln();
	for (int i = 0; i < q; i++) {
		int l = inf.readInt(1, n, "l");
		inf.readSpace();
		int r = inf.readInt(1, n, "r");
		inf.readEoln();
		ensuref(l + 1 <= r, "length of query must be >= 2");	
	}
	inf.readEof();
	return 0;
}