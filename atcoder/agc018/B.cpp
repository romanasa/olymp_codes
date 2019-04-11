#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

int main() {
	int n, m;
	cin >> n >> m;
	vector<vector<int>> A(n, vector<int>(m));
	for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) {
		cin >> A[i][j];
		A[i][j]--;
	}
	
	int l = 0, r = n;
	while (r - l > 1) {
		int mid = (l + r) / 2;
		
		vector<int> ind(n), fail(m);
		
		int ok = 1;
		for (int it = 0; ; it++) {
			for (int i = 0; i < n; i++) if (ind[i] != -1) {
				while (ind[i] < m && fail[A[i][ind[i]]]) ind[i]++;
				if (ind[i] == m) ok = 0;
			}	
			if (!ok) break;
		
			map<int, int> cnt;
			for (int i = 0; i < n; i++) if (ind[i] != -1) {
				cnt[A[i][ind[i]]]++;
			}
			
			if (cnt.empty()) break;
			
			int bad = 0;
			for (auto c : cnt) {
				if (c.second > mid) {
					fail[c.first] = 1;
					bad = 1;
				}
			}
			if (!bad) {
				for (auto c : cnt) {
					for (int i = 0; i < n; i++) if (ind[i] != -1 && A[i][ind[i]] == c.first)
						ind[i] = -1;
				}
			}
		}
		
		if (*max_element(ind.begin(), ind.end()) > -1 || !ok) l = mid;
		else r = mid;
	}
	cout << r << "\n";
	return 0;
}