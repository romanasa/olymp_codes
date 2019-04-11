#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

struct st {
	int r[3], id;
};

int main() {
	
	int n; cin >> n;
	
	vector<st> A(n);
	vector<int> used(n), sum(n);
	
	for (int i = 0; i < n; i++) {
		cin >> A[i].r[0] >> A[i].r[1] >> A[i].r[2] >> A[i].id;
	}
	
	for (int it = 0; it < n - 1; it++) {
	
		for (int i = 0; i < n; i++) if (!used[i]) {
			sum[i] = 0;
			for (int j = 0; j < 3; j++) {
				int mn = (int)1e9, i1 = -1;
				int mn2 = (int)1e9, i2 = -1;
				for (int t = 0; t < n; t++) if (!used[t] && t != i) {
					int q = A[i].r[j] - A[t].r[j];
					if (mn > (q < 0 ? q + 360 : q)) {
						mn = q < 0 ? q + 360 : q, i1 = t;
					}
					q = -q;
					if (mn2 > (q < 0 ? q + 360 : q)) {
						mn2 = q < 0 ? q + 360 : q, i2 = t;
					}
				}
				int q = A[i2].r[j] - A[i1].r[j];
				if (q < 0) q += 360;
				sum[i] += q;
			}
		}
	
		int ind = -1;
		for (int i = 0; i < n; i++) if (!used[i] && (ind == -1 || (sum[i] < sum[ind] || sum[i] == sum[ind] && A[i].id > A[ind].id)))
			ind = i;
		if (ind == -1) assert(0);
		used[ind] = 1;
		cout << A[ind].id << "\n";
	}
	for (int i = 0; i < n; i++) if (!used[i]) cout << A[i].id << "\n";

	return 0;
}