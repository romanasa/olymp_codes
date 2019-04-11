#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)
#define ll long long

using namespace std;

struct flt {
	ll A, B, ind;
	bool operator < (flt b) const {
		return B > b.B;
	}
};

void no() {
	printf("No");
	exit(0);
}

int main() {
#ifndef HOME
	freopen("electro.in", "r", stdin);
	freopen("electro.out", "w", stdout);
#endif
	int k;
	scanf("%d", &k);
	
	vector<flt> T;
	
	for (int i = 0; i < k; ++i) {
		ll a, b;
		scanf("%lld %lld", &a, &b);
		
		T.push_back({ a, b, i });
	}
	
	sort(T.begin(), T.end());
	
	/*vector<ll> A(k);	
	
	for (int i = k - 1; i >= 0; i--) {
		A[i] = (i < (k - 1) ? A[i + 1] : 0) + T[i].B;
	}*/
	
	int n;
	scanf("%d", &n);
	
	vector<pair<ll, int> > J(n);
	
	for (int i = 0; i < n; i++) {
		scanf("%lld", &J[i].first);
		J[i].second = i;
	}
	
	if (n == 1) {
		printf("Yes\n");
		for (int i = 0; i < k; i++)
			printf("-1 ");
		printf("\n");
		printf("0\n");
		return 0;
	}
	
	sort(J.rbegin(), J.rend());
	
	vector<ll> B(n);
	
	for (int i = n - 1; i >= 0; i--) {
		B[i] = (i < (n - 1) ? B[i + 1] : 0) + J[i].first;
	}
	
	vector<int> P1(n, -1), P2(k, -1);
	
	P2[T[0].ind] = 0;
	
	int j = 0;
	for (int i = 0; i < k; i++) {
		if (T[i].B < B[j])
			no();
			
		if (T[i].A >= (n - j)) {
			for (int l = j; l < n; l++)
				P1[J[l].second] = T[i].ind + 1;
			break;
		}	
		
		if (i == k - 1)
			no();
			
		P2[T[i + 1].ind] = T[i].ind + 1;
		for (int l = j; l < j + T[i].A - 1; l++)
			P1[J[l].second] = T[i].ind + 1;
		j += T[i].A - 1;
	}
	
	printf("Yes\n");
	for (int x: P2)
		printf("%d ", x);
	printf("\n");
	
	for (int x : P1)
		printf("%d ", x);
	
	return 0;
}
