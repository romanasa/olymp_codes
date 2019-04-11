#include <bits/stdc++.h>
#define ll long long

using namespace std;

ll n;

bool ask(ll x, ll y) {
	if (x < 1 || x > n) return false;
	if (y < 1 || y > n) return false;
	cout << "examine " << x << " " << y << endl;
	string s;
	cin >> s;
	return (s == "true");
}

void out(ll x, ll y) {
	cout << "solution " << x << " " << y << endl;
}

ll findxr(ll x, ll y) {

	ll pr = 0;
	ll cur = 1;
	
	for (; ask(x + cur, y); pr = cur, cur *= 2);

 	ll l = x + pr, r = x + cur;
 	while (r > l) {
 		ll m = (l + r + 1) / 2;
 		if (ask(m, y))
 			l = m;
 		else
 			r = m - 1;
 	}
 	return l;
}

ll findxl(ll x, ll y) {
	ll pr = 0;
	ll cur = 1;
	
	for (; ask(x - cur, y); pr = cur, cur *= 2);

 	ll l = x - cur, r = x - pr;
 	
 	while (r > l) {
 		ll m = (l + r) / 2;
 		if (ask(m, y))
 			r = m;
 		else
 			l = m + 1;
 	}
 	return l;
}

ll findyl(ll x, ll y) {
	ll pr = 0;
	ll cur = 1;
	
	for (; ask(x, y - cur); pr = cur, cur *= 2);

 	ll l = y - cur, r = y - pr;
 	
 	while (r > l) {
 		ll m = (l + r) / 2;
 		if (ask(x, m))
 			r = m;
 		else
 			l = m + 1;
 	}
 	return l;
}

int main() {

	ll x0, y0;
	cin >> n >> x0 >> y0;

	ll xl = findxl(x0, y0);	
	ll xr = findxr(x0, y0);
	
	ll m = (xr - xl + 1);
	
	ll yl = findyl(x0, y0);
	
	ll xc = xl + m / 2;
	ll yc = yl + m / 2;
	
	ll lx = 1, rx = 1;
	ll ly = 1, ry = 1;
	
	for (; ask(xc + rx * 2 * m, yc); rx++);
	rx--;
	
	for (; ask(xc - lx * 2 * m, yc); lx++);
	lx--;
	
	for (; ask(xc, yc + ry * 2 * m); ry++);
	ry--;
	
	for (; ask(xc, yc - ly * 2 * m); ly++);
	ly--;
	
	
	ll dx = 0, dy = 0;
	
	if ((lx + rx + 1) % 2 == 1) {
	
		//assert(0);
		
		dx = 2 - (lx + 1);
		dy = 2 - (ly + 1);

		out(xc + dx * 2 * m, yc + dy * 2 * m);
		
	} else {
	
		dx = (lx ? -1 : 1);
		dy = (ly ? -1 : 1);
		
		out(xc + dx * m, yc + dy * m);
	}
	
	return 0;
}