#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

const int dd = (int)1e5 + 7;

int used[dd];
int cycle;

vector<vector<int> > E;
vector<int> C;

void dfs(int v, int pr) {
	used[v] = 1;
	C.push_back(v);

	for (int to : E[v]) if (to != pr) {
		if (used[to]) {
			cycle = true;
			
			int pos = -1;
			for (int i = 0; i < (int)C.size(); i++) if (C[i] == to)
				pos = i;
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


int main() {
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
	
	cout << n - (int)C.size() << "\n";
	return 0;
}