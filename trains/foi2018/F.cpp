#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

int main() {
	int n, k;
	cin >> n >> k;
	
	vector<int> a(n);
	for (int i = 0; i < n; i++) cin >> a[i];
	
	sort(a.begin(), a.end());
	
	if (k == 1) {
		if (accumulate(a.begin(), a.end(), 0) % 2 == 0) {
			cout << "NO\n";
		} else {
			cout << "YES\n";
			cout << "TAKE " << a[0] << " 1\n";
			cout << "KEEP 1\n";
			cout << "END\n";
		}
		return 0;
	}
	
	vector<int> cnt(543);
	for (int x : a) cnt[x]++;
	
	
	vector<int> T;
	for (int i = 1; i < 543; i++) if (cnt[i] & 1) {
		T.push_back(i);
	}
	
	if (T.empty()) cout << "NO\n", exit(0);
	sort(T.rbegin(), T.rend());
	
	cout << "YES\n";
	cout << "TAKE " << T[0] << " " << T[0] << "\n";
	
	vector<pair<int, int> > res;
	int q = T[0];
	
	for (int i = 1; i < (int)T.size(); i += 2) {
		if (i + 1 < (int)T.size()) res.push_back({ T[i + 1], T[i] - T[i + 1] }), q -= (T[i] - T[i + 1]);
		else res.push_back({ 0, T[i] }), q -= T[i];
	}
	
	while (q > k) {
		res.push_back({ 0, 1 });
		res.push_back({ 0, 1 });
		q -= 2;	
	}
	cout << "KEEP " << q << "\n";
	for (auto c : res) cout << "ADD " << c.first << " " << c.second << "\n";
	cout << "END\n";
	
	return 0;
}