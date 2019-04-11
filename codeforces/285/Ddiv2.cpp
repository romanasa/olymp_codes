#define _CRT_SECURE_NO_WARNINGS
#pragma comment(linker, "/STACK:66777216")
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
#include <unordered_set>
#include <cstring>

using namespace std;

typedef unsigned long long ull;
typedef long long ll;
typedef long double ld;

#define forn(i, n) for (ll i = 0; i < (ll)n; i++)
#define fornn(i, q, n) for (ll i = q; i < (ll)n; i++)
#define mp make_pair
#define pk push_back
#define all(v) v.begin(), v.end()
#define times clock() * 1.0 / CLOCKS_PER_SEC

#define TASK "kthsubstr"

const double eps = 1e-7;
const double pi = acos(-1.0);

const int inf = (int)2e9 + 1;
const ll linf = (ll)9e18 + 7;
const ll MM = (ll)1e9 + 7;
    
const int MAXN = 2e5 + 7;

int T[4 * MAXN];

int f(int i) {
	return i & (-i);
}

void update(int pos, int val) {
	pos++;
	for (int i = pos; i < MAXN; i += f(i))
		T[i] += val;
}

int get(int pos) {
	pos++;
	int ans = 0;
	for (int i = pos; i; i -= f(i))
		ans += T[i];
	return ans;
}

int P[MAXN], Q[MAXN], F1[MAXN], F2[MAXN], S[MAXN], ans[MAXN];

int main() {
	//freopen(TASK".in", "r", stdin), freopen(TASK".out", "w", stdout);
    //freopen("input.txt", "r", stdin), freopen("output.txt", "w", stdout), freopen("test.txt", "w", stderr);
	int n;
	cin >> n;       
	forn(i, n) 
		scanf("%d", P + i);
			
	forn(i, n)
		scanf("%d", Q + i);
	
	forn(i, n) {             
		F1[i] = get(P[i]);   
		update(P[i], 1);     
	}            
	memset(T, 0, sizeof(int) * MAXN);
	forn(i, n) {
		F2[i] = get(Q[i]);
		update(Q[i], 1);     
	}
	memset(T, 0, sizeof(int) * MAXN);
    forn(i, n)
    	S[i] = (P[i] - F1[i] + Q[i] - F2[i]);
	
	for (int i = n - 1; i >= 0; i--) {
		int cur = n - i;
		if (S[i] >= cur && i)
			S[i - 1]++;
		S[i] %= cur;
	}

	forn(i, n) {
		update(i, 1);
	}
             
    forn(i, n) {            
    	int l = -1, r = n - 1;             	
    	while (r - l > 1) {
    		int m = (l + r) / 2;
    		if (get(m) >= S[i] + 1)
    			r = m;
    		else
    			l = m;
    	}
    	ans[i] = r;
    	update(r, -1);
    }
    forn(i, n)
    	printf("%d ", ans[i]);
	return 0;
}