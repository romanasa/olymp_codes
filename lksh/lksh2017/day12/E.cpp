#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

const int dd = (int)3e5 + 7;

vector<ll> E[dd], W[dd];
int A[dd], tp[dd], NA[dd];
ll P[dd];

const int C = 100;

unordered_map<int, int> M;

int main() {
	int n, m, q;
	scanf("%d %d %d", &n, &m, &q);
	
	for (int i = 0; i < n; i++) {
		scanf("%d", &tp[i]);
		tp[i]--;
		E[tp[i]].push_back(i);
	}
	
	for (int i = 0; i < n; i++) scanf("%d", &A[i]);
	for (int i = 0; i < n; i++) P[i + 1] = P[i] + A[i];
	
	for (int i = 0; i < m; i++) {
		W[i].push_back(0);
		for (int j : E[i]) W[i].push_back(W[i].back() + A[j]);	
	}
	
	while (q--) {
		int tp;
		scanf("%d", &tp);
		
		if (tp == 1) {
			int l, r;
			scanf("%d %d", &l, &r);
			l--, r--;
			
			ll sum = P[r + 1] - P[l];
			
			for (auto c : M) {
				int i = c.first;
				int a = lower_bound(E[i].begin(), E[i].end(), l) - E[i].begin();
				int b = upper_bound(E[i].begin(), E[i].end(), r) - E[i].begin() - 1;
				
				if (a <= b) {
					sum -= W[i][b + 1] - W[i][a];
					
					a -= c.second;
					b -= c.second;
					
					if (a < 0) a += (int)E[i].size();
					if (b < 0) b += (int)E[i].size();
					
					if (a <= b) sum += W[i][b + 1] - W[i][a];
					else sum += W[i][b + 1] + W[i][E[i].size()] - W[i][a];
				}
			}
			printf("%lld\n", sum);		
		} else {
			int x;
			scanf("%d", &x);
			M[x - 1]++;
		}
		
		if (M.size() > C) {
			for (auto c : M) {
				int i = c.first;
				int cur = c.second % (int)E[i].size();
			
				for (int j = 0; j < (int)E[i].size(); j++) {
					int ind = j + cur - (int)E[i].size();
					if (ind < 0) ind += (int)E[i].size();
					NA[E[i][ind]] = A[E[i][j]];
				}                 
				for (int j = 0; j < (int)E[i].size(); j++) W[i][j + 1] = W[i][j] + (A[E[i][j]] = NA[E[i][j]]);
			}
			M.clear();
			for (int i = 0; i < n; i++) P[i + 1] = P[i] + A[i];
		}
	}
	
	
	return 0;
}