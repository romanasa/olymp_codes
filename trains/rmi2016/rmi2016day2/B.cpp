#include <iostream>
#include <vector>
#include <cstring>
#include <map>
#include <algorithm>
#include <string>
#include <unordered_map>

#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

typedef long long ll;

using namespace std;

const int dd = (int)4e5 + 7;

int lcp[dd], A[dd];
int st[dd], ind[dd], sz;
int nxt[dd], prv[dd];
int n;

int col[dd];
pair<int, int> S[dd];
pair<pair<int, int>, int> J[dd], tmp[dd];

inline int check(int x) { return x >= n ? x - n : x; }

int cnt[dd];

void mysort() {
	memset(cnt, 0, sizeof(cnt));
	for (int i = 0; i < n; i++) cnt[J[i].first.second + 1]++;
	for (int i = 1; i < dd; i++) cnt[i] += cnt[i - 1];
	for (int i = 0; i < n; i++) tmp[cnt[J[i].first.second]++] = J[i];
	
	memset(cnt, 0, sizeof(cnt));
	for (int i = 0; i < n; i++) cnt[tmp[i].first.first + 1]++;
	for (int i = 1; i < dd; i++) cnt[i] += cnt[i - 1];
	for (int i = 0; i < n; i++) J[cnt[tmp[i].first.first]++] = tmp[i];
}

void build(string s) {
	s += (char)0;
	n = (int)s.size();
	
	for (int i = 0; i < n; i++) S[i] = { s[i], i };
	sort(S, S + n);
	
	int c = 0;
	for (int i = 0; i < n; i++) {
		if (i && S[i - 1].first != S[i].first) c++;
		col[S[i].second] = c;
	}

	for (int L = 1; L <= n; L *= 2) {
		for (int i = 0; i < n; i++) {
			J[i] = make_pair( make_pair( col[i], col[check(i + L)] ), i );
		}	
		mysort();
		int c = 0;
		for (int i = 0; i < n; i++) {
			if (i && (J[i - 1].first.first != J[i].first.first || J[i - 1].first.second != J[i].first.second)) c++;
			col[J[i].second] = c;
		}
	}
	
	for (int i = 0; i < n; i++) A[col[i]] = i;
	
	int z = 0;
	
	for (int i = 0; i < n; i++) {
		int j = col[i];
		if (j + 1 == n) continue;
		int t = A[j + 1];
		while (t + z < n && i + z < n && s[t + z] == s[i + z] && s[t + z] != '$') z++;
		lcp[j] = z;
		if (z > 0) z--;
	}
	
	fill(nxt, nxt + n, n - 1);
	
	for (int i = n - 2; i >= 0; i--) {
		while (sz && st[sz - 1] >= lcp[i]) sz--;
		if (sz) nxt[i] = ind[sz - 1];
		st[sz] = lcp[i], ind[sz] = i;
		sz++;
	}
	
	fill(prv, prv + n, 1);
	
	for (int i = 1; i < n; i++) {
		while (sz && st[sz - 1] >= lcp[i]) sz--;
		if (sz) prv[i] = ind[sz - 1] + 1;
		st[sz] = lcp[i], ind[sz] = i;
		sz++;
	}
}

vector<pair<int, int> > E[dd];
unordered_map<int, int> pos;

struct Fen {
	int T[dd];
	void upd(int pos, int val) {
		for (int i = pos + 1; i < dd; i += (i&-i)) T[i] += val;
	}
	int get(int pos) {
		int res = 0;
		for (int i = pos + 1; i; i -= (i&-i)) res += T[i];
		return res;
	}
	int get(int l, int r) {
		return get(r) - get(l - 1);
	}
} F;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int k;
	cin >> k;
	
	string s;
	vector<int> num;
	
	for (int it = 0; it < k; it++) {
		string cur;
		cin >> cur;
		s += cur;
		s += '$';
		for (int j = 0; j <= (int)cur.size(); j++) num.push_back(it);
	}
	
	build(s);
	
	int n = (int)s.size() + 1;
	vector<int> ans(k + 1);
	
	for (int i = 1; i < n; i++) {
		if (prv[i] <= i && i <= nxt[i]) {
			E[nxt[i]].push_back({ prv[i], lcp[i] });
		}
	}
	
	for (int i = 1; i < n; i++) {
		if (pos.find(num[A[i]]) != pos.end()) F.upd(pos[num[A[i]]], -1);
		pos[num[A[i]]] = i;
		F.upd(i, 1);
		for (auto c : E[i]) {
			int cnt = F.get(c.first, i);
			ans[cnt] = max(ans[cnt], c.second);
		}
	}
	for (int i = k - 1; i > 1; i--) ans[i] = max(ans[i], ans[i + 1]);
	for (int i = 2; i <= k; i++) cout << ans[i] << "\n";
	return 0;
}