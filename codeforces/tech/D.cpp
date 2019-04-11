#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

const int dd = (int)1e5 + 7;

int in[dd];
int used[dd];
int nxt[31];
int was[31];

void no()  {
    cout << "NO\n";
    exit(0);
}

vector<vector<int> > G;
vector<int> ans;

void dfs(int v) {
    ans.push_back(v);
    used[v] = 1;
    
    int to = nxt[v];
    if (to != -1) {
        if (used[to] == 1) no();
        if (!used[to]) {
            dfs(to);
        }
    }
    used[v] = 2;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;

    fill(nxt, nxt + 31, -1);
    
    vector<string> A(n);

    for (int i = 0; i < n; i++) cin >> A[i];

    for (int i = 0; i < n; i++) {
        string s = A[i];
        map<int, int> m;
        for (int j = (int)s.size() - 1; j >= 0; j--) {
        	if (m.count(s[j])) no();
        	m[s[j]] = j;
        	was[s[j] - 'a'] = 1;
        }
        for (int j = 0; j + 1 < (int)s.size(); j++) if (nxt[s[j] - 'a'] == -1) {
        	nxt[s[j] - 'a'] = s[j + 1] - 'a';
        	in[s[j + 1] - 'a']++;
        	if (in[s[j + 1] - 'a'] > 1) no();
        }
    }
    
    for (int i = 0; i < n; i++) {
    	string s = A[i];
    	for (int j = 0; j + 1 < (int)s.size(); j++) {
    		if (nxt[s[j] - 'a'] != s[j + 1] - 'a') no();
    	}
    }

	for (int i = 0; i < 31; i++) if (!used[i] && !in[i] && was[i]) {
		dfs(i);
	}
	
	for (int i = 0; i < 31; i++) if (was[i]) {
		int ok = 0;
		for (int x : ans) if (x == i) ok = 1;
		if (!ok) no();
	}
	
	if (ans.empty()) no();
	for (int x : ans) cout << (char)('a' + x);
    return 0;
}