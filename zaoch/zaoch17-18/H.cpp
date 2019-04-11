#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

struct pt {
	ll x, y;
	pt() {}
	pt(ll x, ll y): x(x), y(y) {}
	pt(pt A, pt B): x(B.x - A.x), y(B.y - A.y) {}
	
	ll operator % (pt b) const { return x * b.y - y * b.x; }
	ll operator * (pt b) const { return x * b.x + y * b.y; }
	
	bool operator < (pt B) const {
		if (y <= 0 && B.y > 0) return true;
		if (B.y <= 0 && y > 0) return false;
	
		if (y == 0 && B.y == 0 && (x < 0 && B.x >= 0)) return true;
		if (y == 0 && B.y == 0 && (B.x < 0 && x >= 0)) return true;
	
		return (*this % B) > 0;
	}
};

struct line {
	ll a, b, c;
	line() {}
	line(pt A, pt B) {
		a = B.y - A.y;
		b = A.x - B.x;
		c = -(a * A.x + b * A.y);
	}
	int sign(ll x) {
		if (x < 0) return -1;
		if (x > 0) return 1;
		return 0;
	}
	
	int get(pt A) { return sign(a * A.x + b * A.y + c); }
};

pt get(pt A, pt B, pt M) {
	line p(A, B);
	pt N(A.x + p.a, A.y + p.b);
	if (p.get(M) == p.get(N)) N = pt(A.x - p.a, A.y - p.b);
	return pt(N.x - A.x, N.y - A.y);
}

int main() {
	int n;
	cin >> n;
	
	vector<pair<pt, int> > E;
	
	int bal = 0;
	
	for (int i = 0; i < n; i++) {
		pt A, B, C;
		cin >> A.x >> A.y >> B.x >> B.y >> C.x >> C.y;
		
		if (pt(A, B) % pt(B, C) < 0) swap(B, C);
		
		pt L = get(A, C, B);
		pt R = get(A, B, C);
	 	
		E.push_back({ L, 0 });
		E.push_back({ R, 1 });	
		
		if (R < L) bal++;
	}
	
	sort(E.begin(), E.end());
	
	int ans = bal;
	
	for (auto c : E) {
		if (c.second == 0) bal++;
		else bal--;
		ans = max(ans, bal);
	}
	cout << ans << "\n";
	return 0;
}