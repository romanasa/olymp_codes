#include <bits/stdc++.h>
#define ll long long

using namespace std;

vector<set<int> > E;
set<pair<int, int> > S;


void go(int v) {
	while (E[v].size()) {
		int to = *E[v].begin();

		E[v].erase(E[v].find(to));
		E[to].erase(E[to].find(v));
		
		S.insert({ v, to });
		go(to);
	}
}

int solve() {

	int n, m;
	scanf("%d %d", &n, &m);
	
	S.clear();
	E.clear();
	E.resize(n + 1);
	
	for (int i = 0; i < m; i++) {
		int a, b;
		scanf("%d %d", &a, &b);
		
		E[a - 1].insert(b - 1);
		E[b - 1].insert(a - 1);
	}
	
	for (int i = 0; i < n; i++) {
		if (E[i].size() % 2) {
			E[n].insert(i);
			E[i].insert(n);
		}
	}
	
	go(n);
	
	vector<int> tin(n + 1), tout(n + 1);
	for (auto c : S) {
		tin[c.second]++;
		tout[c.first]++;
	}
	
	int t = 0;
	for (int i = 0; i < n; i++)
		if (tin[i] == tout[i])
			t++;
	printf("%d\n", t);
	for (auto c : S)
		if (c.first != n && c.second != n)
			printf("%d %d\n", c.first + 1, c.second + 1);
	return 0;
}

int main() {
	int t;
	scanf("%d", &t);
	while (t--) solve();
}