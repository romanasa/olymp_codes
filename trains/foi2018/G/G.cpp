#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

const int N = 50 * 50;

int dx[] = { -1, 0, 1, 0 };
int dy[] = { 0, 1, 0, -1 };

int ans[50][50];

vector<int> d[N + 7];
set<int> E[N + 7];

set<pair<int, int> > U;
int used[N + 7];
pair<int, int> pos[N + 7];

int dist(int x, int y, int b) {
	return abs(x - pos[b].first) + abs(y - pos[b].second);
}

void add(int a, int b) {
	E[a].insert(b);
	E[b].insert(a);
}

vector<int> bfs(int v) {
	vector<int> d(N, (int)1e9);
	queue<int> q;
	
	d[v] = 0;
	q.push(v);
	
	while (q.size()) {
		int t = q.front();
		q.pop();
		for (int to : E[t]) 
			if (d[to] > d[t] + 1) d[to] = d[t] + 1, q.push(to);
	}	
	return d;
}


int calc(int v, int x, int y, vector<int> &cur) {
	int t = 0;
	for (int q : cur) if (d[q][v] != (int)1e9) {
		if (dist(x, y, q) != d[q][v]) t++;
	}
	return t;
}

int main() {
	for (int it = 0; it < 100; it++) {
		int pr = -1;
		for (int j = 0; j < 100; j++) {
			int t;
			cin >> t;
			t--;
			if (pr != -1) add(pr, t);
			pr = t;
		}
	}
	
	for (int i = 0; i < N; i++) d[i] = bfs(i);
	
	vector<int> cur;
	
	int st = rand() % N;
	
	cur.push_back(st);
	used[st] = 1;
	pos[st] = { 0, 0 };
	U.insert({ 0, 0 });
	
	
	int lx = 0, rx = 0;
	int ly = 0, ry = 0;
	
	while ((int)cur.size() < N) {
	
		if (cur.size() % 100 == 0) err("%d\n", (int)cur.size());
		
		int cc = (int)1e9;
		int nv = -1;
		int nx = -1, ny = -1;
		
		for (int v : cur) {
			for (int gg = 0; gg < 4; gg++) {
			
				int ni = pos[v].first + dx[gg];
				int nj = pos[v].second + dy[gg];
				
				if (U.count({ ni, nj })) continue;
				if (max(rx, ni) - min(lx, ni) >= 50) continue;
				if (max(ry, nj) - min(ly, nj) >= 50) continue;
			
    			for (int to : E[v]) if (!used[to]) {
    				
    				//pos[to] = { ni, nj };
    				int val = calc(to, ni, nj, cur);
    				if (val < cc) {
  						cc = val;
  						nv = to;
  						nx = ni, ny = nj;
      				}
    			}
			}
		}
		
		if (nv == -1) {
			for (int v : cur) {
    			for (int gg = 0; gg < 4; gg++) {
    			
    				int ni = pos[v].first + dx[gg];
    				int nj = pos[v].second + dy[gg];
    				
    				if (U.count({ ni, nj })) continue;
    				if (max(rx, ni) - min(lx, ni) >= 50) continue;
    				if (max(ry, nj) - min(ly, nj) >= 50) continue;
    			
        			for (int to = 0; to < N; to++) if (!used[to]) {
        				
        				//pos[to] = { ni, nj };
        				int val = calc(to, ni, nj, cur);
        				if (val < cc) {
      						cc = val;
      						nv = to;
      						nx = ni, ny = nj;
          				}
          				break;
        			}
    			}
    		}
		}
		
		//err("%d\n", cc);
		
		used[nv] = 1;
		pos[nv] = { nx, ny };
		U.insert({ nx, ny });
		cur.push_back(nv);
		
		lx = min(lx, nx);
		rx = max(rx, nx);
		
		ly = min(ly, ny);
		ry = max(ry, ny);
		
	}
	
	//err("lx = %d, rx = %d\n", lx, rx);
	//err("ly = %d, ry = %d\n", ly, ry);
	//err("%d\n", (int)U.size());
	
	int xx = (int)1e9;
	int yy = (int)1e9;
	vector<pair<int, int> > fr;
	
	for (int x = lx; x <= rx; x++) {
		for (int y = ly; y <= ry; y++) if (!U.count({ x, y }))
			fr.push_back({ x, y });
	}
	for (int i = 0; i < N; i++) if (!used[i]) {
		used[i] = 1;
		pos[i] = fr.back();
		fr.pop_back();
	}
	
	for (int i = 0; i < N; i++) {
		xx = min(xx, pos[i].first);
		yy = min(yy, pos[i].second);
	}
	
	for (int i = 0; i < N; i++) ans[pos[i].first - xx][pos[i].second - yy] = i + 1;
	for (int i = 0; i < 50; i++) {
		for (int j = 0; j < 50; j++) {
			cout << ans[i][j] << " ";
		}
		cout << "\n";
	}
	
	return 0;
}