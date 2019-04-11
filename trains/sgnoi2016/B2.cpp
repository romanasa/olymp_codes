#include <cstdio>
#include <vector>
#include <set>

#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

char ss[4007];
char a[2007][2007];
int r[2007];

vector<pair<int, int> > T[2007];

int cnt[2007];

void upd(int len, int t) {
	cnt[len] += t;
	//err("cnt[%d] += %d\n", len, t);
}

struct dsu {
	short P[2007], R[2007], I[2007];
	dsu() { for (int i = 0; i < 2007; i++) P[i] = I[i] = i, R[i] = 1; }
	
	int get(int v) { return P[v] == v ? v : P[v] = get(P[v]); }
	int getr(int v) { return I[get(v)]; }
	int getsz(int v) { return R[get(v)]; }
	
	void un(int a, int b) {
		a = get(a), b = get(b);
		if (a != b) {
			if (R[b] > R[a]) swap(a, b);
			I[a] = max(I[a], I[b]);
			P[b] = a, R[a] += R[b];
		}
	}
} J[2007];


int n, m, k;

void add(int i, int j) {
	if (i > 0) {
		int ind = J[j].getr(i - 1);
		if (ind == i) upd(J[j].getsz(i - 1) - 1, -1);
	}
	if (i + 1 < n) {
		int ind = J[j].getr(i + 1);
		if (ind > i + 1) upd(J[j].getsz(i + 1) - 1, -1);
	}
	J[j].un(i, i + 1);
	upd(J[j].getsz(i) - 1, 1);
}

int main() {
	
	scanf("%d %d %d\n", &n, &m, &k);
		
	for (int i = 0; i < n; i++) {
		gets(ss);
		for (int j = 0; j < m; j++) a[i][j] = ss[2 * j] - '0';
	}

	for (int j = m - 1; j >= 0; j--) {
		for (int i = 0; i < n; i++) {
			if (!a[i][j]) r[i]++;
			else r[i] = 0;
		}
		for (int i = 0; i < n; i++) T[r[i]].push_back({ i, j });
	}

	ll ans = 0;
	
	for (int x = m; x > 0; x--) {
		for (auto c : T[x]) add(c.first, c.second);
		
		if (x) {
			int c = (k + (x - 1)) / x;
			ll s = 0;
			for (int y = c; y <= n; y++) {
				s += (y - c + 1);
				ans += cnt[y] * s;
			}
		}
	}
    printf("%lld\n", ans);
	return 0;
}