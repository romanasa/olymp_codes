#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

ll calc(string s) {
	int n = (int)s.size();
	vector<int> P(n), S(n);
	for (int i = 0; i < n; i++) P[i] = (i ? P[i - 1] : 0) + (s[i] == 'J');
	for (int i = n - 1; i >= 0; i--) S[i] = (i + 1 < n ? S[i + 1] : 0) + (s[i] == 'I');
	ll ans = 0;
	for (int i = 0; i < n; i++) if (s[i] == 'O')
		ans += 1ll * P[i] * S[i];
	return ans;
}

ll calcO(string s) {
	int n = (int)s.size();
	vector<int> P(n), S(n);
	for (int i = 0; i < n; i++) P[i] = (i ? P[i - 1] : 0) + (s[i] == 'J');
	for (int i = n - 1; i >= 0; i--) S[i] = (i + 1 < n ? S[i + 1] : 0) + (s[i] == 'I');
	ll ans = 0, cur = 0;
	for (int i = 0; i < n; i++) if (s[i] == 'O')
		ans += 1ll * P[i] * S[i];
	for (int i = 0; i + 1 < n; i++) cur = max(cur, 1ll * P[i] * S[i + 1]);
	return ans + cur;
}

int main() {
	int n;
	cin >> n;
	string s;
	cin >> s;
	
	ll cur1 = calc(s + "I");
	ll cur2 = calc("J" + s);
	ll cur3 = calcO(s);
	cout << max({ cur1, cur2, cur3 }) << "\n";
	
	return 0;
}