#include <bits/stdc++.h>
#define err(...) //fprintf(stderr, __VA_ARGS__), fflush(stderr)

typedef long long ll;

using namespace std;

const int dd = (int)2e5 + 7;

int n;
int len[dd];

bool check(int c) {
	vector<pair<int, int>> st;
	
	st.emplace_back(-1, 0);
	
	auto add = [&](int val, int cnt) {	
		if (cnt <= 0) return;
		if (st.size() && st.back().first == val) st.back().second += cnt;
		else st.emplace_back(val, st.back().second + cnt);
	};
	
	for (int i = 0; i < n; i++) {
		if (len[i] > st.back().second) {
			add(0, len[i] - st.back().second);
		} else {
			int last = -1;
			while (st.back().second >= len[i]) {
				last = st.back().first;
				st.pop_back();
			}
			
			int was = 0;
			int clen = -1;
			
			while (st.size() && last == c - 1) {
				last = st.back().first;
				was = 1, clen = st.back().second;
				st.pop_back();
			}
				
			if (st.empty()) return false;
			
			if (was) {
				add(last, clen - st.back().second - 1);
				add(last + 1, 1);
				add(0, len[i] - st.back().second);
			} else {
				add(last, len[i] - st.back().second - 1);
				add(last + 1, 1);
			}
		}
	}
	return true;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n;
	for (int i = 0; i < n; i++) cin >> len[i];
	
	int l = 0, r = (int)1e9 + 7;
	while (r - l > 1) {
		int m = (l + r) / 2;
		
		if (check(m)) r = m;
		else l = m;
	}
	cout << r << "\n";
	return 0;
}
