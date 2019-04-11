#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <cstring>
#include <vector>
#include <string>
#include <set>
#include <map>
#include <cassert>
#include <ctime>


using namespace std;

#ifdef WIN32
    #define LLD "%I64d"
#else
    #define LLD "%lld"
#endif

typedef pair<int, int> pii;
typedef long long ll;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<bool> vb;
typedef vector<vb> vvb;
typedef vector<ll> vll;
typedef vector<vll> vvll;

ll rdtsc() {
    ll tmp;
    asm("rdtsc" : "=A"(tmp));
    return tmp;
}

#define TASKNAME "makeintihappy"
#define pb push_back
#define mp make_pair
#define EPS (1e-9)
#define INF ((ll)1e18)
#define sqr(x) ((x) * (x))         
#define eprintf(...) fprintf(stderr, __VA_ARGS__)

const int maxh = 10, maxw = 1000;
int now[maxh][maxw];

int h, w;

#define left myleft
ll d[maxw][maxh][1 << (maxh + 1)], left;

int main() {
	srand(rdtsc());
	freopen(TASKNAME".in", "r", stdin);
	freopen(TASKNAME".out", "w", stdout);
	
	while (scanf("%d%d"LLD, &w, &h, &left) >= 1) {
		for (int mask = 0; mask < (1 << (h + 1)); mask++)
			d[w - 1][h - 1][mask] = 1;
			
		for (int x = w - 1; x >= 0; x--) {
			for (int y = h - 2; y >= 0; y--) {
				for (int mask = 0; mask < (1 << (h + 1)); mask++) {
					ll &cur = d[x][y][mask];
					cur = 0;
					if (!x && (mask >> (y + 1)))
						continue;
					
					int maskn = mask;
					maskn &= ((1 << (h + 1)) - 1 - (1 << (y + 1)));
					int need = -1;
					if (x) {
						int tmp = ((mask >> y) & 7);
						if (tmp == 7 || !tmp)
							need = !!tmp;
					}
					//eprintf("need = %d\n", need);
					
					for (int now = 0; now < 2; now++, maskn |= (1 << (y + 1))) {
						if (need != now)
							cur += d[x][y + 1][maskn];
					}
					cur = min(cur, INF);
					assert(cur >= 0);
				}
			}
			if (x) for (int mask = 0; mask < (1 << h); mask++) {
				d[x - 1][h - 1][mask] = d[x][0][mask << 1] + d[x][0][(mask << 1) + 1];
				d[x - 1][h - 1][mask] = min(d[x - 1][h - 1][mask], INF);
				
				d[x - 1][h - 1][mask + (1 << h)] = x > 1 ? d[x - 1][h - 1][mask] : 0;
			}
		}
		/*
		for (int x = 0; x < w; x++) {
			for (int y = 0; y < h; y++) {
				for (int mask = 0; mask < (1 << (h + 1)); mask++) {
					printf("d[%d][%d][%d] = %lld\n", x, y, mask, d[x][y][mask]);
				}
			}
		}*/
		
		if (d[0][0][0] + d[0][0][1] < left) {
			printf("Impossible\n");
			continue;
		}
		int mask = 0;
		for (int x = 0; x < w; x++) {
			for (int y = 0; y < h; y++) {
				int maskn = mask;
				maskn &= (1 << (h + 1)) - 1 - (1 << y);
				
				ll current = d[x][y][maskn];
				if (y && x && !((mask >> (y - 1)) & 7))
					current = 0;
				now[y][x] = 0;
				if (left > current)
					left -= current, now[y][x] = 1;
				mask = (maskn | (now[y][x] << y));
			}
			mask &= ((1 << h) - 1);
			mask <<= 1;
		}
		for (int y = 0; y < h; y++) {
			for (int x = 0; x < w; x++)
				printf(now[y][x] ? "b" : "w");
			printf("\n");
		}
		//break;
	}
	return 0;
}
