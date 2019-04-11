#include <iostream>
#include <ctime>
#include <cassert>
#include <cmath>
#include <string>
#include <cstring>
#include <vector>
#include <fstream>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <set>
#include <map>
#include <iomanip>
#define nextLine() { for (int c = getchar(); c != '\n' && c != EOF; c = getchar()); }
#define sqr(a) ((a)*(a))
#define has(mask,i) (((mask) & (1<<(i))) == 0 ? false : true)

#ifdef LOCAL
    #define eprintf(...) fprintf(stderr, __VA_ARGS__)
#else
    #define eprintf(...)
#endif

#define TASK "i"
using namespace std;

#define pii pair<int,int>
#define mp make_pair
#define pb push_back
#define fi first
#define se second

#if ( _WIN32 || __WIN32__ )
    #define LLD "%I64d"
#else
    #define LLD "%lld"
#endif

typedef long long LL;
typedef long double ldb;
typedef vector <int> vi;
typedef vector <vi> vvi;
typedef vector <bool> vb;
typedef vector <vb> vvb;

const int INF = (1 << 30) - 1;
const ldb EPS = 1e-9;
const ldb PI = fabsl(atan2l(0.0, -1.0));
const int MAXN = 111111;
const int PRIMES = 3;
const int X[PRIMES] = {239, 1543, 57};
const int MODS[PRIMES] = {1000000007, 1000000009, 438476876};
int XPOW[PRIMES][MAXN];

class Hash {
public:
	int value[PRIMES];

	Hash() {
	}

	Hash(int c) {
		for (int i = 0; i < PRIMES; i++) {
			value[i] = c % MODS[i];
		}
	}

	void operator += (const Hash &o) {
		for (int i = 0; i < PRIMES; i++) {
			value[i] += o.value[i];
			if (value[i] >= MODS[i]) {
				value[i] -= MODS[i];
			}
		}
	}

	void shift(int length) {
		for (int i = 0; i < PRIMES; i++) {
			value[i] = (value[i] * 1LL * XPOW[i][length]) % MODS[i];
		}
	}
};

const Hash ZERO = Hash(0);

bool operator == (const Hash &a, const Hash &b) {
	for (int i = 0; i < PRIMES; i++) {
		if (a.value[i] != b.value[i]) {
			return false;
		}
	}
	return true;
}

char s[MAXN];
Hash t[4 * MAXN];
Hash rt[4 * MAXN];

void merge(const Hash &left, int length, const Hash &right, Hash &res) {
	res = left;
	res.shift(length);
	res += right;
}

void build(int v, int l, int r) {
	if (r - l == 1) {
		t[v] = Hash(s[l]);
		rt[v] = Hash(s[l]);
		return;
	}
	build(2 * v + 1, l, (l + r) / 2);
	build(2 * v + 2, (l + r) / 2, r);
	merge(t[2 * v + 1], r - (l + r) / 2, t[2 * v + 2], t[v]);
	merge(rt[2 * v + 2], (l + r) / 2 - l, rt[2 * v + 1], rt[v]);
}

void upd(int v, int l, int r, int x, char c) {
	if (x < l || x >= r) {
		return;
	}
	if (r - l == 1) {
		t[v] = Hash(c);
		rt[v] = Hash(c);
		return;
	}
	upd(2 * v + 1, l, (l + r) / 2, x, c);
	upd(2 * v + 2, (l + r) / 2, r, x, c);
	merge(t[2 * v + 1], r - (l + r) / 2, t[2 * v + 2], t[v]);
	merge(rt[2 * v + 2], (l + r) / 2 - l, rt[2 * v + 1], rt[v]);
}

pair <Hash, int> get(int v, int l, int r, int ql, int qr) {
	if (l >= qr || r <= ql) {
		return mp(ZERO, 0);
	}
	if (ql <= l && r <= qr) {
		return mp(t[v], r - l);
	}
	pair <Hash, int> left = get(2 * v + 1, l, (l + r) / 2, ql, qr);
	pair <Hash, int> right = get(2 * v + 2, (l + r) / 2, r, ql, qr);
	Hash res;
	merge(left.fi, right.se, right.fi, res);
	return mp(res, left.se + right.se);
}

pair <Hash, int> getR(int v, int l, int r, int ql, int qr) {
	if (l >= qr || r <= ql) {
		return mp(ZERO, 0);
	}
	if (ql <= l && r <= qr) {
		return mp(rt[v], r - l);
	}
	pair <Hash, int> left = getR(2 * v + 1, l, (l + r) / 2, ql, qr);
	pair <Hash, int> right = getR(2 * v + 2, (l + r) / 2, r, ql, qr);
	Hash res;
	merge(right.fi, left.se, left.fi, res);
	return mp(res, left.se + right.se);
}

int main() {
	clock_t start = clock();
	freopen("substring-palindromes.in", "r", stdin);
	freopen("substring-palindromes.out", "w", stdout);
	for (int i = 0; i < PRIMES; i++) {
		XPOW[i][0] = 1;
		for (int j = 1; j < MAXN; j++) {
			XPOW[i][j] = (XPOW[i][j - 1] * 1LL * X[i]) % MODS[i];
		}
	}
	scanf("%s", s);
	int n = strlen(s), m;
	build(0, 0, n);
	scanf("%d", &m);
	char op[111] = {0};
	for (int i = 0; i < m; i++) {
		scanf("%s", op);
		if (strcmp(op, "palindrome?") == 0) {
			int left, right;
			scanf("%d%d", &left, &right);
			Hash hash = get(0, 0, n, left - 1, right).fi;
			Hash hashRev = getR(0, 0, n, left - 1, right).fi;
			puts(hash == hashRev ? "Yes" : "No");
		} else if (strcmp(op, "change") == 0) {
			int pos;
			char c;
			scanf("%d %c", &pos, &c);
			upd(0, 0, n, pos - 1, c);
		} else {
			assert(false);
		}
	}
	eprintf("time: %.3lf\n", (double)(clock() - start) / CLOCKS_PER_SEC);
	return 0;
}
