#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

const int dd = (int)2e5 + 7;
unordered_map<ll, vector<int> > A;
unordered_map<ll, int> sum;
set<pair<int, ll> > S[3];
set<pair<int, ll> > T;

set<pair<int, ll> >::iterator nxt(set<pair<int, ll>>::iterator it, set<pair<int, ll> > &s) {
	if (++it == s.end()) it = s.begin();
	return it;
}

set<pair<int, ll> >::iterator prv(set<pair<int, ll>>::iterator it, set<pair<int, ll> > &s) {
	if (it == s.begin()) it = s.end();
	return --it;
}

int calc(ll id, int tp) {
	
	auto it = S[tp].find({ A[id][tp], id });
	auto pr = prv(it, S[tp]);
	auto nx = nxt(it, S[tp]);
	
	int q = nx->first - pr->first;
	if (q <= 0) q += 360;
	if (it->first == pr->first || it->first == nx->first) q = 0;
	return q;
}

int main() {
	int n; cin >> n;
	
	for (int i = 0; i < n; i++) {
		int a, b, c;
		ll id;
		cin >> a >> b >> c >> id;
		A[-id] = { a, b, c };
		
		for (int j = 0; j < 3; j++) S[j].insert({ A[-id][j], -id });
	}
	
	for (auto c : A) {
		for (int j = 0; j < 3; j++) {
			sum[c.first] += calc(c.first, j);
		}
		T.insert({ sum[c.first], c.first });
	}
	
	if (n == 1) {
		cout << -T.begin()->second << "\n";
		return 0;
	}
	
	for (int i = 0; i < n - 2; i++) {
		
		ll id = T.begin()->second;
		T.erase(T.begin());
		
		for (int j = 0; j < 3; j++) {
			auto it = S[j].find({ A[id][j], id });
			auto pr = prv(it, S[j])->second;
			auto nx = nxt(it, S[j])->second;
			
			assert(pr != nx);
			
			T.erase({ sum[pr], pr });
			T.erase({ sum[nx], nx });
			
			sum[pr] -= calc(pr, j);
			sum[nx] -= calc(nx, j);
			S[j].erase(it);
			sum[pr] += calc(pr, j);
			sum[nx] += calc(nx, j);
			T.insert({ sum[pr], pr });
			T.insert({ sum[nx], nx });
		}
		cout << -id << "\n";
	}
	ll a = T.begin()->second;
	ll b = T.rbegin()->second;
	cout << -min(a, b) << "\n" << -max(a, b) << "\n";
	
	
	return 0;
}