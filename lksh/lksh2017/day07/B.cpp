#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

const int dd = (int)1e3 + 7;

#define TASK "equivalence"

struct automaton {
	int n, m, k;
	
	vector<vector<int> > go;
	vector<int> term, used;
	
	automaton() {
		go.resize(dd);
		for (int i = 0; i < dd; i++) go[i].resize(31, -1);
		term.resize(dd), used.resize(dd);
	}
	
	void read() {
		scanf("%d %d %d", &n, &m, &k);
		for (int i = 0; i < k; i++) {
			int v;
			scanf("%d", &v);
			term[v - 1] = 1;
		}
		for (int i = 0; i < m; i++)  {
			int a, b;
			char c;
			scanf("%d %d %c", &a, &b, &c);
			go[a - 1][c - 'a'] = b - 1;
		}
	}
	
	void build() {
		for (int i = 0; i <= n; i++) {
			for (int j = 0; j < 26; j++) {
				if (go[i][j] == -1) go[i][j] = n;
			}
		}
	}
} A, B;



int main() {
#ifndef HOME
	freopen(TASK".in", "r", stdin), freopen(TASK".out", "w", stdout);
#endif
	
	A.read(), B.read();
	A.build(), B.build();
	
	queue<pair<int, int> > q;
	
	q.push({ 0, 0 });
	
	while (q.size()) {
		int v1 = q.front().first;
		int v2 = q.front().second;
		
		q.pop();
		
		if (A.term[v1] ^ B.term[v2]) return 0 * puts("NO");
		
		A.used[v1] = B.used[v2] = 1;
		
		for (int j = 0; j < 26; j++) {
			int n1 = A.go[v1][j];
			int n2 = B.go[v2][j];
			
			if (!A.used[n1] || !B.used[n2])
				q.push({ n1, n2 });
		}
		
	}
	puts("YES");
	return 0;
}