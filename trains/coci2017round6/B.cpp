#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

struct react {
	vector<int> A, B;
};

const int dd = (int)1e5 + 7;
vector<int> X[dd];

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int n, m;
	cin >> n >> m;
	
	vector<int> A(m), used(n + 1);
	for (int i = 0; i < m; i++) {
		cin >> A[i];
		used[A[i]] = 1;
	}
	
	int k;
	cin >> k;
	
	vector<react> T(k);
	vector<int> need(k);
	
	for (int i = 0; i < k; i++) {
		int l, r;
		cin >> l >> r;
		
		for (int j = 0; j < l; j++) {
			int x;
			cin >> x;
			X[x].push_back(i);			
		}
		need[i] = l;
		for (int j = 0; j < r; j++) {
			int x;
			cin >> x;
			T[i].B.push_back(x);
		}
	}
	
	queue<int> q;
	for (int i = 0; i <= n; i++) if (used[i])
		q.push(i);
		
		
	while (q.size()) {
		int v = q.front();
		q.pop();
		
		for (int i : X[v]) {
			need[i]--;
			if (need[i] == 0) {
				for (int x : T[i].B) if (!used[x]) q.push(x), used[x] = 1;
			}
		}
	}
		
	int ans = 0;
	for (int i = 1; i <= n; i++) if (used[i] > 0) ans++;
	
	cout << ans << "\n";
	for (int i = 1; i <= n; i++) if (used[i] > 0) cout << i << " ";
	cout << "\n";
	
	return 0;
}