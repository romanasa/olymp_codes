#define _CRT_SECURE_NO_WARNINGS
#pragma comment(linker, "/STACK:256000000")
#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <cstring>
#include <algorithm>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <queue>
#include <deque>
#include <bitset>
#include <unordered_map>
#include <unordered_set>
 
using namespace std;
 
typedef long long ll;
 
#define forn(i, n) for (int i = 0; i < (int)n; i++)
#define for1(i, n) for (int i = 1; i <= (int)n; i++)
#define forq(i, s, t) for (int i = s; i <= (int)t; i++)
#define ford(i, s, t) for (int i = s; i >= (int)t; i--)
#define all(v) v.begin(), v.end()
#define TIME clock() * 1.0 / CLOCKS_PER_SEC
 
const double EPS = 1e-15;
const double PI = acos(-1.0);
const int MAXN = (int)256 + 2;
const int INF = (int)((ll)(1 << 31) - 1);
const int MOD = (int)1e9 + 7;
const ll P = 239017;
 
#define TASK "kingdom"
 
int solve();
 
int main()
{
#ifdef _DEBUG
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    freopen("test.txt", "w", stderr);
    double tstart = TIME;
#else
    freopen(TASK".in", "r", stdin), freopen(TASK".out", "w", stdout);
#endif
    solve();
#ifdef _DEBUG
    double tend = TIME;
    cerr << tend - tstart << " s.\n";
#endif
    return 0;
}
 
int g[MAXN][MAXN], k, n, p[MAXN];
int used[MAXN], wizard[MAXN];
 
void print_ans(int l, int x) {
    printf("%d\n%d\n", x, l);
    forn(i, n) {
        if (wizard[i])
            printf("%d ", i + 1);
    }
    exit(0);
}
 
int get_ans(int x) {
	memset(used, 0, sizeof(used));
	memset(wizard, 0, sizeof(wizard));
	
    int summ = 0;
    while (true) {
        int v = -1, maxi = -1;
        
        forn(i, n) {
            if (used[p[i]])
                continue;
            
            int cnt = 0;
            forn(j, n) {
                if (g[p[i]][p[j]] == x && !used[p[j]]) cnt++;
            }
            
            if (cnt > maxi) {
                maxi = cnt;
                v = i;
            }
        }
        if (v == -1) {
            break;
        }
        used[p[v]] = 1;
        wizard[p[v]] = 1;
        summ++;
        forn(i, n) {
            if (g[p[v]][p[i]] == x) {
                used[p[i]] = 1;
            }
        }
    }
    
    if (summ <= k) {
    	print_ans(summ, x);
    }
    return summ;
}
 
int solve() {
    srand(100500);
    scanf("%d%d", &n, &k);
    forn(i, n) {
        forn(j, n) {
            scanf("%d", &g[i][j]);
        }
    }
 
    forn(i, n)
        p[i] = i;
        
    while (true) {
        random_shuffle(p, p + n);
        {
        	int old = get_ans(1);
        
        	for (int it = 0; it < n * n; it++) {
        		int i = rand() % n, j = rand() % n;
        		if (i == j)
        			j = (j + 1) % n;
        		swap(p[i], p[j]);
        		int t = get_ans(1);
        	
        		if (old > t) {
        			old = t;
        		} else {
        			swap(p[i], p[j]);
        		}
        	}
        }
        
        {
        	int old = get_ans(2);
        
        	for (int it = 0; it < n * n; it++) {
        		int i = rand() % n, j = rand() % n;
        		if (i == j)
        			j = (j + 1) % n;
        		swap(p[i], p[j]);
        		int t = get_ans(2);
        	
        		if (old > t) {
        			old = t;
        		} else {
        			swap(p[i], p[j]);
        		}
        	}
        }
    }
    return 0;
 
}