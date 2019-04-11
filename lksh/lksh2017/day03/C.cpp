#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

const int dd = (int)6e6 + 7;
int qMin[dd], qMax[dd];
int lMin, rMin, lMax, rMax;

void addMin(int x) {
	while (rMin > lMin && qMin[rMin - 1] > x) rMin--;
	qMin[rMin++] = x;
}

void addMax(int x) {
	while (rMax > lMax && qMax[rMax - 1] < x) rMax--;
	qMax[rMax++] = x;
}

int getMin() { return qMin[lMin]; }
int getMax() { return qMax[lMax]; }

void popMin(int x) { if (qMin[lMin] == x) lMin++; }

void popMax(int x) { if (qMax[lMax] == x) lMax++; }

#define TASK "e"

int main() {

#ifndef HOME
	freopen(TASK".in", "r", stdin), freopen(TASK".out", "w", stdout);
#endif
	int n;
	scanf("%d", &n);
	
	vector<int> A(n);
	
	for (int i = 0; i < n; i++) {
		scanf("%d", &A[i]);
	}
	
	int q;
	scanf("%d", &q);
	
	while (q--) {
		int x;
		scanf("%d", &x);
		
		int j = 0, sz = 0;
		int ans = 0;
		int L = -1, R = -1;
		
		lMin = 0, rMin = 0, lMax = 0, rMax = 0;
		
		for (int i = 0; i < n; i++) {
			
			while (j < n && (!sz || getMax() - getMin() <= x)) {
				addMin(A[j]), addMax(A[j]);
				j++, sz++;	
				//err("i = %d, j = %d, max = %d, min = %d\n", i, j, getMax(), getMin());
			}
			
			int cur = j - i;
			if (j == n && getMax() - getMin() <= x) cur++;
			
			if (cur > ans) {
				ans = cur;
				L = i, R = i + cur - 2;
			}
			
			
			popMin(A[i]), popMax(A[i]);
			sz--;
		}
		printf("%d %d\n", L + 1, R + 1);
	}
	
	return 0;
}