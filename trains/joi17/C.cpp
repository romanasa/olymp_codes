#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

const int dd = 2007;

int A[dd][dd], len[dd];
int val;
int n, m;

bool check(int x) {
	int ok = 0;
	for (int it = 0; it < 2; it++) {
    	for (int i = 0; i < n; i++) {
    		int j = 0;
    		while (j < m && A[i][j] <= val + x) j++;
    		len[i] = j;
    	}
    	
    	//for (int i = 0; i < n; i++) err("len[%d] = %d\n", i, len[i]);
    	
    	for (int i = 1; i < n; i++) len[i] = min(len[i], len[i - 1]);
    	int minv = (int)1e9, maxv = -1;
    	for (int i = 0; i < n; i++) {
    		for (int j = len[i]; j < m; j++) {
    			minv = min(minv, A[i][j]);
    			maxv = max(maxv, A[i][j]);
    		}
    	}
    	
    	for (int i = 0; i < n; i++) reverse(A[i], A[i] + m);
    	if (maxv - minv <= x) ok = 1;
	}
	return ok;
}

bool check2(int x) {
	int ok = 0;
	for (int it = 0; it < 2; it++) {
		ok |= check(x);
		for (int i = 0; i < n - i - 1; i++) {
			for (int j = 0; j < m; j++) {
				swap(A[i][j], A[n - i - 1][j]);
			}
		}
	}
	return ok;
}

int main() {
	scanf("%d %d", &n, &m);
	
	val = (int)1e9 + 1;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			scanf("%d", &A[i][j]);
			val = min(val, A[i][j]);
		}
	}
	
	//check(18);
	//return 0;
	
	int l = -1, r = (int)1e9 + 1;
	
	while (r - l > 1) {
		int m = (l + r) / 2;
		if (check2(m)) r = m;
		else l = m;
	}
	printf("%d\n", r);
	
	return 0;
}