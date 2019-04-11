#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

const int dd = (int)1e3 + 7;

vector<int> E[dd][31];
int go[dd][31];
int comp[dd], term[dd], nterm[dd];
int used[dd][dd], was[dd];

#define TASK "minimization"

int main() {
#ifndef HOME
	freopen(TASK".in", "r", stdin), freopen(TASK".out", "w", stdout);
#endif
	for (int i = 0; i < dd; i++) fill(go[i], go[i] + 31, -1);
	
	int n, m, k;
	scanf("%d %d %d", &n, &m, &k);	
	
	for (int i = 0; i < k; i++) {
		int v;
		scanf("%d", &v);
		term[v - 1] = 1;
	}
	
	for (int i = 0; i < m; i++) {
		int a, b;
		char c;
		scanf("%d %d %c", &a, &b, &c);
		go[a - 1][c - 'a'] = b - 1;
		E[b - 1][c - 'a'].push_back(a - 1);
	}
	
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < 26; j++) if (go[i][j] == -1) {
			go[i][j] = n;		
			E[n][j].push_back(i);
		}
	}
	
	for (int j = 0; j < 26; j++) {
		go[n][j] = n;
		E[n][j].push_back(n);
	}
	n++;
	
	queue<pair<int, int> > q;
	
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (!used[i][j] && term[i] != term[j]) {
				used[i][j] = used[j][i] = 1;
				q.push({ i, j });
			}
		}
	}
	
	while (q.size()) {
		int v1 = q.front().first, v2 = q.front().second;
		q.pop();
		for (int j = 0; j < 26; j++) {
			for (int r : E[v1][j]) {
				for (int s : E[v2][j]) {
					if (!used[r][s]) {
						used[r][s] = used[s][r] = 1;
						q.push({ r, s });
					}
				}
			}
		}
	}
	
	/*for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			err("%d%c", used[i][j], " \n"[j == n - 1]);
		}
	}*/
	
	fill(comp, comp + n, -1);
	
	int cur = 0;
	
	for (int i = 0; i < n; i++) if (comp[i] == -1) {
		for (int j = 0; j < n; j++) if (!used[i][j]) {
			comp[j] = cur;
		}
		cur++;
	}
	
	//for (int i = 0; i < n; i++) err("comp[%d] = %d\n", i, comp[i]);
	
	vector<vector<pair<int, int> > > Q(cur);
	vector<vector<int> > QR(cur);
	
	int sz = 0;
	
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < 26; j++) {
			Q[comp[i]].push_back({ comp[go[i][j]], j });
			QR[comp[go[i][j]]].push_back(comp[i]);
		}
	}

	for (int i = 0; i < n; i++) if (term[i]) {
		nterm[comp[i]] = 1;
	}
	
	queue<int> R;
	
	for (int i = 0; i < cur; i++) if (nterm[i]) was[i] = 1, R.push(i);
	
	while (R.size()) {
		int v = R.front();
		R.pop();
		for (int to : QR[v]) {
			if (!was[to]) was[to] = 1, R.push(to);
		}
	}
	
	for (int i = 0; i < cur; i++) {
		sort(Q[i].begin(), Q[i].end());
		Q[i].resize(unique(Q[i].begin(), Q[i].end()) - Q[i].begin());
	}
	
	for (int i = 0; i < cur; i++) if (was[i]) {
		for (auto c : Q[i]) if (was[c.first]) {
			sz++;
		}
	}
	
	int kk = 0;
	for (int i = 0; i < cur; i++) kk += (nterm[i] && was[i]);
	
	printf("%d %d %d\n", accumulate(was, was + cur, 0), sz, kk);
	
	
	for (int i = 0; i < cur; i++) if (nterm[i] && was[i]) printf("%d ", i + 1); printf("\n");
	
	for (int i = 0; i < cur; i++) if (was[i]) {
		for (auto c : Q[i]) if (was[c.first]) {
			printf("%d %d %c\n", i + 1, c.first + 1, (char)('a' + c.second));
		}
	}
	
	return 0;
}