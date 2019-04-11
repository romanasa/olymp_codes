#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

const int dd = (int)2e6 + 7;

struct pt { 
	int x, y, z, id; 
	pt() {}
	pt(int x, int y, int z): x(x), y(y), z(z) {}
	bool operator < (pt b) const {
		return y < b.y;
	}
};

ll a, b, C = ~(1<<31), M = (1<<16)-1;
int r() {
	a = 36969 * (a & M) + (a >> 16);
	b = 18000 * (b & M) + (b >> 16);
	return (C & ((a << 16) + b)) % 1000000;
}

int main() {
	int n, m, AA, B;
	while (cin >> n >> m >> AA >> B) {
		if (n == 0 && m == 0) break;
		
		vector<pt> A(n + m);
		vector<int> Q(n + m), pos(n + m);
		for (int i = 0; i < n; i++) {
			cin >> A[i].x >> A[i].y >> A[i].z;
			A[i].id = i;
		}
		a = AA, b = B;
		for (int i = 0; i < m; i++) A[n + i].x = r(), A[n + i].y = r(), A[n + i].z = r();
		n += m;
		
		sort(A.begin(), A.end(), [](pt a, pt b) {
			return a.z < b.z;t
		});
		
		vector<int> dp(A.size());
		for (int i = 0; i < (int)A.size(); i++) {
			int t = 0;
			for (int j = 0; j < i; j++) if (A[j].x < A[i].x && A[j].y < A[i].y && A[j].z < A[i].z) {
				t = max(t, dp[j]);
			}
			dp[i] = t + 1;
		}
		cout << *max_element(dp.begin(), dp.end()) << "\n";
	}
	return 0;
}