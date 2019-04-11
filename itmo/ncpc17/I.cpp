#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

map<string, int> M;
const int dd = 507;

int G[dd][dd];
int p[dd][dd];

vector<int> restore(int s, int t) {
	int x = p[s][t];
	if (x == -1) return { s, t };
	
	//err("s = %d, x = %d, t = %d\n", s, x, t);
	
	vector<int> C;
	//C.push_back(s);
	
	vector<int> A = restore(s, x);
	if (A.size()) A.pop_back();
	for (int x : A) C.push_back(x);
	
	vector<int> B = restore(x, t);
	for (int x : B) C.push_back(x);
	//C.push_back(t);
	return C;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int n; cin >> n;
	
	vector<string> A(n);
	for (int i = 0; i < n; i++) {
		cin >> A[i];
		M[A[i]] = i;
	}
	
	for (int i = 0; i < n; i++) fill(G[i], G[i] + n, (int)1e9);
	for (int i = 0; i < n; i++) fill(p[i], p[i] + n, -1);
	
	for (int i = 0; i < n; i++) {
		string s; cin >> s;
		int k; cin >> k;	
		int v = M[s];
		
		getline(cin, s);
		for (int j = 0; j < k; j++) {
			string line;
			getline(cin, line);
			
			istringstream in(line);
			string t;
			while (in >> t) {
				if (t == "import") continue;
				if (t.back() == ',') t.pop_back();
				assert(M.count(t));
				
				if (v == M[t]) {
					cout << A[v] << "\n";
					return 0;
				}
				
				G[v][M[t]] = min(G[v][M[t]], 1);
			}
		}
	}
	
	//for (int v = 0; v < n; v++) 
	//	for (int to = 0; to < n; to++) if (G[v][to] < (int)1e9)
	//		err("%d-->%d\n", v, to);
	
	for (int k = 0; k < n; k++) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) if (G[i][k] < (int)1e9 && G[k][j] < (int)1e9 && G[i][j] > G[i][k] + G[k][j] && i != k && k != j) {
				G[i][j] = G[i][k] + G[k][j];
				p[i][j] = k;
				//if (i == j) {
				//	ind = i;
				//	break;
				//}
			}
			//if (ind != -1) break;
		}
		//if (ind != -1) break;
	}
	
	
	int ind = 0;
	for (int i = 0; i < n; i++) if (G[i][i] < G[ind][ind]) ind = i;
	
	if (G[ind][ind] == (int)1e9) {
		cout << "SHIP IT\n";
	} else {
		//err("ind = %d\n", ind);
	
		auto ans = restore(ind, ind);
		ans.pop_back();
		for (int x : ans) cout << A[x] << "\n";
	}
	
	return 0;
}