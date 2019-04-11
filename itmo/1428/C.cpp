#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

const int N = 8;
ll part[N + 7][N + 7][N + 7];
ll m[N + 7][N + 7][N + 7];
ll Q[N + 7], ans[N + 7];


ll C1(ll n, ll k) {
	if (k == 0) return 1;
	ll x = n + k - 1;
	ll cur = 1;
	for (int it = 0; it < k; it++) {
		cur *= x;
		x--;
	}
	for (int it = 0; it < k; it++) cur /= (it + 1);
	return cur;
}

void precalc() {


	part[0][0][0] = 1;
	
	for (int i = 0; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			for (int k = 0; k <= N; k++) {
    			part[i][j][k] = (i >= j && k > 0 ? part[i - j][j][k - 1] : 0) + part[i][j - 1][k];
			}
		}
	}
	
	Q[0] = 1;
	m[0][0][0] = 1;
	
	for (int i = 0; i <= N; i++) {
		for (int children = 0; children < i; children++) {
			for (int groups = 0; groups <= children; groups++) {
				Q[i] += part[children][children][groups] * m[i - 1][i - 1][children];
			}
			ans[i] += m[i - 1][i - 1][children];
		}
		
		err("ans[%d] = %lld\n", i, ans[i]);
		err("Q[%d] = %lld\n", i, Q[i]);
	
		for (int j = 1; j <= N; j++) {
			for (int k = 0; k <= N; k++) {
				for (int last = 0; last <= (i / j) && last <= k; last++) {
				
					if (i == 5 && j == 2 && k == 3) {
						//err("last = %d\n", last);
						//err("+= C1(%lld, %d) * m[%d][%d][%d] = %lld * %lld\n", Q[j], last, i - last * j, j - 1, k - last,
						//	C1(Q[j], last), m[i - last * j][j - 1][k - last]);
					}
				
					m[i][j][k] += C1(Q[j], last) * m[i - last * j][j - 1][k - last];
				}
			}
		}
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	precalc();
	
	int n;
	while (cin >> n) {
		if (n == 0) break;
		cout << ans[n + 1] << "\n";
	}
	return 0;
}