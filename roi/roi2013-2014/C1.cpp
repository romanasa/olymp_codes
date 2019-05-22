#include <bits/stdc++.h>
#define ll long long

using namespace std;

ll ask(int i, int j) {
	printf("swap %d %d\n", i, j);
	fflush(stdout);
	ll t;
	scanf("%lld", &t);
	return t;
}

bool cmp(int i, int j) {
	ll a = ask(i, j);
	ll b = ask(i, j);
	return a < b;
}

int main() {
	int n;
	ll cur;
	
	scanf("%d %lld", &n, &cur);
	
	vector<int> T(n);
	for (int i = 0; i < n; i++)
		T[i] = i + 1;
	
	stable_sort(T.begin(), T.end(), cmp);
	
	vector<int> P(n);
	for (int i = 0; i < n; i++)
		P[T[i] - 1] = i + 1;
		
	printf("answer");
	for (int i = 0; i < n; i++)
		printf(" %d", P[i]);
	printf("\n");
	fflush(stdout);
	return 0;
}