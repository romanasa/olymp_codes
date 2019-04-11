#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

int P[1234][1234];
int S[1234][1234];

#define TASK "fence-relicts"

int main() {
#ifndef HOME
	freopen(TASK".in", "r", stdin), freopen(TASK".out", "w", stdout);
#endif
	int n, s;
	cin >> n >> s;
	
	vector<pair<int, int> > A(n);
	vector<int> Gx, Gy;
	
	for (int i = 0; i < n; i++) {
		cin >> A[i].first >> A[i].second;
		Gx.push_back(A[i].first);
		Gy.push_back(A[i].second);
	}
	
	sort(Gx.begin(), Gx.end());
	Gx.resize(unique(Gx.begin(), Gx.end()) - Gx.begin());
	
	sort(Gy.begin(), Gy.end());
	Gy.resize(unique(Gy.begin(), Gy.end()) - Gy.begin());
	
	for (int i = 0; i < n; i++) {
		A[i].first = lower_bound(Gx.begin(), Gx.end(), A[i].first) - Gx.begin() + 1;
		A[i].second = lower_bound(Gy.begin(), Gy.end(), A[i].second) - Gy.begin() + 1;
		S[A[i].first][A[i].second]++;
	}
	
	int szx = (int)Gx.size();
	int szy = (int)Gy.size();
	
	for (int i = 1; i <= szx; i++) {
		for (int j = 1; j <= szy; j++) {
			P[i][j] = P[i - 1][j] + P[i][j - 1] - P[i - 1][j - 1] + S[i][j];
		}	
	}
	
	int ans = -1;
	int x1 = -1, y1 = -1, x2 = -1, y2 = -1;
	
	for (int i = 1; i <= szx; i++) {
		for (int j = 1; j <= szy; j++) {
		
			int l = szy;
		
			for (int t = i; t <= szx; t++) {

				if (i != t) while (l >= j && s < (Gy[l - 1] - Gy[j - 1]) * (Gx[t - 1] - Gx[i - 1])) l--;
				if (l < j) continue;
				
				//err("i = %d, j = %d, t = %d, l = %d\n", i, j, t, l);
				
				int cur = P[t][l] - P[i - 1][l] - P[t][j - 1] + P[i - 1][j - 1];
				
				if (cur > ans) {
					ans = cur, x1 = Gx[i - 1], y1 = Gy[j - 1], x2 = Gx[t - 1], y2 = Gy[l - 1];		
				}
			}
		}
	}
	cout << x1 << " " << y1 << " " << x2 << " " << y2 << "\n";
	
	return 0;
}