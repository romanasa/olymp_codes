/**
 * Author: Sergey Kopeliovich (Burunduk30@gmail.com)
 */

#include <cassert>
#include <cstring>
#include <cstdio>

#define forn(i, n) for (int i = 0; i < (int)(n); i++)
#define fill(a, x) memset(a, x, sizeof(a))

const int N = 300;
int l[N][N], r[N][N], id[N][N], k[N], res[N];

void go( int l[N][N], int r[N][N], int v, int u, int c1, int c2 ) {
	int x = r[u][c1];
    if (x != -1) {
	    l[x][c1] = -1;
		go(r, l, u, x, c2, c1);
	}
	l[v][c1] = u;
	r[u][c1] = v;
}

int main() {
	#define NAME "move"
	assert(freopen(NAME ".in", "r", stdin));
	assert(freopen(NAME ".out", "w", stdout));

	int n, m, a;
	scanf("%d%d", &n, &m);
	int size = n > m ? n : m;
	fill(l, -1), fill(r, -1);
	forn(i, n) {
		scanf("%d", &k[i]);
		forn(j, k[i]) {
			scanf("%d", &a), a--;
			id[i][a] = j;
			int c = 0;
			while (r[a][c] != -1)
			  c++;
			go(l, r, i, a, j, c);
		}
	}
	forn(i, n) {
		fill(res, -1);
		forn(c, size)
			if (l[i][c] != -1)
				res[id[i][l[i][c]]] = c;
		forn(j, k[i])
			printf("%d ", res[j]);
		puts("");
	}
}
