#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

void no() { puts("-1"); exit(0); }

struct req { 
	ll x; int tp, ind; 
	bool operator < (req b) const {
		if (x != b.x) return x < b.x;
		if (tp != b.tp) return tp < b.tp;
		return ind < b.ind;
	}
};

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	int n, k;
	cin >> n >> k;
	
	ll sum = 0;
	
	vector<ll> a(n);
	for (int i = 0; i < n; i++) {
		cin >> a[i];
		sum += a[i];
	}
	
	if (sum % k) no();
	if (*max_element(a.begin(), a.end()) > sum / k) no();

	vector<req> E;	
	
	ll cur = 1;
	for (int i = 0; i < n; i++) {
		if (cur + a[i] - 1 <= sum / k) {
			E.push_back({ cur, 0, i });
			E.push_back({ cur + a[i] - 1, 1, i });
			cur += a[i];
			if (cur > sum / k) cur -= sum / k;
		} else {
			
			if (cur <= sum / k) {
				E.push_back({ cur, 0, i });
				E.push_back({ sum / k, 1, i });
			}
			
			cur = a[i] - (sum / k - cur + 1);
			E.push_back({ 1, 0, i });
			E.push_back({ cur, 1, i });
			
			cur++;
		}
	}
	
	sort(E.begin(), E.end());
	
	vector<pair<ll, vector<int> > > ans;
	set<int> S;
	
	//err("E = "); for (auto c : E) err("(%I64d, %d, %d), ", c.x, c.tp, c.ind); err("\n");
	
	for (int i = 0; i < (int)E.size(); i++) {
		auto c = E[i];
		
		if (c.tp == 0) S.insert(c.ind);
		
		if (c.tp == 1) {
			if (i && (E[i - 1].tp == 0 || E[i - 1].x < c.x)) {	
				vector<int> cur;
				for (auto x : S) cur.push_back(x);
				ans.push_back({ c.x - E[i - 1].x + 1, cur });
			}
			S.erase(c.ind);
		}	
	}
	
	cout << ans.size() << "\n";
	for (auto c : ans) {
		cout << c.first << " ";
		for (auto x : c.second) cout << x + 1 << " ";
		cout << "\n";
	}
	
	
	return 0;
}