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
	

	ll j1 = (a - 2 * b) / 5;
	ll i1 = b + 2 * j1;

	ll j2 = (c - 2 * d) / 5;
	ll i2 = d + 2 * j2;

	cout << abs(i1 - i2) + abs(j1 - j2);	
	return 0;
}