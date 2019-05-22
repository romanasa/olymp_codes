#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <cstring>
#include <queue>
#include <string>

using namespace std;

int solve();

typedef long long ll;

int main() {
#ifdef ROII
	//freopen("input.txt", "r", stdin), freopen("output.txt", "w", stdout);
#endif
	solve();
}

int ask(int l, int r) {
	cout << "? " << l + 1 << " " << r + 1 << endl;
	string s;
	cin >> s;
	return (s == "Yes");
}

int solve() {
	int n;
	cin >> n;

	vector<int> st;
	string ans(n, '-');
	for (int i = 0; i < n; i++) {
		if (st.empty()) {
			st.push_back(i);
			continue;
		}
		int t = ask(st.back(), i);
		if (t) {
			ans[st.back()] = '(', ans[i] = ')';
			st.pop_back();
		} else {
			st.push_back(i);
		}
	}
	cout << "! " << ans << endl;
	return 0;
}