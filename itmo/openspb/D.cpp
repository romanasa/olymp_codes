#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

const long double pi = atan2(1.0, 1.0) * 4.0;

int dx[] = { -1, 0, 1, 0 };
int dy[] = { 0, 1, 0, -1 };

bool ok(ll x, ll y) {
	ll j = (x - 2 * y) / 5;
	ll i = y + 2 * j;
	return 2 * i + j == x && i - 2 * j == y;
}

void upd(ll &a, ll &b) {
	for (int i = 0; i < 4; i++) {
		ll na = a + dx[i], nb = b + dy[i];
		if (ok(na, nb)) {
			a = na, b = nb;
			break;
		}
	}
	assert(ok(a, b));
}

pair<long double, long double> rot(ll x, ll y, long double ang) {
	long double x1 = x * cos(ang) - y * sin(ang);
	long double y1 = y * cos(ang) + x * sin(ang);
	return { x1, y1 };
}

int main() {
	
	ll a, b, c, d;
	cin >> a >> b >> c >> d;
	
	upd(a, b); upd(c, d);
	
	//err("(%I64d, %I64d), (%I64d, %I64d)\n", a, b, c, d);
	/*
	auto c1 = rot(a, b, -pi / 6);
	auto c2 = rot(c, d, -pi / 6);
	
	ll ans = (ll)(abs(c1.first - c2.first) / sqrt(5) + 0.5) + (ll)(abs(c1.second - c2.second) / sqrt(5) + 0.5);
	cout << ans << "\n";*/
	
	ll dx = a - c; 
	ll dy = b - d;
	if (dx < 0 || dx == 0 && dy < 0) dx = -dx, dy = -dy;
	
	if (dx == 0) {
		cout << abs(dy) / 5 * 3;
		return 0;
	}
	if (dy == 0) {
		cout << abs(dx) / 5 * 3;
		return 0;
	}
	
	if (dy >= 0) {
		assert((dx + 3 * dy) % 5 == 0);
		cout << abs(dx + 3 * dy) / 5;
	} else {
		assert((3 * dx - dy) % 5 == 0);
		cout << abs(3 * dx - dy) / 5;		
	}

	return 0;
}