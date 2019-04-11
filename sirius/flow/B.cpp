#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

const int dd = (int)1e4 + 7;

struct edge { int to, f, c, back; };

vector<vector<edge> > E;

void add(int a, int b, int c) {
	 int ia = (int)E[b].size();
	 int ib = (int)E[a].size();
	 
	 E[a].push_back({ b, 0, c, ia });
	 E[b].push_back({ a, 0, 0, ib });
}

int used[dd];

int dfs(int v, int t, int cmin) {
	if (v == t) return cmin;
	used[v] = 1;
	for (auto &e : E[v]) {
		if (!used[e.to] && e.f < e.c) {
			int df = dfs(e.to, t, min(cmin, e.c - e.f));
			if (df) {
				e.f += df;
				E[e.to][e.back].f -= df;
				return df;
			}
		}
	}
	return 0;
}

int N;

int findflow(int s, int t) {
	int flow = 0;
	while (1) {
		fill(used, used + N, 0);
		int df = dfs(s, t, (int)1e9);
		if (!df) break;
		flow += df;
	}
	return flow;
}

map<string, int> M;
int nv;


int get(string s) {
	if (M.count(s)) return M[s];
	return M[s] = nv++;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);	
	
	int t;
	cin >> t;
	
	while (t--) {	
		int n;
		cin >> n;

		M.clear();
		nv = n;	
		
		N = 2 * 1000 + n * 10;
		N *= 2;
		
		E.resize(0);
		E.resize(N);
		
		string s;
		getline(cin, s);
		
		for (int i = 0; i < n; i++) {
			
			getline(cin, s);
			istringstream in(s);
			//cout << i << endl;
			//cout << s << endl;
			
			string t;
			while (in >> t) {
				//cout << i << " " << t << endl;
				
				int x = get(t);
				
				add(i, 2 * x, (int)1e9);
				add(2 * x + 1, i, (int)1e9);
			}
		}
		
		for (int i = n; i < nv; i++) add(2 * i, 2 * i + 1, 1);
		
		if (n == 1) cout << "0\n";
		else cout << findflow(0, 1) << "\n";
	}
	return 0;
}