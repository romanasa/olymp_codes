#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

vector<int> cnt = { 0, 2, 5, 5, 4, 5, 6, 3, 7, 6 };

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int n, m;
	cin >> n >> m;
	
	
	vector<int> A(m);
	for (int i = 0; i < m; i++) cin >> A[i];
	
	sort(A.rbegin(), A.rend());
	
	vector<int> p(n + 1, -1);
	
	auto calc = [&](vector<int> &P) {
		P.assign(n + 1, -1);
		P[0] = 0;
		for (int i = 0; i < n; i++) if (P[i] != -1) 
			for (int c : A) if (i + cnt[c] <= n && P[i + cnt[c]] < P[i] + 1)
				P[i + cnt[c]] = P[i] + 1;
		return P;
	};
	
	vector<int> S, P;
	calc(S);
	calc(P), reverse(P.begin(), P.end());
	
	vector<int> Q;
	Q.push_back(0);
	
	while (Q.size()) {
	
		int cur = -1;
		for (int w : Q) {
			for (int c : A) if (w + cnt[c] <= n && S[w] + P[w + cnt[c]] + 1 == S[n])
				cur = max(cur, c);
		}
		if (cur == -1) break;
			
		set<int> SS;
		for (int w : Q) {
			for (int c : A) if (c == cur && w + cnt[c] <= n && S[w] + P[w + cnt[c]] + 1 == S[n])
				p[w + cnt[c]] = c, SS.insert(w + cnt[c]);
		}
		Q.clear();
		for (auto c : SS) Q.push_back(c);
	}
	
	string ans;
	for (int i = n; i; i -= cnt[p[i]]) ans += (char)('0' + p[i]);
	reverse(ans.begin(), ans.end());
	cout << ans << "\n";
	return 0;
}