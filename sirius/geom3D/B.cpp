#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;
typedef double ld;

 
struct pt {
	ld x, y, z;
	
	pt() {}
	
	pt(ld x, ld y, ld z) : x(x), y(y), z(z) {}
	
	pt operator + (pt b) { return pt( x + b.x, y + b.y, z + b.z ); }
	pt operator - (pt b) { return pt( x - b.x, y - b.y, z - b.z ); }
	pt operator * (ld t) { return pt( x * t, y * t, z * t ); }
	
	ld operator * (pt b) { return x * b.x + y * b.y + z * b.z; }
	pt operator % (pt b) { return pt( y * b.z - b.y * z, b.x * z - x * b.z, x * b.y - y * b.x ); }
	
	void norm() { 
		ld len = sqrt(x * x + y * y + z * z);
		x /= len, y /= len, z /= len;
	}
	
	void read() { cin >> x >> y >> z; }	
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

ld get(pt M, pt A, pt B) {
	if ((M - A) * (B - A) < 0) return dist(A, M);
	if ((M - B) * (A - B) < 0) return dist(B, M);
	return dist(M, A, B);
}

#define TASK "dist"

int main() {
#ifndef HOME
	freopen(TASK".in", "r", stdin), freopen(TASK".out", "w", stdout);
#endif
	pt A, B, C, D;
	A.read(), B.read(), C.read(), D.read();
	
	ld l = 0, r = 1;
	for (int it = 0; it < 100; it++) {
		ld m1 = l + (r - l) / 3, m2 = r - (r - l) / 3;
		
		pt X1 = A + (B - A) * m1;
		pt X2 = A + (B - A) * m2;
		
		if (get(X1, C, D) < get(X2, C, D))
			r = m2;
		else
			l = m1;
	}
	
	pt X = A + (B - A) * l;
	cout.precision(10);
	
	cout << fixed << get(X, C, D) << "\n";
	return 0;
}