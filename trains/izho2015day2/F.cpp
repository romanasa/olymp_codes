#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

vector<vector<pair<int, char> > > E, ER, G, GR;

const int dd = (int)1e5 + 7;
int used[dd], comp[dd];

vector<int> J;

void dfs(int v) {
	used[v] = 1;
	for (auto c : E[v]) if (!used[c.first]) 
		dfs(c.first);
	J.push_back(v);
}

void mark(int v, int cc) {
	comp[v] = cc;
	for (auto c : ER[v]) if (comp[c.first] == -1)
		mark(c.first, cc);
}

vector<int> D;

void topsort(int v) {
	used[v] = 1;
	for (auto c : G[v]) if (!used[c.first])
		topsort(c.first);
	D.push_back(v);
}

#define TASK "magican"

int main() {
#ifndef HOME
	freopen(TASK".in", "r", stdin), freopen(TASK".out", "w", stdout);
#endif
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	
	int n, m;
	cin >> n >> m;
	
	E.resize(n);
	ER.resize(n);
	
	for (int i = 0; i < m; i++) {
		int a, b;
		char c;
		cin >> a >> b >> c;
		E[a - 1].push_back({ b - 1, c });
		ER[b - 1].push_back({ a - 1, c });
	}
	
	for (int i = 0; i < n; i++) if (!used[i])
		dfs(i);
		
	reverse(J.begin(), J.end());
	
	int cc = 0;
	fill(comp, comp + n, -1);
	for (int v : J) if (comp[v] == -1)
		mark(v, cc++);
		
	G.resize(cc);
	GR.resize(cc);
		
	vector<int> in(cc);
	
	for (int v = 0; v < n; v++) {
		for (auto c : E[v]) if (comp[v] != comp[c.first]) {
			G[comp[v]].push_back({ comp[c.first], c.second });
			GR[comp[c.first]].push_back({ comp[v], c.second });
			
			//err("%d--%c-->%d\n", comp[v], c.second, comp[c.first]);
			
			in[comp[c.first]]++;
		}
	}
	
	for (int v = 0; v < cc; v++) {
		sort(G[v].begin(), G[v].end());
		G[v].resize(unique(G[v].begin(), G[v].end()) - G[v].begin());
		sort(GR[v].begin(), GR[v].end());
		GR[v].resize(unique(GR[v].begin(), GR[v].end()) - GR[v].begin());
	}
	
	fill(used, used + cc, 0);
	//for (int i = 0; i < cc; i++) if (in[i] == 0)
	//	topsort(i);

	topsort(comp[0]);
	
	reverse(D.begin(), D.end());
	
	vector<int> len(cc), lenR(cc);

	for (int v : D) 
		for (auto c : G[v]) 
			len[c.first] = max(len[c.first], len[v] + 1);
			
	for (int i = (int)D.size() - 1; i >= 0; i--) {
		int v = D[i];
		for (auto c : GR[v]) 
			lenR[c.first] = max(lenR[c.first], lenR[v] + 1);
	}
	
	int maxlen = *max_element(len.begin(), len.end());
	
	vector<string> In(cc), Out(cc);
	
	for (int v : D) {
		for (auto c : G[v]) if (len[v] + 1 + lenR[c.first] == maxlen) {
			string cur = In[v];
			cur += c.second;
			if (In[c.first].empty()) In[c.first] = cur;
			else In[c.first] = min(In[c.first], cur);
		}
	}
	
	
	for (int i = (int)D.size() - 1; i >= 0; i--) {
		int v = D[i];
		for (auto c : GR[v]) if (len[c.first] + 1 + lenR[v] == maxlen) {
			string cur;
			cur += c.second;
			cur += Out[v];
			if (Out[c.first].empty()) Out[c.first] = cur;
			else Out[c.first] = min(Out[c.first], cur);
		}
	}
	
	string ans;
	for (int i = 0; i < cc; i++) if (In[i].size() || Out[i].size()) {
		if (ans.empty()) ans = In[i] + Out[i];
		ans = min(ans, Out[i] + In[i]);
	}
	cout << ans << "\n";
	
	/*for (int i = 0; i < cc; i++) {
		cout << i << ": ";
		cout << In[i] << ", " << Out[i] << "\n";
	}*/
	
	return 0;
}