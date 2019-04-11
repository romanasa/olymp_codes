#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

vector<int> zf(string &s) {
	int n = (int)s.size();
	
	vector<int> z(n);
	
	for (int i = 1, l = 0, r = 0; i < n; i++) {
		if (i <= r) z[i] = min(r - i + 1, z[i - l]);
		
		while (i + z[i] < n && s[i + z[i]] == s[z[i]]) z[i]++;
		
		if (i + z[i] - 1 > r)
			l = i, r = i + z[i] - 1;
	}
	return z;
}

int main() {
	string s;
	cin >> s;
	
	int n = (int)s.size() / 2;
	
	auto z1 = zf(s);
	reverse(s.begin(), s.end());
	
	auto z2 = zf(s);
	reverse(z2.begin(), z2.end());
	
	for (int i = 0; i < n + n; i++) err("%d, ", z2[i]); err("\n");
	
	vector<int> ans;
	for (int i = 0; i <= n; i++) {
		int s1 = z1[i];
		int s2 = z2[i + n - 1];
		if (s1 + s2 >= n && (i == 0 || s1) && (i == n || s2)) ans.push_back(i + 1);
		err("i = %d, s1 = %d, s2 = %d\n", i, s1, s2);
	}
	
	printf("%d\n", (int)ans.size());
	for (int x : ans) printf("%d ", x);
	
	return 0;
}