#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)
 
using namespace std;
 
typedef unsigned long long ll;
 
mt19937 rnd(1);
 
ll mul(ll a, ll b, ll m) {
	ll cur = a * b - m * ((long double)a * b / m);
	if (cur >= m) cur -= m;
	if (cur < 0) cur += m;
	return cur;
}

ll gcd(ll a, ll b) {
    if (!a || !b) return a ? a : b;
    if (a == b) return a;
    if ((a & 1) == 0 && (b & 1) == 0) return 2 * gcd(a >> 1, b >> 1);
    if ((a & 1) == 0) return gcd(a >> 1, b);
    if ((b & 1) == 0) return gcd(a, b >> 1);
    if (a > b) swap(a, b);
    return gcd((b - a) >> 1, a);
}
 
ll fact(ll n, ll add) {
    ll b0 = (((1ull * rnd()) << 32) + rnd()) % n;
    
    ll b1 = mul(b0, b0, n) + add;
    if (b1 >= n) b1 -= n;
    
    ll a = b1;
     
    for (int it = 0; it < 22; it++) {
        ll g = gcd(abs(b1 - b0), n); 
        for (int i = 0; i < (1 << it) && (g == 1 || g == n); i++) {       	
   			b1 = mul(b1, b1, n) + add;
    		if (b1 >= n) b1 -= n;
            g = gcd(abs(b1 - b0), n);
        }
        b0 = a;
        a = b1;
        if (g != 1 && g != n) return g;
    }
    return 1;
}
 
int main() {
    ll x;
    cin >> x;
          
    for (int it = 0; it < 15; it++) {
        ll t = fact(x, rnd() % 100 - 50);
        if (t != 1) {
            cout << t << " " << x / t << "\n";
            return 0;
        }
    }
    puts("IMPOSSIBLE");
    return 0;
}