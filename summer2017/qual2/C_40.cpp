#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

vector<vector<int> > E;

int P[123];
int res[123];

int get() {
	int res = 0;
	for (auto c : E) {
		int mn = 1000, mx = -1000;
		for (int x : c) mn = min(mn, P[x]), mx = max(mx, P[x]);
		res += (mx - mn + 1) - (int)c.size();
	}
	return res;
}

int main() {
	int c, m;
	scanf("%d %d", &c, &m);
	
	E.resize(m);
	
	for (int i = 0; i < m; i++) {
		int x;
		scanf("%d", &x);
		E[i].resize(x);
		for (int j = 0; j < x; j++) {
			int t;
			scanf("%d", &t);
			E[i][j] = t - 1;
		}
	}
	
	for (int i = 0; i < c; i++) P[i] = i;
	
	srand(1488);
	
	while (1) {
		random_shuffle(P, P + c);
		
		int cur = get();
		
		for (int it = 0; it < 5000; it++) {
			int i = rand() % c, j = rand() % c;
			
			swap(P[i], P[j]);
			
			int t = get();
			
			if (t == 0) {
				for (int i = 0; i < c; i++) res[P[i]] = i;
				for (int i = 0; i < c; i++) cout << res[i] + 1 << " ";
				exit(0);
			}
			
			if (cur < t) {
				swap(P[i], P[j]);
			} else {
				cur = t;
			}
		}
	}
	return 0;
}