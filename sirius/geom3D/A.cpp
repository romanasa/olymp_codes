#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;
typedef double ld;

ld G[111][111];
 
struct pt {
	ld x, y, z;
	
	pt() {}
	pt(ld x, ld y, ld z) : x(x), y(y), z(z) {}
	
	pt operator + (pt b) { return pt( x + b.x, y + b.y, z + b.z ); }
	pt operator - (pt b) { return pt( x - b.x, y - b.y, z - b.z ); }
	
	ld operator * (pt b) { return x * b.x + y * b.y + z * b.z; }
	pt operator % (pt b) { return pt( y * b.z - b.y * z, b.x * z - x * b.z, x * b.y - y * b.x ); }
	
	void norm() { 
		ld len = sqrt(x * x + y * y + z * z);
		x /= len, y /= len, z /= len;
	}
	
	void read() {
		cin >> x >> y >> z;
	}	
	
	ld len() { return sqrt(x * x + y * y + z * z); }
	
	friend ld mixed(pt A, pt B, pt C) { return (A % B) * C; }
	friend ld dist(pt A, pt B, pt C, pt D) {
		if (((B - A) % (D - C)).len()) return mixed((B - A), (D - C), (C - A)) / ((B - A) % (D - C)).len();
		pt M = (C - A) % (B - A);
		pt N = M % (B - A);
		N.norm();
		return (C - A) * N;
	}
	
	friend ld dist(pt A, pt B) { return sqrt((B.x - A.x) * (B.x - A.x) + (B.y - A.y) * (B.y - A.y) + (B.z - A.z) * (B.z - A.z)); }
	friend ld dist(pt M, pt A, pt B) { return ((A - M) % (B - M)).len() / dist(A, B); }
};

#define TASK "lines"

int main() {
#ifndef HOME
	freopen(TASK".in", "r", stdin), freopen(TASK".out", "w", stdout);
#endif

	int n;
	cin >> n;
	
	pt S, T;
	S.read(), T.read();
	
	vector<pair<pt, pt> > A(n);
	
	for (int i = 0; i < n; i++) {
		A[i].first.read(), A[i].second.read();
	}
	
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < i; j++) {
			G[i][j] = G[j][i] = abs(dist(A[i].first, A[i].second, A[j].first, A[j].second));
		}
	}
	
	for (int i = 0; i < n; i++) G[i][n] = G[n][i] = abs(dist(S, A[i].first, A[i].second));
	for (int i = 0; i < n; i++) G[i][n + 1] = G[n + 1][i] = abs(dist(T, A[i].first, A[i].second));
	
	G[n][n + 1] = G[n + 1][n] = dist(S, T);
	
	for (int k = 0; k < n + 2; k++) {
		for (int i = 0; i < n + 2; i++) {
			for (int j = 0; j < n + 2; j++) {
				G[i][j] = min(G[i][j], G[i][k] + G[k][j]);
			}
		}
	}
	cout.precision(10);
	cout << fixed << G[n][n + 1] << "\n";
	return 0;
}