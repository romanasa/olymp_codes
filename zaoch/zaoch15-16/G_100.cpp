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

vector<ull> P;

ull gcd(ull a, ull b) {
	while (b)
		a %= b, swap(a, b);
	return a;
}

ull get(ull n) {
	for (ull i : P) {
		if (i * i > n)
			return 1;
		if (n % i == 0)
			return i;
	}

	ull c1 = (ull)pow(n, 1.0 / 3) + 6;

	for (ull k = 1; k <= c1; k++) {
		ull c2 = (ull)(pow(n, 1.0 / 6) / (4 * sqrt(k))) + 6;
		for (ull d = 0; d <= c2; d++) {
			ull A = (ull)(2 * sqrt(k) * sqrt(n)) + d;

			for (int i = 0; i < 2; i++, A++) {
				ull t = A * A - 4 * k * n;
			
				if (t < 0)
					continue;
				ull B = (ull)(sqrt(t));
				if (B * B == t) {
					ull dd = gcd(A - B, n);	
					if (1 < dd && dd < n && n % dd == 0)
						return dd;
				}
				B++;
				if (B * B == t) {
					ull dd = gcd(A - B, n);
					if (1 < dd && dd < n && n % dd == 0)
						return dd;
				}
			}
		}
	}
	return 1;
}

bitset<1000007> F;

vector<ull> ans;

void fact(ull n) {
	if (n == 1)
		return;
	ull div = get(n);
	if (div == 1)
		ans.push_back(n);
	else {
		fact(n / div);
		fact(div);
	}
}

int solve() {
	fornn(i, 2, 1000007)
		F[i] = 1;
	for (ull i = 2; i * i < 1000007; i++)
		if (F[i]) {
			for (ull j = i * i; j < 1000007; j += i)
				F[j] = 0;
		}
	for (ull i = 2; i < 1000007; i++)
		if (F[i])
			P.push_back(i);


	ull n;
	cin >> n;
	n--;
	fact(n);

	sort(all(ans));

	cout << ans.size() << "\n";
	for (ull i : ans)
		cout << i - 1 << " ";
	return 0;
}