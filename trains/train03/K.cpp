#include <bits/stdc++.h>
#define ll long long
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;
/*
const int MAX_MEM = (int)2e8 + (int)5e7;
char MEM[MAX_MEM];
int mpos = 0;

inline void* operator new (size_t n) {
	if (mpos + n >= MAX_MEM)
		mpos = 0;
	char *res = MEM + mpos;
	mpos += n;
	return (void*)res;
}

inline void operator delete(void*) {}
*/

const int dd = 81;

ll S[dd + 5];

void upd(int &a, int b) { if (a > b) a = b;}

int A1[dd + 5], AN[dd + 5], B1[dd + 5], BN[dd + 5];
int G[dd + 5];

void calcA(ll a, int i) {
	if (i == 0) {
		(A1[i] = 0, AN[i] = 0);
		return;
	}
	if (i == 1) {
		(A1[i] = (a == 2), AN[i] = (a == 1));
		return;
	}
	if (a <= S[i - 1]) {
		calcA(a, i - 1);
		A1[i] = min(A1[i - 1], AN[i - 1] + 2);
		AN[i] = min(A1[i - 1], AN[i - 1]) + 1 + G[i - 2];
	} else {
		calcA(a - S[i - 1], i - 2);
		A1[i] = A1[i - 2] + 1;
		AN[i] = AN[i - 2];
	}
}

void calcB(ll a, int i) {
	if (i == 0) {
		(B1[i] = 0, BN[i] = 0);
		return;
	}
	if (i == 1) {
		(B1[i] = (a == 2), BN[i] = (a == 1));
		return;
	}
	if (a <= S[i - 1]) {
		calcB(a, i - 1);
		B1[i] = min(B1[i - 1], BN[i - 1] + 2);
		BN[i] = min(B1[i - 1], BN[i - 1]) + 1 + G[i - 2];
	} else {
		calcB(a - S[i - 1], i - 2);	
		B1[i] = B1[i - 2] + 1;
		BN[i] = BN[i - 2];
	}
}

int dist(ll a, ll b, int i) {
	if (a == b) {
		return 0;
	}
	
	if (a + 1 == b) {
		return 1;
	}
	
	int ans = (int)1e9 + 1;
	
	if (a <= S[i - 1] && b <= S[i - 1]) {
		upd(ans, dist(a, b, i - 1));
		upd(ans, A1[i - 1] + BN[i - 1] + 2);
	} else if (a > S[i - 1] && b > S[i - 1]) {
		upd(ans, dist(a - S[i - 1], b - S[i - 1], i - 2));
	} else {
		upd(ans, min(AN[i - 1], A1[i - 1]) + B1[i - 2] + 1); 
	}	
	return ans;
}

int main() {
	int n, q;
	scanf("%d %d", &q, &n);

	if (n > dd)
		n = dd;
	
	S[0] = 1;
	S[1] = 2;
	
	G[0] = 0;
	G[1] = 1;
	
	for (int i = 2; i <= n; i++) {
		S[i] = S[i - 1] + S[i - 2];
		G[i] = G[i - 2] + 1;
	}		
	
	while (q--) {	
		ll a, b;
		scanf("%I64d %I64d", &a, &b);
		if (a > b) swap(a, b);
		calcA(a, n), calcB(b, n);
		printf("%d\n", dist(a, b, n));
	}
	return 0;
}