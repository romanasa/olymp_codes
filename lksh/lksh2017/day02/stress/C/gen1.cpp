#include <bits/stdc++.h>                            

using namespace std;

int R() { return (rand() << 16) | rand(); }

int main(int argc, char* argv[]) {    
	
	srand(atoi(argv[1]));
	
	int n = 5, q = 50;
	int m = 1500;
	cout << n << " " << q << "\n";
	
	vector<pair<int, int> > edges;
	/*set<pair<int, int> > Q;
	
	for (int i = 0; i < m; i++) {
		int a = R() % n + 1, b = R() % n + 1;
		
		if (a == b) b++;
		if (b > n) b -= n;
		
		if (a > b) swap(a, b);
		Q.insert({ a, b });
	}
	
	for (auto c : Q) {
		edges.push_back(c);
	}*/
	
	for (int i = 1; i < n; i++) {
		edges.push_back({ R() % i + 1, i + 1 });
	}
	
	vector<int> f, u;
	for (int i = 0; i < (int)edges.size(); i++) f.push_back(i);
	
	for (int i = 0; i < q; i++) {
		int tp = R() % 4;
		if (tp <= 1 && f.size()) {
			int ind = i % (int)f.size();
			cout << "link " << edges[f[ind]].first << " " << edges[f[ind]].second << "\n";
			u.push_back(f[ind]);
			f.erase(f.begin() + ind);
		} else if (tp == 2 && u.size()) {
			int ind = i % (int)u.size();
			cout << "cut " << edges[u[ind]].first << " " << edges[u[ind]].second << "\n";
			f.push_back(u[ind]);
			u.erase(u.begin() + ind);
		} else {
			cout << "get " << R() % n + 1 << " " << R() % n + 1 << "\n";
			//cout << "?\n";
		}
	}
	
	return 0;
}

