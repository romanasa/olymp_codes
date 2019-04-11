#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

map<string, int> num;

vector<string> name(1, "#");
int nv = 1;

int get(string &s) {
	int &res = num[s];
	if (res > 0) return res;
	name.push_back(s);
	return res = nv++;
}

vector<int> ans;

vector<multiset<int> > E;

void dfs(int v) {
	
	while (E[v].size()) {
		int to = *E[v].begin();
		
		E[v].erase(E[v].begin());
		
		dfs(to);
	}

	ans.push_back(v);
}

#define TASK "h"

int main() {
#ifndef HOME
	freopen(TASK".in", "r", stdin), freopen(TASK".out", "w", stdout);
#endif
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	string s;
	vector<string> A;
	
	while (cin >> s) A.push_back(s);
	
	int n = (int)A.size();
	int len = (int)A[0].size();
	
	E.resize(2 * n + 5);
	vector<int> in(2 * n + 5), out(2 * n + 5);
	
	for (int i = 0; i < n; i++) {
		
		string a = string(A[i].begin(), A[i].end() - 1);
		string b = string(A[i].begin() + 1, A[i].end());
	
		E[get(a)].insert(get(b));
		out[get(a)]++;
		in[get(b)]++;
	}
	
	int start = 1;
	for (int i = 1; i < nv; i++) {
		if (out[i] > in[i]) start = i;
	}
	
	dfs(start);
	
	reverse(ans.begin(), ans.end());
	
	cout << name[ans[0]];
	for (int i = 1; i < (int)ans.size(); i++) cout << name[ans[i]].back();
	cout << "\n";
	return 0;
}