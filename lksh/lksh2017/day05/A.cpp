#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

char s[543];
int G[543][543];

int main() {
	int n, m;
	scanf("%d %d", &n, &m);
	
	for (int i = 0; i < n; i++)
		fill(G[i], G[i] + m, (int)1e9);
	
	for (int i = 0; i < n; i++) {
		scanf("%s", s);
		for (int j = 0; j < m; j++) {
			if (s[j] == 'x') {				
				for (int y = 0; y < m; y++) {
					G[i][y] = min(G[i][y], j * j - 2 * j * y);
				}
			}
		}
	}
	
	int q;
	scanf("%d", &q);
	while (q--) {
		int i, j;
		scanf("%d %d", &i, &j);
		i--, j--;
		int cur = (int)1e9;
		for (int x = 0; x < n; x++) cur = min(cur, G[x][j] + x * x - 2 * x * i);
		cur += i * i + j * j;
		printf("%d\n", cur);
		for (int y = 0; y < m; y++) G[i][y] = min(G[i][y], j * j - 2 * j * y);
	}
	
	return 0;
}