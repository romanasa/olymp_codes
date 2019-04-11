#include <bits/stdc++.h>    
 
#define forn(i, n) for(int i = 0; i < n; ++i)
#define fornn(i, q, n) for(int i = q; i < n; ++i)
#define X first
#define Y second
#define all(v) (v.begin(), v.end())
#define pb push_back
#define mp make_pair
#define ll long long
#define ld long double
#define ull unsigned long long
#define pii pair<int, int>
#define vi vector<int>
 
using namespace std;

const int inf = 1e9 + 7;
const ll linf = (ll)1e18 + 7;

const int dd = 1e5 + 7;

ll p;
                
ll get(ll l, ll r) {
	ll lq, rq = r / p * p;
	if (l % p == 0)
		lq = l;
	else
		lq = ((l / p) + 1) * p;

	return max(0ll, rq / p - lq / p + 1);
}

ll L[dd], R[dd];

double ans = 0;

double add(ll a, ll b) {
	return (a * 1.0 / b) * 1000;
}

int main() {
	int n;

	cin >> n >> p;
	forn(i, n)
		cin >> L[i] >> R[i];
	           
	forn(i, n) {
		
		int t = (i - 1 + n) % n;

		double a0 = get(L[t], R[t]);
		double b0 = R[t] - L[t] + 1;
        
        t = i;
                                              
		double a1 = get(L[t], R[t]);
		double b1 = R[t] - L[t] + 1;               

        t = (i + 1) % n;
                                              
		double a2 = get(L[t], R[t]);
		double b2 = R[t] - L[t] + 1;

		ans += (a0 / b0 + a1 / b1 + a2 / b2) * 1000;
    }

    printf("%.10f", ans);
	return 0;
}