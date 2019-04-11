#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

const int dd = (int)2e5 + 1;

struct pt { ll x, y; } P[dd];

struct vt {
	ll x, y;
	vt() {}
	vt(pt a, pt b) { x = b.x - a.x, y = b.y - a.y; }
	ll operator %(vt b) { return x * b.y - y * b.x; }
};

ll dist(pt a, pt b) {
	return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}

int main() {
	int n;
	scanf("%d", &n);
	
	for (int i = 0; i < n; i++) {
		scanf("%I64d %I64d", &P[i].x, &P[i].y);
	}
	
	vt cur(P[0], P[1]);
	int ok = 0;
	for (int i = 2; i < n; i++) {
		if (cur % vt(P[0], P[i])) ok = 1;
	}
	if(!ok) return 0 * puts("-1");
	
	sort(P, P + n, [](pt a, pt b) { return a.y == b.y ? a.x < b.x : a.y < b.y; });

	pt O = P[0];
	sort(P + 1, P + n, [O](pt A, pt B) {
		int t = vt(O, A) % vt(O, B);
		if (t == 0) return dist(O, A) > dist(O, B);
		return t > 0;
	});
	
	vt cur2(P[0], P[1]);
	
	int i = 1;
	while (cur2 % vt(P[0], P[i]) == 0) i++;
	reverse(P + 1, P + i);
	
	for (int i = 0; i < n; i++) printf("%I64d %I64d\n", P[i].x, P[i].y);
	return 0;
}