#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

vector<vector<int> > E;

const int dd = (int)2e5 + 7;

int used[dd];
int cycle;

vector<int> C;

void dfs(int v, int pr) {
	used[v] = 1;
	C.push_back(v);

	for (int to : E[v]) if (to != pr) {
		if (used[to]) {
			cycle = true;
			
			int pos = -1;
			for (int i = 0; i < (int)C.size(); i++) if (C[i] == to)
				pos = to;
			assert(pos != -1);
			
			C.erase(C.begin(), C.begin() + pos);
			return;
		}
		if (!used[to]) {
			dfs(to, v);
			if (cycle) return;
		}
	}	
	C.pop_back();
}

int diam;
ll cnt;

pair<int, int> calc(int v, int pr, int h) {
	if (E[v].size() == 1 && E[v][0] == pr) return { h, 1 };
	int a = 0, b = 1;
	
	vector<pair<int, int> > cur;
	
	for (int to : E[v]) if (to != pr && !used[to]) {
		auto c = calc(to, v, h + 1);
		cur.push_back(c);
		if (c.first > a) {
			a = c.first;
			b = c.second;
		} else if (c.first == a) {
			b += c.second;
		}
	}
	
	for (int i = 0; i < (int)cur.size(); i++) {
		for (int j = 0; j < i; j++) {
			int len = cur[i].first + cur[j].first;
			ll c = cur[i].second * cur[j].second;

			if (len > diam) diam = len, cnt = c;
			else if (len == diam) cnt += c;
		}
	}
		
	return { a, b };
}

#define TASK "shymbulak"

int main() {
#ifndef HOME
	freopen(TASK".in", "r", stdin), freopen(TASK".out", "w", stdout);
#endif
	int n;
	cin >> n;
	
	E.resize(n);
	
	for (int i = 0; i < n; i++) {
		int a, b;
		cin >> a >> b;
		E[a - 1].push_back(b - 1);
		E[b - 1].push_back(a - 1);
	}
	
	dfs(0, -1);
	
	fill(used, used + n, 0);
	for (int v : C) used[v] = 1;
	
	vector<pair<int, int> > T, G;
	
	int maxdiam = 0;
	
	for (int v : C) {
		diam = 0;
		cnt = 1;
		T.push_back(calc(v, -1, 0));
		G.push_back({ diam, cnt });
		maxdiam = max(maxdiam, diam);
	}
	
	for (int i = 0; i < (int)C.size(); i++) T.push_back(T[i]);
	
	int cc = (int)C.size();
	
	int len = 0;
	for (int i = 0; i < cc; i++) {
		for (int j = i + 1; j <= i + cc / 2; j++) 
			len = max(len, T[i].first + T[j].first + (j - i));
	}
	
	ll cnt1 = 0;
	ll cnt2 = 0;
	
	
   	for (auto c : G) if (c.first == maxdiam)
   		cnt1 += c.second;
	
	for (int i = 0; i < cc; i++) {
   		for (int j = i + 1; j <= i + cc / 2; j++) 
   			if (len == T[i].first + T[j].first + (j - i)) {
   				cnt2 += 1ll * T[i].second * T[j].second; 
   			}
   	}
	
	if (maxdiam > len) {
		cout << cnt1 << "\n";
	} else if (maxdiam == len) {
    	cout << cnt1 + cnt2 << "\n";
	} else {
		cout << cnt2 << "\n";
	}
	
	return 0;
}