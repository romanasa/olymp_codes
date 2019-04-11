#include <bits/stdc++.h>
#define ll long long

using namespace std;

struct pt {
	ll x, y;
};

struct vt {
	ll x, y;
	vt(pt a, pt b) {
		x = b.x - a.x;
		y = b.y - a.y;
	}
	ll operator % (vt b) {
		return x * b.y - y * b.x;
	}
	ll operator * (vt b) {
		return x * b.x + y * b.y;
	}
	/*void out() {
		printf("(%d; %d)\n", x, y);
	}*/
};

bool inter(pt A, pt B, pt C, pt D) {
	bool ok1 = (vt(A, B) % vt(A, C)) * (vt(A, B) % vt(A, D)) <= 0;
	bool ok2 = (vt(C, D) % vt(C, A)) * (vt(C, D) % vt(C, B)) <= 0;
	return ok1 && ok2;	
}


bool check(pt O, vector<pt> &P) {
	long double t = 0;
	for (int i = 0; i < (int)P.size(); i++) {
		pt A = P[i], B = P[(i + 1) % P.size()];
		t += atan2((long double)(vt(O, A) % vt(O, B)), 
			(long double)(vt(O, A) * vt(O, B)));	
			
		/*vt(O, A).out();
		vt(O, B).out();*/
	}
	return t > 2;
}

int main() {
#ifndef HOME
	freopen("intersect.in", "r", stdin);
	freopen("intersect.out", "w", stdout);
#endif
	int k;
	scanf("%d", &k);
	
	while (k--) {
		int n;
		scanf("%d", &n);
		
		vector<pt> P(n);
		for (int i = 0; i < n; i++) {
			scanf("%I64d %I64d", &P[i].x, &P[i].y);
		}
		
		int m;
		scanf("%d", &m);
		vector<pt> T(m);
		for (int i = 0; i < m; i++) {
			scanf("%I64d %I64d", &T[i].x, &T[i].y);
		}


		bool ok1 = false;	
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				if (inter(P[i], P[(i + 1) % n], T[j], T[(j + 1) % m]))
					ok1 = true;
			}
		}
		
		if (ok1) {
			puts("YES");
		} else {
			if (check(P[0], T) || check(T[0], P)) {
				puts("YES");
			} else {
				puts("NO");
			}
		}
	}
	return 0;
}
