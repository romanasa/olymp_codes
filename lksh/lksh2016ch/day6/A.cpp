#include <bits/stdc++.h>
#include "grader.h"

using namespace std;

int Solution(int n) {
	int l = 1, r = n;
	
	while (r > l) {
		int m = (l + r) / 2;
		
		int t = Guess(m);
		
		if (t == 0)
			return m;
		if (t == 1)
			r = m - 1;
		if (t == -1)
			l = m + 1;
	}
	return l;
}
/*
int main() {
	
	return 0;
}*/
