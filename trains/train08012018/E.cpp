#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

const int dd = 2007;
int used[dd];
int n, m, k;
vector<vector<int> > E;
vector<int> T;

void go(int v, int cur) {
	if (cur > k) return;
	if (used[v]) {
		go(v + 1, cur);
		return;
	}
	
	if (v == n) {
		cout << "Yes\n";
		for (int v : T) cout << v + 1 << " ";
		
		int add = k - cur;
		for (int v = 0; v < n; v++) if (!used[v]) {
			if (add == 0) break;
			cout << v + 1 << " ";
			add--;
		}
		cout << "\n";
		
		exit(0);
	}

	int c = 0;
	for (int to : E[v]) if (!used[to]++) {
   		T.push_back(to);
   		c++;
   	}
   	
   	go(v + 1, cur + c);
   	
   	for (int to : E[v]) if (--used[to] == 0) {
   		T.pop_back();
   	}

	if (c > 1) {
		used[v] = 1;
		
    	T.push_back(v);
    	go(v + 1, cur + 1);
    	T.pop_back();
    	
    	used[v] = 0;
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> m >> k;
	E.resize(n);
	
	for (int i = 0; i < m; i++) {
		int a, b;
		cin >> a >> b;
		E[a - 1].push_back(b - 1);
		E[b - 1].push_back(a - 1);
	}
	
	go(0, 0);
	
	cout << "No\n";
	
	return 0;
}