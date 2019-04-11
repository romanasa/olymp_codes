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
#include <cstring>
#include <sstream>
#include <numeric>
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

#define TASK "king"

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
	//freopen("input.txt", "r", stdin), freopen("output.txt", "w", stdout);// freopen("test.txt", "w", stderr);
#endif
	solve();
	return 0;
}
ull gcd(ull a, ull b) {
    if (!a || !b) return a ? a : b;
    if (a == b) return a;
     
    if ((a & 1) == 0 && (b & 1) == 0) return 2 * gcd(a >> 1, b >> 1);
    if ((a & 1) == 0) return gcd(a >> 1, b);
    if ((b & 1) == 0) return gcd(a, b >> 1);
    if (a > b) swap(a, b);
    return gcd((b - a) >> 1, a);
}

const int dd = (int)1e6 + 1;

bitset<dd> F;

vector<ull> ans;
int P[dd], iP;
int ind;

ull get(ull n) {
	for (int i = 0; i < iP; i++) {
		if (1ull * P[i] * P[i] > n) return 1;
		if (n % P[i] == 0) return P[i];
	}
	ull c1 = (ull)pow(n, 1.0 / 3) + 6;
	for (ull k = 1; k <= c1; k++) {
		ull c2 = (ull)(pow(n, 1.0 / 6) / (4 * sqrt(k))) + 6;
		for (ull d = 0; d <= c2; d++) {
			ull A = (ull)(2 * sqrt(k) * sqrt(n)) + d;
			ull t = A * A - 4 * k * n;
			if (t < 0) continue;
			ull B = (ull)(sqrt(t));
			if (B * B == t) {
				ull dd = gcd(A - B, n);	
				if (1 < dd && dd < n && n % dd == 0)
					return dd;
			}
		}
	}
	return 1;
}

void fact(ull n) {
	if (n == 1) return;
	ull div = get(n);
	if (div == 1)
		ans.push_back(n);
	else {
		fact(n / div);
		fact(div);
	}
}

int solve() {
	fornn(i, 2, dd)
		F[i] = 1;
	
	for (ull i = 2; i * i < dd; i++)
		if (F[i]) {
			for (ull j = i * i; j < dd; j += i)
				F[j] = 0;
		}
		
	for (ull i = 2; i < dd; i++)
		if (F[i]) P[iP++] = i;

	ios_base::sync_with_stdio(0);
	cin.tie(0);
		
	map<ull, vector<ull> > M;
	ull x;
	while (cin >> x) {
		if (!M.count(x)) { ans.clear(); fact(x); sort(ans.begin(), ans.end()); M[x] = ans; }	
		for (ull i : M[x]) cout << i << " "; cout << "\n";
	}
	return 0;
}