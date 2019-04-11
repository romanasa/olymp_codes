#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

const int dd = (int)4007;
int G[dd][dd];
int cur[dd], ind;
string s;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int n;
	cin >> n;
	
	getline(cin, s);
	for (int i = 0; i < n; i++) {
		getline(cin, s);
		for (int j = 0; j < i; j++) {
			if (s[j] == '1') G[j][i] = G[i][j] = 1;
		}
	}
	
	deque<int> q;
	
	for (int i = 0; i < n; i++) {
		q.push_back(i);
	}
	
	for (int k = 0; k < n * (n - 1); k++) {
		if (!G[q[0]][q[1]]) {
			int i = 2;
			while (!G[q[0]][q[i]] || !G[q[1]][q[i + 1]]) i++;
			
			for (int j = 0; j <= i; j++) cur[j] = q.front(), q.pop_front();
			for (int j = 1; j <= i; j++) q.push_front(cur[j]);
			q.push_front(cur[0]);
		}
		q.push_back(q.front());
		q.pop_front();
	}
	for (int x : q) cout << x + 1 << " ";
	return 0;
}