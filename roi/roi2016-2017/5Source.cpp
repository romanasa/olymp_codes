#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <vector>
#include <map>
#include <set>
#include <string>
#include <cstring>
#include <queue>

using namespace std;
typedef long long ll;

int solve();

#define TASK "storage"

int main() {
#ifdef ROII
	freopen("input.txt", "r", stdin), freopen("output.txt", "w", stdout);
#else
	freopen(TASK".in", "r", stdin), freopen(TASK".out", "w", stdout);
#endif
	solve();
}

string rev(string s) {
	string t;
	for (char c : s) t += (c == '+' ? '-' : '+');
	return t;
}

bool check(string s) {
	int n = (int)s.size();
	vector<pair<int, char> > T;
	for (int i = 0; i < n; i++) {
		if (T.empty() || T.back().second != s[i])
			T.push_back({ 1, s[i] });
		else
			T.back().first++;
	}

	vector<pair<int, char> > st;
	for (auto c : T) {
		if (c.second == '+') {
			while (st.size()) {
				if (st.back().second == '+') c.first += st.back().first, st.pop_back();
				else {
					if (st.back().first < c.first) {
						c.first += st.back().first;
						st.pop_back();
					} else {
						break;
					}
				}
			}
			st.push_back(c);
		} else {
			if (st.size() && st.back().second == '+' && st.back().first > c.first) {
				int x = c.first;

				c = st.back();
				st.pop_back();

				c.first += x;

				while (st.size()) {
					if (st.back().second == '+') c.first += st.back().first, st.pop_back();
					else {
						if (st.back().first < c.first) {
							c.first += st.back().first;
							st.pop_back();
						} else {
							break;
						}
					}
				}
				st.push_back(c);

			} else {
				st.push_back(c);
			}
		}
	}
	return (st[0].second == '+' && st[0].first == n);
}

bool get(string s, string t) {

	vector<pair<int, char> > T;
	for (char c : t) {
		if (T.empty() || T.back().second != c)
			T.push_back({ 1, c });
		else
			T.back().first++;
	}

	int l = 0;
	for (auto c : T) {
		int r = l + c.first - 1;

		if (r + 1 < (int)s.size() && s[r] != c.second && s[r + 1] != c.second) return false;
		if (l - 1 >= 0 && s[l] != c.second && s[l - 1] != c.second) return false;

		string q(s.begin() + l, s.begin() + r + 1);

		if (c.second == '-') q = rev(q);

		if (!check(q)) return false;

		l += c.first;
	}
	return true;
}

int solve() {
	int test;
	cin >> test;

	while (test--) {

		string s, t;
		cin >> s >> t;
		puts(get(s, t) ? "Yes" : "No");
	}
	return 0;
}