#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

vector<vector<pair<int, ll> > > E;
map<pair<int, int>, int> M, I;
int nv;

int num(int x, int y) {
	int &res = M[{ x, y }];
	if (res == 0) {
		res = nv++;
		E.push_back(vector<pair<int, ll>>(0));
	}
	return res;
}

void add(int x1, int y1, int x2, int y2) {
	int a = num(x1, y1);
	int b = num(x2, y2);
	
	assert(x1 == x2 || y1 == y2);
	ll len = max(abs(x2 - x1), abs(y2 - y1));
	
	E[a].push_back({ b, len });
	E[b].push_back({ a, len });
}


struct rect {
	int x1, y1, x2, y2;
};

void add(pair<int, int> a, pair<int, int> b, vector<rect> &T) {
	
	if (I.count(a) && I.count(b) && I[a] == I[b]) {
		int j = I[a];
		if (a.first == b.first) {
			if (a.first != T[j].x1 && a.first != T[j].x2) return;
		}
		if (a.second == b.second) {
			if (a.second != T[j].y1 && a.second != T[j].y2) return;
		}
	}
	
	add(a.first, a.second, b.first, b.second);
}

bool ch(int a, int b, int c) { return a <= b && b <= c; }



void down(int X, int Y, vector<rect> &T, int n) {
   	int ind = -1;
   	for (int j = 0; j < n; j++) if (T[j].y2 < Y && ch(T[j].x1, X, T[j].x2)) {
   		if (ind == -1 || T[j].y2 > T[ind].y2) ind = j;	
   	}
   	if (ind != -1) { int j = ind;
   		num(X, T[j].y2);
   		I[{ X, T[j].y2 }] = j;
   	}
}

void left(int X, int Y, vector<rect> &T, int n) {
	int ind  = -1;
   	for (int j = 0; j < n; j++) if (T[j].x2 < X && ch(T[j].y1, Y, T[j].y2)) {
   		if (ind == -1 || T[j].x2 > T[ind].x2) ind = j;
   	}
   	if (ind != -1) { int j = ind;
   		num(T[j].x2, Y);
   		I[{ T[j].x2, Y }] = j;
	}
}

void up(int X, int Y, vector<rect> &T, int n) {
   	int ind = -1;
   	for (int j = 0; j < n; j++) if (T[j].y1 > Y && ch(T[j].x1, X, T[j].x2)) {
   		if (ind == -1 || T[j].y1 < T[ind].y1) ind = j;	
   	}
   	if (ind != -1) { int j = ind;
   		num(X, T[j].y1);
   		I[{ X, T[j].y1 }] = j;
   	}
}


void right(int X, int Y, vector<rect> &T, int n) {
	int ind  = -1;
   	for (int j = 0; j < n; j++) if (T[j].x1 > X && ch(T[j].y1, Y, T[j].y2)) {
   		if (ind == -1 || T[j].x1 < T[ind].x1) ind = j;
   	}
   	if (ind != -1) { int j = ind;
   		num(T[j].x1, Y);
   		I[{ T[j].x1, Y }] = j;
	}
}

ll dist(int s, int t) {
	vector<ll> d(nv, (ll)1e18);
	priority_queue<pair<ll, int> > Q;
	
	d[s] = 0;
	Q.push({ -d[s], s });
	
	while (Q.size()) {
		int v = Q.top().second;
		ll cur = -Q.top().first;
		
		Q.pop();
		
		if (d[v] != cur) continue;
		
		for (auto &e : E[v]) {
			if (d[e.first] > cur + e.second) {
				d[e.first] = cur + e.second;
				Q.push({ -d[e.first], e.first });
			}
		}
	}
	return d[t];
}

int solve() {
	I.clear();
	M.clear(), nv = 1;
	E.resize(1);

	int sx, sy, fx, fy;
	cin >> sx >> sy >> fx >> fy;

	int n;
	cin >> n;
	
	vector<rect> T(n);
	
	for (int i = 0; i < n; i++) {
		int x1, y1, x2, y2;
		cin >> x1 >> y1 >> x2 >> y2;
		
		if (x1 > x2) swap(x1, x2);
		if (y1 > y2) swap(y1, y2);
		
		add(x1, y1, x2, y1);
		add(x1, y1, x1, y2);
		add(x2, y2, x2, y1);
		add(x2, y2, x1, y2);
		
		T[i] = { x1, y1, x2, y2 };
	}	
	
	for (int i = 0; i < n; i++) {
		down(T[i].x1, T[i].y1, T, n);
		left(T[i].x1, T[i].y1, T, n);
		
		left(T[i].x1, T[i].y2, T, n);
		up(T[i].x1, T[i].y2, T, n);
		
		up(T[i].x2, T[i].y2, T, n);
		right(T[i].x2, T[i].y2, T, n);
		
		right(T[i].x2, T[i].y1, T, n);
		down(T[i].x2, T[i].y1, T, n);
	}
	
	down(sx, sy, T, n), left(sx, sy, T, n), up(sx, sy, T, n), right(sx, sy, T, n);
	down(fx, fy, T, n), left(fx, fy, T, n), up(fx, fy, T, n), right(fx, fy, T, n);
	
	
	num(sx, sy);
	num(fx, fy);
	
	vector<pair<int, int> > W;
	for (auto c : M) W.push_back(c.first);
	
	
	//err("W = "); for (auto c : W) err("(%d, %d), ", c.first, c.second); err("\n");
	
	for (int i = 1; i < (int)W.size(); i++) {
		if (W[i - 1].first == W[i].first) add(W[i - 1], W[i], T);
	}
	
	sort(W.begin(), W.end(), [](pair<int, int> a, pair<int,int> b) { return make_pair(a.second, a.first) < make_pair(b.second, b.first); });
	
	//err("W = "); for (auto c : W) err("(%d, %d), ", c.first, c.second); err("\n");
	for (int i = 1; i < (int)W.size(); i++) {
		if (W[i - 1].second == W[i].second) add(W[i - 1], W[i], T);
	}
	
	//if (sx == fx || sy == fy) add(sx, sy, fx, fy);
	
	ll d = dist(num(sx, sy), num(fx, fy));
	if (d == (ll)1e18) cout << "No Path\n";
	else cout << d << "\n";
	
	/*for (auto c : M) {
		err("(%d, %d) = %d\n", c.first.first, c.first.second, c.second);
	}
	
	for (int v = 0; v < nv; v++) {
		for (auto &e : E[v]) {
			err("%d--%I64d-->%d\n", v, e.second, e.first); 
		}
	}*/
	
	return 0;
}

int main() {
	int t;
	cin >> t;
	while (t--) solve();
	return 0;
}