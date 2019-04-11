#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <set>
#include <map>
#include <bitset>
#include <string>
#include <fstream>
#include <vector>
#include <cstring>
#include <cassert>
#include <random>
#include <queue>
#include <ctime>
  
using namespace std;
  
typedef long long ll;
typedef double ld;
  
int solve();
  
#define TASK "moocast"
#define err(...) //fprintf(stdout, __VA_ARGS__), fflush(stdout)
  
int main() {
    solve();
}
  
const int dd = 1e5 + 7;
  
inline ll get(ll x) {
    if (x < 0) return 0;
    if ((x & 3) == 0) return x;
    if ((x & 3) == 1) return 1;
    if ((x & 3) == 2) return x + 1;
    return 0;
}
  
inline void uax(ll &a, ll b) { if (a < b) a = b; }
  
const int C = 100 * 1000;
  
int solve() {
  
    ll n, a, b;
  
    cin >> a >> b >> n;
  	
      
    ll ans = 0;
    
    if (n & 1) {
    	for (ll x = max(a, b - n); x < b - n + 2; x++) {
        	uax(ans, get(x + n - 1) ^ get(x - 1));
    	}
    	cout << ans << "\n";
    	return 0;
    }
  
    for (ll x = max(a, b - n - n); x < b - n + 2; x++) {
        uax(ans, get(x + n - 1) ^ get(x - 1));
    }
    
    ll k = 0;
    while ((1ll << k) <= b) k++;
    k--;
    
    ll t = 1ll << k;
    ll q = min(b - n + 2, t + 1);
     
    for (ll x = max(a, t - n - 1); x < q; x++) {
        uax(ans, get(x + n - 1) ^ get(x - 1));
    }
  
    cout << ans;
  
    return 0;
}