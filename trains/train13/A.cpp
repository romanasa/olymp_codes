#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

const int dd = (int)1e5 + 1;
const int maxN = (int)1e6 + 1;
const int len = 9;

int A[dd];
int go[11][maxN];
ll cnt[maxN];
int root, nv = 1;

void add(string &s) {
	int cur = root;
	for (char &c : s) {
		if (go[c - '0'][cur] == -1) go[c - '0'][cur] = nv++;
		cur = go[c - '0'][cur];
	}
}

int tmp;

void dfs(int cur, string &s, int pos) {
	if (pos == len) {
		cnt[cur]++;
		return;
	}
	for (int i = 0; i < s[pos] - '0'; i++) if ((tmp = go[i][cur]) != -1) 
		cnt[tmp]++;
	
	if ((tmp = go[s[pos] - '0'][cur]) != -1) 
		dfs(tmp, s, pos + 1);
	
	if ((tmp = go[10][cur]) != -1) {
		cnt[tmp] += (s[pos] - '0');
		dfs(tmp, s, pos + 1);
	}
}

int T[10];

ll get(string &s) {
	int cur = root;
	ll res = 0;

	int iT = 0;	
	for (char &c : s) {
		cur = go[c - '0'][cur];
		T[iT++] = cur;
	}
	
	ll p = 1;
	for (int i = len - 1; i >= 0; i--) {
		res += cnt[T[i]] * p;
		if (s[i] == '0' + 10) p *= 10;
	}
	return res;
}

#define TASK "queries"

int main() {
#ifndef HOME
	freopen(TASK".in", "r", stdin), freopen(TASK".out", "w", stdout);
#endif
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	for (int i = 0; i < 11; i++) fill(go[i], go[i] + maxN, -1);
	int n, m;
	cin >> n >> m;
	
	vector<string> A(n), B(m);
	
	for (int i = 0; i < n; i++) {
		cin >> A[i];
		A[i] = string(len - (int)A[i].size(), '0') + A[i];
		//cout << A[i] << "\n";
	}

	for (int i = 0; i < m; i++) {
		cin >> B[i];
		B[i] = string(len - (int)B[i].size(), '0') + B[i];
		for (char &c : B[i]) if (c == '?') c = '0' + 10;
		add(B[i]);
		//cout << B[i] << "\n";
	}
	
	for (int i = 0; i < n; i++) dfs(root, A[i], 0);
	for (int i = 0; i < m; i++) cout << get(B[i]) << "\n";
	
	return 0;
}