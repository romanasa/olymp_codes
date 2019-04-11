#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

const int dd = (int)2e5 + 7;
int go[dd][31];
int suf[dd], len[dd];

int nv = 1;
int root, last;

int clone(int v) {
	int cur = nv++;
	copy(go[v], go[v] + 31, go[cur]);
	return cur;
}

void add(int c) {
	int nlast = nv++;
	len[nlast] = len[last] + 1;
	
	int p = last;
	while (p != -1 && go[p][c] == -1) go[p][c] = nlast, p = suf[p];
	
	if (p == -1) {
		suf[nlast] = root;
	} else {
		int q = go[p][c];
		if (len[p] + 1 == len[q]) {
			suf[nlast] = q;
		} else {
			int r = clone(q);
			
			suf[r] = suf[q];
			suf[q] = r;
			suf[nlast] = r;
			
			len[r] = len[p] + 1;
			
			while (p != -1 && go[p][c] == q) go[p][c] = r, p = suf[p];
		}
	}
	last = nlast;
}

int main() {
	fill(suf, suf + dd, -1);
	for (int i = 0; i < dd; i++) fill(go[i], go[i] + 31, -1);
	
	string s;
	cin >> s;
	
	for (char c : s)
		add(c - 'a');
		
	int cnt = 0;
	for (int i = 0; i < nv; i++)
		for (int j = 0; j < 31; j++) if (go[i][j] != -1)
			cnt++;
			
	cout << nv << " " << cnt << "\n";
	for (int i = 0; i < nv; i++) {
		for (int j = 0; j < 31; j++) if (go[i][j] != -1) {
			cout << i + 1 << " " << go[i][j] + 1 << " " << (char)('a' + j) << "\n";
		}
	}
	vector<int> res;
	for (int t = last; t != -1; res.push_back(t), t = suf[t]);
	cout << (int)res.size() << "\n";
	for (int x : res) cout << x + 1 << " ";
	return 0;
}