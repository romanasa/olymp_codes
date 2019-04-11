#include <bits/stdc++.h>

using namespace std;

int A[507][507];
int T[507];
int D[1007], G[1007], L[1007];

int n;

void out() {
		
	for (int i = 0; i < n; i++)
		A[i][T[i]] = 1;
		
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++)
			if (A[i][j])
				putchar('#');
			else
				putchar('.');
		putchar('\n');
	}
	exit(0);
}

int check() {
	fill(G, G + n + n, 0);
	fill(D, D + n + n, 0);
	fill(L, L + n + n, 0);
	
	int c = 0;
	for (int i = 0; i < n; i++) {
		c += G[T[i]];
		G[T[i]]++;
		
		c += D[i + T[i]];
		D[i + T[i]]++;
		
		c += L[i - T[i] + n];
		L[i - T[i] + n]++;
	}
	return c;
}

int main() {
#ifndef HOME
    freopen("queen.in", "r", stdin);
    freopen("queen.out", "w", stdout);
#endif

	srand(1377);
	
	scanf("%d", &n);
	
	for (int i = 0; i < n; i++)
		T[i] = i;
	
	while (1) {

		random_shuffle(T, T + n);
		
		int c1 = check();

		if (c1 == 0) {
			out();
		}
		
		for (int it = 0; it < n * n; it++) {
			
			int i = rand() % n, j = rand() % n;
			
			swap(T[i], T[j]);
			
			int c2 = check();
			
			if (c2 == 0) {
				out();
			}
					
			if (c1 < c2)
				swap(T[i], T[j]);
			else
				c1 = c2;
		}
	}
	
	return 0;
}
