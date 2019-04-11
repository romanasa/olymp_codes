#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

#define TASK "base-i-1"

int main() {
#ifndef HOME
	freopen(TASK".in", "r", stdin), freopen(TASK".out", "w", stdout);
#endif
	vector<pair<int, int> > T;
	T.push_back({ 1, 0 });
	
	int n = 15;
	for (int i = 0; i + 1 < n; i++) {
		int a = T.back().first;
		int b = T.back().second;
		T.push_back({ -a - b, a - b });
	}
	
	int sz = (int)1e3;
	
	vector<string> ans(sz);
	for (int msk = 0; msk < (1 << n); msk++) {
		int ca = 0, cb = 0;
		for (int i = 0; i < n; i++) if ((msk >> i) & 1)
			ca += T[i].first, cb += T[i].second;
			
		if (cb == 0 && 0 <= ca && ca < (int)ans.size() && ans[ca].empty()) {
			string cur;
			for (int i = 0; i < n; i++) cur += (char)('0' + ((msk >> i) & 1));
			//reverse(cur.begin(), cur.end());
			ans[ca] = cur;
		}
	}
	
	for (int i = 0; i <= 20; i++) cout << ans[i] << "\n";
	return 0;
	
	string A, B, C;
	cin >> A >> B;
	
	vector<int> a, b;
	
	for (int i = (int)A.size() - 1; i >= 0; i--) a.push_back(A[i] - '0');
	for (int i = (int)B.size() - 1; i >= 0; i--) b.push_back(B[i] - '0');
	
	vector<int> c(a.size() + b.size());
	vector<int> res;
	
	for (int i = 0; i < (int)c.size(); i++) {
	
		int curv = (i < (int)a.size() ? a[i] : 0) + (i < (int)b.size() ? b[i] : 0) + c[i];
		err("i = %d\n", i);	
		err("a = "); for (int x : a) err("%d, ", x); err("\n");
		err("b = "); for (int x : b) err("%d, ", x); err("\n");
		err("c = "); for (int x : c) err("%d, ", x); err("\n");
		
		if (i > 1000) break;
		
		if (curv <= 1) {
			res.push_back(curv);
		} else {
			err("curv = %d\n", curv);
			string cur = ans[curv];
			res.push_back(cur[0] - '0');
			
			while (c.size() < i + (int)cur.size()) c.push_back(0);
			
			for (int t = 1; t < (int)cur.size(); t++) {
				c[i + t] += (cur[t] - '0');
			}
		}
	}
	
	while (res.size() > 1 && res.back() == 0) res.pop_back();
	reverse(res.begin(), res.end());
	for (int x : res) cout << x;
	cout << "\n";
	
	return 0;
}