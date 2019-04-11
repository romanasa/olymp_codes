#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

const int dd = (int)1e5 + 7;
int go[dd][31];

int nv = 1;
void add(string s) {
	int cur = 0;
	for (char c : s) {
		if (go[cur][c - 'a'] == -1)
			go[cur][c - 'a'] = nv++;
		cur = go[cur][c - 'a'];
	}
}

#define TASK "trie"

int main() {
#ifndef HOME
	freopen(TASK".in", "r", stdin), freopen(TASK".out", "w", stdout);
#endif
	for (int i = 0; i < dd; i++) fill(go[i], go[i] + 31, -1);
	
	string s;
	cin >> s;
	
	int n = (int)s.size();
	
	for (int i = 0; i < n; i++) {
		string cur;
		for (int j = i; j < n; j++) {
			cur += s[j];
			add(cur);
		}
	}
	
	int cnt = 0;
	for (int i = 0; i < nv; i++)
		for (int j = 0; j < 31; j++)
			cnt += (go[i][j] != -1);
			
	cout << nv << " " << cnt << "\n";
	for (int i = 0; i < nv; i++) {
		for (int j = 0; j < 31; j++) {
			if (go[i][j] == -1) continue;
			cout << i + 1 << " " << go[i][j] + 1 << " " << (char)('a' + j) << "\n";
		}
	}
	return 0;
}