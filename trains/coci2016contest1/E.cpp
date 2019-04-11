#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

const int dd = (int)1e6 + 7;
int a[dd], p[dd], v[dd];
vector<int> T[dd];
int P[dd];

int main() {
	int n;
	cin >> n;
	
	for (int i = 0; i < n; i++) {
		cin >> a[i]; a[i]--;
	}
	
	for (int i = 0; i < n; i++) cin >> p[i];
	for (int i = 0; i < n; i++) cin >> v[i];
	
	for (int i = 0; i < n; i++) {
		P[a[i]]++;
		T[a[i]].push_back(v[i]);
	}
	
	for (int i = 1; i < n; i++) P[i] += P[i - 1];
	for (int i = 0; i < n; i++) P[i] -= i;
	
	int ind = min_element(P, P + n) - P;
	int st = (ind + 1) % n;
	
	set<int> S;
	int ans = 0;
	
	for (int itt = 0; itt < n; itt++) {
		int i = (st + itt) % n;
		for (int x : T[i]) S.insert(x);
		
		auto it = S.lower_bound(p[i]);
		if (it == S.end()) S.erase(S.begin());
		else ans++, S.erase(it);
	}
	cout << ans << "\n";
	
	return 0;
}