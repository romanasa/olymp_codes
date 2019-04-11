#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;


const int dd = (int)1e6 + 7;
unordered_map<string, vector<string> > D;

map<string, vector<string>> dp;

vector<string> go(string &s) {

	if (dp.count(s)) return dp[s];

	vector<string> ans;
	for (int i = 0; i < (int)s.size(); i++) {
		string t = s;
		t.erase(t.begin() + i);
		
		sort(t.begin(), t.end());
		
		if (D.count(t)) for (auto c : D[t]) {
			auto t = go(c);
			if (t.size() > ans.size()) ans = t;
		}
	}
	ans.push_back(s);
	return dp[s] = ans;
}

int main() {
	int n; cin >> n;
	vector<string> A(n);
	for (int i = 0; i < n; i++) cin >> A[i];
	
	int m;
	cin >> m;

	for (int i = 0; i < m; i++) {
		string s; cin >> s;
		string t = s;
		sort(t.begin(), t.end());
		D[t].push_back(s);
	}
	
	for (int i = 0; i < n; i++) {
		auto c = go(A[i]);
		reverse(c.begin(), c.end());
		if (c.back().size() == 1) c.push_back(".");
		
		cout << (int)c.size() << "\n";
		for (int i = 0; i < (int)c.size(); i++) {
			cout << c[i];
			if (i + 1 < (int)c.size()) cout << " -> ";
			else cout << "\n";
		}
	}
	
	
	return 0;
}