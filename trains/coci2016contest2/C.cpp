#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

int main() {
	int n;
	cin >> n;
	
	ll s = 0;
	
	vector<int> A(n);
	
	for (int i = 0; i < n; i++) {
		cin >> A[i];
		s += A[i];
	}
	
	ll c = 0;
	int ind = -1;
	
	for (int i = 0; i < n; i++) {
		if (2 * (c + A[i]) == s) {
			ind = i + 1;
			break;
		}
		c += A[i];
	}
	
	int ans = n - 1;
	
	if (ind != -1) {
		
		ll cs = 0;
		
		vector<ll> T1, T2;
		for (int i = ind - 1; i >= 0; i--) cs += A[i], T1.push_back(cs);
		
		cs = 0;
		for (int i = ind; i < n; i++) cs += A[i], T2.push_back(cs);
		
		
		int cnt = 0, j = 0;
		for (ll x : T1) {
			while (j < (int)T2.size() && T2[j] < x) j++;
			if (j < (int)T2.size() && T2[j] == x) cnt++;
		}
		ans = min(ans, (int)T1.size() + (int)T2.size() - 2 * cnt);
	}
	
	
	vector<ll> T1, T2;
	int j = n - 1;
	int cnt = 0;
	c = 0;
	
	for (int i = 0; i < n; i++) {
		c += A[i];
		T1.push_back(c);
		
		while ((T2.empty() || T2.back() < T1.back()) && j > i) {
			T2.push_back((T2.size() ? T2.back() : 0ll) + A[j]);
			j--;
		}
		
		//err("i = %d, j = %d\n", i, j);
		if (j <= i) break;
		
		if (T2.size() && T1.size() && T1.back() == T2.back()) {
			//err("tut\n");
			cnt++;
			ans = min(ans, (int)T1.size() + (int)T2.size() - 2 * cnt + j - i - 1);
		}
	}
	cout << ans << "\n";
	return 0;
}