#include <bits/stdc++.h>
#define ll long long
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)
using namespace std;

const int dd = (int)1e6 + 1;
int n, P[dd], B[dd];
/*
const int MAX_MEM = (int)2e8;
char MEM[MAX_MEM];
int mpos;

inline void* operator new(size_t n) {
	char *res = MEM + mpos;
	mpos += n;
	return (void*)res;
}*/

inline void operator delete(void*) {}

int main() {
	scanf("%d", &n);
	
	for (int i = 1; i <= n; i++) {
		scanf("%d", &B[i]);
		P[B[i]] = i;
	}	
	
	int ans = (int)1e9;
		
	for (int it = 0; it < 2; it++) {
	
		vector<int> used(2 * n + 7);
		int add = (n + 1) / 2;
		
		for (int i = 1; i <= n; i++) {
			int a = i, b = P[i];
		
			int t1 = (a <= b ? b - a : n - a + b);
			int t2 = -(a >= b ? a - b : n - b + a);
		
			if (abs(t1) < abs(t2)) 
				used[t1 + add] = used[t1 + add + n] = 1;
			else 
				used[t2 + add] = used[t2 + add + n] = 1;
		}
		
		
		int C = 0;
		
		int cur = 1 - (n + 1) / 2;
		int len = 0;
		
		for (int it = 0; it < 2 * n; it++) {
			if (used[cur + add]) {
				len = 0;
			} else {
				len++, C = max(C, len); 
			}
			if (cur == n / 2) cur = 1 - (n + 1) / 2;
			else cur++;
		}
		
		ans = min(ans, (n - C) / 2);
		for (int i = 1; i <= n; i++) P[i] = n + 1 - P[i];
	}
	
	printf("%d\n", ans);
	return 0;
}