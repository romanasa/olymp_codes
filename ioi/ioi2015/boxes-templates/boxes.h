#include <bits/stdc++.h>
#define ll long long
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

const int dd = (int)1e7 + 7;
ll L[dd], R[dd];

long long delivery(int N, int K, int t, int p[]) {
	for (int i = 0; i < K; i++) {
		L[i] = 2 * p[i];
		R[N - 1 - i] = 2 * (t - p[N - 1 - i]);
	}
	
	for (int i = K; i < N; i++) {
		int ind = i / K * K - 1;
		L[i] = L[ind] + 2 * p[i];
		R[N - 1 - i] = R[N - 1 - ind] + 2 * (t - p[N - 1 - i]);
	} 
	
	ll ans = (ll)1e18 + 7;
	
	for (int i = -1; i < N; i++) {
		if (i < 0)
			ans = min(ans, R[i + 1]);
		else if (i + 1 >= N)
			ans = min(ans, L[i]);
		else
			ans = min(ans, L[i] + R[i + 1]);	
	}
	
	for (int i = -1; i < N; i++) {
		if (i < 0) 
			ans = min(ans, t + R[i + K + 1]);
		else if (i + K + 1 >= N)
			ans = min(ans, L[i] + t);
		else
			ans = min(ans, L[i] + t + R[i + K + 1]);
	}
	return ans;
}
