#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

const int dd = 31;

struct rect { int x1, y1, x2, y2; } A[dd];

int main() {
	int n;
	scanf("%d", &n);
	
	for (int i = 0; i < n; i++) {
		scanf("%d %d %d %d", &A[i].x1, &A[i].x2, &A[i].y1, &A[i].y2);
	}
	
	for (int i = 0; i < n; i++) {
		int x, y;
		scanf("%d %d", &x, &y);
		for (int j = 0; j < n; j++) {
			if (A[j].x1 <= x && x <= A[j].x2 && A[j].y1 <= y && y <= A[j].y2) {
				E[j].push_back(i);
			}
		}
	}
	
	for (int v = 0; v < n; v++) {
		for (int to : E[v]) {
			
			
		
		}
	}
	
	return 0;
}