#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

int main() {
#ifndef HOME
	freopen("input.txt", "r", stdin), freopen("output.txt", "w", stdout);
#endif
	int n;
	cin >> n;
	vector<int> A(n);
	for (int i = 0; i < n; i++) cin >> A[i];
	
	vector<int> st, ind, nxt(n), prv(n);
	for (int i = n - 1; i >= 0; i--) {
		
		while (st.size() && st.back() <= A[i]) st.pop_back(), ind.pop_back();
		nxt[i] = (st.size() ? ind.back() - i : (int)1e9);
		st.push_back(A[i]);
		ind.push_back(i);
	}
	
	st.clear(), ind.clear();
	for (int i = 0; i < n; i++) {	
		while (st.size() && st.back() <= A[i]) st.pop_back(), ind.pop_back();
		prv[i] = (st.size() ? i - ind.back() : (int)1e9);
		st.push_back(A[i]);
		ind.push_back(i);
	}
	
	for (int i = 0; i < n; i++) {
		int cur = min(nxt[i], prv[i]);
		cout << (cur == (int)1e9 ? 0 : cur) << " ";
	}
	return 0;
}