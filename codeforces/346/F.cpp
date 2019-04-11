#define _CRT_SECURE_NO_WARNINGS
#pragma comment(linker, "/STACK:256000000")
#include <iostream>
#include <cstdio>
#include <cmath>
#include <vector>
#include <ctime>
#include <map>
#include <set>
#include <string>
#include <queue>
#include <deque>
#include <cassert>
#include <cstdlib>
#include <bitset>
#include <algorithm>
#include <string>
#include <list>
#include <fstream>
#include <cstring>
#include <sstream>
#include <numeric>
#include <unordered_map>
#include <unordered_set>

using namespace std;

typedef unsigned long long ull;
typedef long long ll;
typedef long double ld;

#define forn(i, n) for (int i = 0; i < (int)n; i++)
#define fornn(i, q, n) for (int i = q; i < (ll)n; i++)
#define mp make_pair
#define pk push_back
#define all(v) v.begin(), v.end()
#define times clock() * 1.0 / CLOCKS_PER_SEC

#define TASK "rollback"

const double eps = 1e-7;
const double pi = acos(-1.0);

const ll INF = (ll)2e9 + 1;
const ll LINF = (ll)8e18;
const ll inf = (ll)2e9 + 1;
const ll linf = (ll)8e18;
const ll MM = (ll)1e9 + 7;

int solve();
void gen();

int main()
{
#ifdef _DEBUG
    freopen("input.txt", "r", stdin), freopen("output.txt", "w", stdout);
#else
    //freopen(TASK".in", "r", stdin), freopen(TASK".out", "w", stdout);
    //freopen("input.txt", "r", stdin), freopen("output.txt", "w", stdout);//, freopen("test.txt", "w", stderr);
#endif
    solve();
    return 0;
}

const int dd = 1e3 + 7;

int A[dd][dd];
int T[dd][dd];

map<int, vector<pair<int, int> > > M;
int n, m;

bool ok(int x, int y) {
    return x >= 0 && x < n && y >= 0 && y < m;
}

int dx[] = {-1, 0, 1, 0};
int dy[] = {0, 1, 0, -1};

int p[dd * dd], r[dd * dd];

int get(int v) {
    return v == p[v] ? v : p[v] = get(p[v]);
}

void un(int a, int b) {
    a = get(a), b = get(b);
    if (a != b) {
        if (r[b] > r[a])
            swap(a, b);
        p[b] = a;
        r[a] += r[b];
    }
}
ll k;


int j = 0;

ll O[dd][dd];

void out(int x, int y, ll k) {
    if (j == 0)
        return;
    O[x][y] = k;
    j--;

    forn(gg, 4) {
        int nx = x + dx[gg];
        int ny = y + dy[gg];
        if (ok(nx, ny) && T[nx][ny] && !O[nx][ny])
            out(nx, ny, k);
    }
}

int solve() {
    cin >> n >> m >> k;
               
    forn(i, n) {
        forn(j, m) {
            scanf("%d", &A[i][j]);
            M[A[i][j]].push_back(mp(i, j));
        }
    }                                      

    forn(i, n)
        forn(j, m)
            p[i * m + j] = i * m + j, r[i * m + j] = 1;

    int cnt = 0;
    int cntC = 0;

    for (auto it = M.rbegin(); it != M.rend(); it++) {

        for (auto c : it->second) {
            int x, y;
            tie(x, y) = c;

            T[x][y] = 1;
            cntC++;
            cnt++;

            forn(gg, 4) {
                int nx = x + dx[gg];
                int ny = y + dy[gg];

                if (ok(nx, ny) && T[nx][ny]) {
                    if (get(x * m + y) != get(nx * m + ny)) {
                        un(x * m + y, nx * m + ny);
                        cnt--;
                    }
                }
            }
            ll t = it->first;

        	if (k % t)
           		continue;                                                  

        	if (k / t <= r[get(x * m + y)]) {
            	j = k / t;
           		out(x, y, t);
            	puts("YES");
            	forn(i, n) {
                	forn(j, m) {
                    	printf("%d ", O[i][j]);
                	}
                	printf("\n");
            	}
            	return 0;
        	}
        }
                                  
        
                        
    }
    puts("NO");
    return 0;
}