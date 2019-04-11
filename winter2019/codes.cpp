#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;


vector <string> gen(vector<string> prev, vector<char>digits) {
vector<string> next;
for ( int i = 0; i < digits.size(); i++) {
if (i%2 == 0){
for (int j = 0; j < prev.size(); j++) {
next.push_back(digits[i] + prev[j]);
}
} else {
for ( int j = prev.size()-1; j >= 0; j--) {
next.push_back(digits[i] + prev[j]);
}
}
}
 return next ;
}

int sum(string s) {
	int res = 0;
	for (char c : s) res += (c - '0');
	return res;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int n, k, a, b;
	cin >> n >> k >> a >> b;
	a--, b--;
	
	vector<char> digits(n);
	for (int i = 0; i < n; i++) cin >> digits[i];
	
	vector<string> cur(n);
	for (int i = 0; i < n; i++) cur[i] += digits[i];
	
	for (int it = 1; it < k; it++) {
		cur = gen(cur, digits);
	}
	cout << *max_element(cur.begin() + a, cur.begin() + b + 1) << " ";
	
	int ans = 0;
	for (int i = a; i + 1 <= b; i++) {
		ans = max(ans, abs(sum(cur[i + 1]) - sum(cur[i])));
	}
	cout << ans << "\n";
	
	return 0;
}