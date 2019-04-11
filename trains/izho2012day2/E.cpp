#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

map<int, vector<int> > X, Y;
vector<int> x, y, d;
int w, h, k, t;
	
#define TASK "e"

void doX(vector<int> &cur) {
	vector<int> used((int)cur.size());
   	for (int i = 0; i + 1 < (int)cur.size(); i++) if (!used[i]) {
   		if (y[cur[i]] + 1 == y[cur[i + 1]] && d[cur[i]] == 2 && d[cur[i + 1]] == 4) {
   			swap(d[cur[i]], d[cur[i + 1]]);
   			used[i] = 1, used[i + 1] = 1;
   			continue;
   		}
   		if (y[cur[i]] + 2 == y[cur[i + 1]] && d[cur[i]] == 2 && d[cur[i + 1]] == 4) {
   			swap(d[cur[i]], d[cur[i + 1]]);
   			y[cur[i]]++;
   			y[cur[i + 1]]--;
   			used[i] = 1, used[i + 1] = 1;
   			continue;
   		}
   	}
   	for (int i = 0; i < (int)cur.size(); i++) if (!used[i]) 
   		if (d[cur[i]] == 2) y[cur[i]]++;
   		else y[cur[i]]--; 
   	for (int i = 0; i + 1 < (int)cur.size(); i++) 
   		if (y[cur[i]] == y[cur[i + 1]] && d[cur[i]] == 2 && d[cur[i + 1]] == 4) swap(d[cur[i]], d[cur[i + 1]]);
   	for (int i = 0; i < (int)cur.size(); i++) {
   		if (y[cur[i]] == h && d[cur[i]] == 2) d[cur[i]] = 4;
   		if (y[cur[i]] == 0 && d[cur[i]] == 4) d[cur[i]] = 2;
 	}
}

void doY(vector<int> &cur) {
	vector<int> used((int)cur.size());
   	for (int i = 0; i + 1 < (int)cur.size(); i++) if (!used[i]) {
   		if (x[cur[i]] + 1 == x[cur[i + 1]] && d[cur[i]] == 1 && d[cur[i + 1]] == 3) {
   			swap(d[cur[i]], d[cur[i + 1]]);
   			used[i] = 1, used[i + 1] = 1;
   			continue;
   		}
   		if (x[cur[i]] + 2 == x[cur[i + 1]] && d[cur[i]] == 1 && d[cur[i + 1]] == 3) {
   			swap(d[cur[i]], d[cur[i + 1]]);
   			x[cur[i]]++;
   			x[cur[i + 1]]--;
   			used[i] = 1, used[i + 1] = 1;
   			continue;
   		}
   	}
   	for (int i = 0; i < (int)cur.size(); i++) if (!used[i]) 
   		if (d[cur[i]] == 1) x[cur[i]]++;
   		else x[cur[i]]--; 
   	for (int i = 0; i + 1 < (int)cur.size(); i++) 
   		if (x[cur[i]] == x[cur[i + 1]] && d[cur[i]] == 1 && d[cur[i + 1]] == 3) swap(d[cur[i]], d[cur[i + 1]]);
   	for (int i = 0; i < (int)cur.size(); i++) {
   		if (x[cur[i]] == w && d[cur[i]] == 1) d[cur[i]] = 3;
   		if (x[cur[i]] == 0 && d[cur[i]] == 3) d[cur[i]] = 1;
	}
}

void outY(vector<pair<int, pair<int, int> > > Q) {
	for (auto c : Q) {
		x[c.first] = c.second.first;
		d[c.first] = c.second.second;
	}
}

void outX(vector<pair<int, pair<int, int> > > Q) {
	for (auto c : Q) {
		y[c.first] = c.second.first;
		d[c.first] = c.second.second;
	}
}

int main() {
#ifndef HOME
	freopen(TASK".in", "r", stdin), freopen(TASK".out", "w", stdout);
#endif
	cin >> w >> h >> k >> t;
	
	x.resize(k), y.resize(k), d.resize(k);
	
	for (int i = 0; i < k; i++) {
		cin >> x[i] >> y[i] >> d[i];
		if (d[i] == 2 || d[i] == 4) X[x[i]].push_back(i);
		else Y[y[i]].push_back(i);
	}
	
	for (auto c : X) {
		auto &cur = c.second;
		sort(cur.begin(), cur.end(), [&](int a, int b) { return y[a] < y[b]; });
		
		vector<vector<pair<int, pair<int, int>> > > Q;
		vector<pair<int, int> > T;
		map<vector<pair<int, int> >, int> M;
		
		for (int i : cur) T.push_back({ y[i], d[i] });
		M[T] = 0;
		
		int A = (int)1e9 + 1, B = -1;		
		
		for (int it = 0; it <= t; it++) {
			Q.push_back(vector<pair<int, pair<int, int> > >(0));
			for (int i : cur) Q[it].push_back({ i, { y[i], d[i] } });
			if (it == t) break;
			doX(cur);
			
			int cnt = 0;
			for (int i : cur) T[cnt++] = { y[i], d[i] };
			
			
			auto itt = M.find(T);
			if (itt == M.end()) M[T] = it + 1;
			else {
				A = itt->second, B = it;
				break;
			}
			//err("it = %d\n", it);
		}
		if (t <= A) outX(Q[t]);
		else {
			int q = t;
			q -= A;
			q %= (B - A + 1);
			outX(Q[q + A]);
		}
	}
	
	for (auto c : Y) {
		auto &cur = c.second;
		sort(cur.begin(), cur.end(), [&](int a, int b) { return x[a] < x[b]; });
		
		vector<vector<pair<int, pair<int, int>> > > Q;
		vector<pair<int, int> > T;
		map<vector<pair<int, int> >, int> M;
		
		for (int i : cur) T.push_back({ x[i], d[i] });
		M[T] = 0;
		
		int A = (int)1e9 + 1, B = -1;
		
		for (int it = 0; it <= t; it++) {
			//err("it = %d\n", it);
			Q.push_back(vector<pair<int, pair<int, int> > >(0));
			for (int i : cur) Q[it].push_back({ i, { x[i], d[i] } });
		
			if (it == t) break;
			
			doY(cur);
			//err("ok\n");
			
			int cnt = 0;
			for (int i : cur) T[cnt++] = { x[i], d[i] };
			
			auto itt = M.find(T);
			if (itt == M.end()) M[T] = it + 1;
			else {
				A = itt->second, B = it;
				break;
			}
			//err("ok1\n");
		}

		//err("t = %d, A = %d\n", t, A);
		
		//err("t = %d, A = %d\n", t, A);
		  	
		
		if (t <= A) outY(Q[t]);
		else {
			int q = t;
			q -= A;
			q %= (B - A + 1);
			outY(Q[q + A]);
		}
	}
	
	for (int i = 0; i < k; i++) cout << x[i] << " " << y[i] << " " << d[i] << "\n";

	return 0;
}