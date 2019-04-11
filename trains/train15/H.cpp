#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

const int maxT = 24 * 60 + 7;
int cntA[maxT], cntB[maxT];
vector<int> A[maxT], B[maxT];
int curA, curB;
int ans;

int main() {
	int n1;
	scanf("%d", &n1);
	for (int i = 0; i < n1; i++) {
		int h1, m1, h2, m2;
		scanf("%d:%d-%d:%d", &h1, &m1, &h2, &m2);
		A[h1 * 60 + m1].push_back(h2 * 60 + m2);
	}
	int n2;
	scanf("%d", &n2);
	for (int i = 0; i < n2; i++) {
		int h1, m1, h2, m2;
		scanf("%d:%d-%d:%d", &h1, &m1, &h2, &m2);
		B[h1 * 60 + m1].push_back(h2 * 60 + m2);
	}
	
	
	for (int t = 0; t < maxT; t++) {
		curA += cntA[t];
		curB += cntB[t];
		
		for (int x : A[t]) {
			if (curA == 0) curA++, ans++;
			cntB[x]++, curA--;
		}
		for (int x : B[t]) {
			if (curB == 0) curB++, ans++;
			cntA[x]++, curB--;
		}
	}
	printf("%d\n", ans);
	return 0;
}