#include <bits/stdc++.h>
#define err(...) //fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

const int dd = (int)5e5 + 7;

vector<vector<pair<int, int> > > E;
int need[dd], S[dd];
ll A[dd], B[dd];
ll ans[dd];

void dfs(int v, int pr = -1) {
	A[v] = B[v] = (ll)1e18, S[v] = need[v];
	
	ll sum = 0, mx = -(ll)1e18;
	
	for (auto c : E[v]) if (c.first != pr) {
		dfs(c.first, v);
		if (S[c.first]) {
			S[v] = 1;
			sum += B[c.first] + 2 * c.second;
			mx = max(mx, (B[c.first] + 2 * c.second) - (A[c.first] + c.second));
		}
	}
	if (mx == -(ll)1e18) A[v] = B[v] = 0;
	else A[v] = sum - mx, B[v] = sum;
}

void calc(int v, int pr, int w, ll pa, ll pb, int ps) {
	
	err("v = %d, pa = %I64d, pb = %I64d, ps = %d\n", v, pa, pb, ps);

	ll sum = 0, mx = -(ll)1e18;
	int s = 0;
	
	multiset<ll> T;
	
	for (auto c : E[v]) if (c.first != pr) {
		if (S[c.first]) {
			s++, sum += B[c.first] + 2 * c.second;
			T.insert((B[c.first] + 2 * c.second) - (A[c.first] + c.second));
		}
	}
	
	if (pr != -1 && ps) {
		s++, sum += pb + 2 * w;
		T.insert((pb + 2 * w) - (pa + w));
	}
	
	if (T.empty()) ans[v] = 0;
	else ans[v] = sum - *T.rbegin();
	
	
	for (auto c : E[v]) if (c.first != pr) {
		
		ll x = (B[c.first] + 2 * c.second) - (A[c.first] + c.second);
	
		ll pa, pb;
		int ps;
		
		if (S[c.first]) {
			T.erase(T.find(x));
			sum -= (B[c.first] + 2 * c.second);
		}	
    	
    	pa = (T.size() ? sum - *T.rbegin() : 0);
    	pb = sum;
    	ps = s - S[c.first];
		
		calc(c.first, v, c.second, pa, pb, ps);
		
		if (S[c.first]) {
			sum += (B[c.first] + 2 * c.second);
			T.insert(x);
		}
	}
}

int main() {
	int n, k;
	scanf("%d %d", &n, &k);
	
	E.resize(n);
	
	for (int i = 0; i < n - 1; i++) {
		int a, b, c;
		scanf("%d %d %d", &a, &b, &c);
		E[a - 1].push_back({ b - 1, c });
		E[b - 1].push_back({ a - 1, c });
	}
	
	
	for (int i = 0; i < k; i++) {
		int v;
		scanf("%d", &v);
		need[v - 1] = 1;
	}
	
	dfs(0);
	calc(0, -1, -1, 0, 0, 0);
	
	for (int i = 0; i < n; i++) printf("%lld\n", ans[i]);
	return 0;
}