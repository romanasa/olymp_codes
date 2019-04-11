#include <bits/stdc++.h>
#define ll long long
#define y1 dfasfdwaf
using namespace std;

struct pt {
	ll x, y;
	ll operator % (pt b) {
		return x * b.y - y * b.x;
	}
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
	
};

ll dist(pt A, pt B) {
	return (B.x - A.x) * (B.x - A.x) + (B.y - A.y) * (B.y - A.y);
}

struct line {
	ll A, B, C;
	line(pt a, pt b, pt c) {
		A = b.y - a.y;
		B = a.x - b.x;
		C = -(A * a.x + B * a.y);
		
		if (get(c) < 0)
			A *= -1, B *= -1, C *= -1;
	}
	ll get(pt M) {
		return A * M.x + B * M.y + C;
	}
};

struct Convex {
	vector<pt> T;
	
	void build(vector<pt> &P) {
		sort(P.begin(), P.end(), [](pt a, pt b) { return a.x == b.x ? a.y < b.y : a.x < b.x; });
		pt O = P[0];

		sort(P.begin(), P.end(), [O](pt A, pt B) {
			ll t = vt(O, A) % vt(O, B);
			if (t == 0)
				return dist(O, A) < dist(O, B);
			return t > 0;
		});
		
		for (auto p : P) {
			while (T.size() > 1 && (vt(T[T.size() - 2], T.back()) % vt(T.back(), p) <= 0))
				T.pop_back();
			T.push_back(p);
		}
		T.push_back(T[0]);
	}
	
	ll get(line M) {
		int l = 0, r = (int)T.size() - 1;
		
		
		ll j = M.get(T[0]);
		ll ans = j;
		
		while (r - l > 1) {
			int m = (l + r) / 2;
			
			bool ok1 = M.get(T[m]) >= j;
			bool ok2 = M.get(T[m]) > M.get(T[m + 1]);
			
			ans = max(ans, M.get(T[m]));
			
			if (ok1 && !ok2)
				l = m;
			else
				r = m;
		}
		
		l = 0, r = (int)T.size() - 1;
		
		while (r - l > 1) {
			int m = (l + r) / 2;
			
			bool ok1 = M.get(T[m]) >= j;
			bool ok2 = M.get(T[m]) > M.get(T[m + 1]);
			
			ans = max(ans, M.get(T[m]));
			
			if (ok1 && ok2)
				r = m;
			else
				l = m;
		}
		return ans;
	}
} F;


vector<pt> P;

inline ll get(pt A, pt B, pt C) {
	return abs((A % B) + (B % C) + (C % A));
}

int main() {
	int n;
	scanf("%d", &n);
	
	P.resize(2 * n);
	
	for (int i = 0; i < n; i++) {
		scanf("%lld %lld", &P[i].x, &P[i].y);
		P[i + n] = P[i];
	}
	
	int m;
	scanf("%d", &m);
	vector<pt> T(m);
	
	for (int i = 0; i < m; i++) {
		scanf("%lld %lld", &T[i].x, &T[i].y);
	}

	F.build(T);
	
	ll ans = 0;
	
	int j = 0;
	ll sq = 0;
	
	for (int i = 0; i < n; i++) {
	
		if (j < i + 2) {
			j = i + 2;
			sq = get(P[i], P[i + 1], P[i + 2]);
		}	
	
		while (1) {
			line t(P[i], P[j], P[i + 1]);

			bool ok = (F.get(t) < 0);	
			
			if (ok) {
				j++;
				sq += get(P[i], P[j - 1], P[j]);
			}
			else
				break;
		}
		
		ans = max(ans, sq - get(P[i], P[j - 1], P[j]));
		sq -= get(P[i], P[i + 1], P[j]);
	}
	printf("%lld", ans);
	return 0;
}
