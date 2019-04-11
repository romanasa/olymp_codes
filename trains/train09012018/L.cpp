#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

struct pt {
	ll x, y;
	pt() {}
    pt(pt A, pt B) : x(B.x - A.x), y(B.y - A.y) {}
	ll len() { return x * x + y * y; }
	ll operator % (pt b) const { return x * b.y - y * b.x; }
};

struct line {
	ll a, b, c;
	int get(pt A) { return (a * A.x + b * A.y + c) > 0; }
};

int sgn(ll x) { return x ? x > 0 ? 1 : -1 : 0; }

bool in(pt A, pt B, pt C, pt M) {
    int s1 = sgn(pt(A, B) % pt(A, M));
    int s2 = sgn(pt(B, C) % pt(B, M));
    int s3 = sgn(pt(C, A) % pt(C, M));
    return s1 == s2 && s2 == s3 && s1;
}

#define TASK "triangles"

int main() {
#ifndef HOME
	freopen(TASK".in", "r", stdin), freopen(TASK".out", "w", stdout);
#endif
	line m = { -1, (ll)2e9 + 7, 0 };
	
	int n;
	cin >> n;
	
	pt O; cin >> O.x >> O.y;
	
	vector<pt> A, B, P(n);
	for (int i = 0; i < n; i++) cin >> P[i].x >> P[i].y;
	
	/*int t1 = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < i; j++) {
			for (int k = 0; k < j; k++) {
				if (in(P[i], P[j], P[k], O)) t1++;
			}
		}
	}
	cout << t1 << "\n";*/
	
	for (auto &p : P) p.x -= O.x, p.y -= O.y;
	
	for (auto p : P) {
    	if (m.get(p)) A.push_back(p);
    	else B.push_back(p);
	}
	
	sort(A.begin(), A.end(), [](pt A, pt B) {
		ll t = A % B;
		if (t == 0) return A.len() < B.len();
		return t > 0;
	});
	
	sort(B.begin(), B.end(), [](pt A, pt B) {
		ll t = A % B;
		if (t == 0) return A.len() < B.len();
		return t > 0;
	});
	
	ll ans = 0;
	
	//err("A = "); for (auto p : A) err("(%I64d, %I64d), ", p.x, p.y); err("\n");
	//err("B = "); for (auto p : B) err("(%I64d, %I64d), ", p.x, p.y); err("\n");
	
	int j = 0;
	
	ll c = -1;
	pt pr;
	pr.x = pr.y = 0;
	
	for (auto p : A) {
		p.x = -p.x, p.y = -p.y;
		
		if (c != -1 && (pr % p == 0)) {
			ans += c;
			continue;
		}
		
		while (j < (int)B.size() && (B[j] % p > 0)) j++;
		int l = j;
		while (j < (int)B.size() && (B[j] % p == 0)) j++;
		ans += (c = 1ll * l * ((int)B.size() - j));
		pr = p;
	}
	
	j = 0;
	
	
	c = -1;
	pr.x = pr.y = 0;
	
	for (auto p : B) {
		p.x = -p.x, p.y = -p.y;
		
		if (c != -1 && (pr % p == 0)) {
			ans += c;
			continue;
		}
		
		while (j < (int)A.size() && (A[j] % p > 0)) j++;
		int l = j;
		while (j < (int)A.size() && (A[j] % p == 0)) j++;
		ans += (c = 1ll * l * ((int)A.size() - j));
		pr = p;
	}
	cout << ans << "\n";
	return 0;
}