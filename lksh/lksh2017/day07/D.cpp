#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

const int dd = (int)1e5 + 7;

int go[dd][26], term[dd], classes[dd];
vector<int> ER[dd][26];

struct automaton {
	int n, m, k;

	automaton() {
		for (int i = 0; i < dd; i++) fill(go[i], go[i] + 26, -1);
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
				ER[go[i][j]][j].push_back(i);
			}
		}
		n++;
	}
	
	int findClasses() {
		vector<unordered_set<int> > P;
		
		unordered_set<int> A, B;
		for (int i = 0; i < n; i++) {
			(term[i] ? A : B).insert(i);
			classes[i] = term[i] ^ 1;
		}
		
		P.push_back(A);
		P.push_back(B);
		
		queue<pair<int, int> > Q;
		
		for (int c = 0; c < 26; c++) {
			Q.push({ 0, c });		
		}
		for (int c = 0; c < 26; c++) {
			Q.push({ 1, c });		
		}
		
		while (Q.size()) {
			int ind = Q.front().first, x = Q.front().second;
			Q.pop();
			
			unordered_map<int, unordered_set<int> > involved;
			
			for (int v : P[ind]) {
				for (auto c : ER[v][x]) {
					involved[classes[c]].insert(c);
				}
			}
			
			for (auto c : involved) {
				auto R = c.first;
				auto R1 = c.second;
				
				if (P[R].size() <= R1.size()) continue;
				
				int j = (int)P.size();	
				P.push_back(R1);
				
				for (auto v : R1) P[R].erase(v);
				
				if (P[j].size() > P[R].size()) swap(P[j], P[R]);
				
				for (auto v : P[j]) classes[v] = j;
				for (int z = 0; z < 26; z++) Q.push({ j, z });
			}
		}
		//for (int i = 0; i < n; i++) err("class[%d] = %d\n", i, classes[i]);
		return (int)P.size();
	}
} A;

#define TASK "fastminimization"

int main() {
#ifndef HOME
	freopen(TASK".in", "r", stdin), freopen(TASK".out", "w", stdout);
#endif
	A.read();
	A.build();
	
	int len = A.findClasses();

	vector<vector<pair<int, int> > > E(len);
	vector<vector<int> > ER(len);
	vector<int> nterm(len), was(len), in(len), was2(len);
	auto comp = classes;
	
	for (int i = 0; i < A.n; i++) {
		for (int j = 0; j < 26; j++) {
			E[comp[i]].push_back({ comp[go[i][j]], j });		
			ER[comp[go[i][j]]].push_back(comp[i]);
		}
	}	
	
	for (int i = 0; i < len; i++) {
		sort(E[i].begin(), E[i].end());
		E[i].resize(unique(E[i].begin(), E[i].end()) - E[i].begin());
	}
	
	for (int i = 0; i < A.n; i++) if (term[i]) {
		nterm[comp[i]] = 1;
	}
	
	queue<int> q;
	
	for (int i = 0; i < len; i++) if (nterm[i]) {
		was[i] = 1, q.push(i);
	}
	
	while (q.size()) {
		int v = q.front();
		q.pop();
		for (int to : ER[v]) if (!was[to]) {
			was[to] = 1, q.push(to);
		}
	}
	
	while (q.size()) q.pop();
	
	was2[comp[0]] = 1;
	q.push(comp[0]);
	
	while (q.size()) {
		int v = q.front();
		q.pop();
		for (auto c : E[v]) if (!was2[c.first]) {
			was2[c.first] = 1, q.push(c.first);
		}
	}
	
	for (int i = 0; i < len; i++) was[i] &= was2[i];
	
	vector<int> G;
	
	int nv = 0, nm = 0, nt = 0;
	for (int i = 0; i < len; i++) if (was[i]) {
		G.push_back(i);
		nv++;
	}
	
	unordered_map<int, int> M;
	for (int i = 0; i < (int)G.size(); i++) M[G[i]] = i;
	
	int ind = comp[0];
	swap(M[ind], M[G[0]]);
	
	for (int i = 0; i < len; i++) {
		for (auto c : E[i]) {
			if (was[i] && was[c.first]) nm++;
		}
	}
	
	for (int i = 0; i < len; i++) if (was[i] && nterm[i]) nt++;
		
	printf("%d %d %d\n", (int)M.size(), nm, nt);
	for (int i = 0; i < len; i++) if (was[i] && nterm[i]) printf("%d ", M[i] + 1);
	printf("\n");
	
	for (int i = 0; i < len; i++) if (was[i]) {
		for (auto c : E[i]) if (was[c.first]) {
			printf("%d %d %c\n", M[i] + 1, M[c.first] + 1, (char)('a' + c.second));
		}
	}
	
	return 0;
}