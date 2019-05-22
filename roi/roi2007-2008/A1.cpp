#include <bits/stdc++.h>
#define ll long long

using namespace std;

map<int, int> M;

int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	int n;
	cin >> n;

	string s;
	cin >> s;
	
	int p = 0;
	ll ans = 0;
	
	M[0]++;
	for (int i = 0; i < n; i++) {
		p += (s[i] == 'a' ? 1 : -1);
		ans += M[p]++;
	}  
	cout << ans;
	return 0;
}