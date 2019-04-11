#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

ll A[505];
vector<ll> goodPrimes;
vector<pair<ll, int> > semiPrimes;

const ll mod = 998244353;

set<ll> S;
map<ll, int> M, X;

int main() {
	int N;
	cin >> N;
	
	for (int i = 1; i <= N; i++) cin >> A[i];
	
	
	for (int i = 1; i <= N; i++) {
		int flag = 0;
		for (int j = 4; j >= 2; j--) {
			//long long x = findRoot(A[i], j);
			
		}
		if (flag == 0) X[A[i]]++;
	}
	for (auto &x : X) semiPrimes.push_back({ x.first, x.second });
	long long ans = 1;
	
	for (int i = 0; i < semiPrimes.size(); i++) {
		for (int j = i + 1; j < semiPrimes.size(); j++) {
			ll g = __gcd(semiPrimes[i].first, semiPrimes[j].first);
			if (g > 1) {
				if (S.find(g) == S.end()) {
					goodPrimes.push_back(g);
					S.insert(g);
				}
			}
		}
	}
	for (int i = 0; i < semiPrimes.size(); i++) {
		int f = 0;
		for (auto gp : goodPrimes) {
			if (semiPrimes[i].first % gp == 0)
				M[gp] += semiPrimes[i].second, f++;
		}
		if (f == 0) {
			ans = ans * (semiPrimes[i].second + 1) * (semiPrimes[i].second + 1);
		}
		else if (f == 1)
			ans = ans * (semiPrimes[i].second + 1);
	}
	for (auto &it : M) ans = ans * (it.second + 1) % mod;
	cout << ans << "\n";

	return 0;
}